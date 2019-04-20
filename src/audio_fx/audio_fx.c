/**
 * \file audio_fx.c
 * \brief Audio effects data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the audio effects, and the related functions
 */

#include "audio_fx.h"

static Sint8 sgn(double x)
{
    // return 1 if positive, -1 if negative
    return (x >= 0) ? 1 : -1;
}

int distortion(Audio_Buffer buff, Uint16 buffer_length, Uint8 dist_level, Uint8 wet)
{
    if (buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if (dist_level > 100 || wet > 100)
    {
        sys_print_error("Parameter is out of range (>100)");
        return -1;
    }

    double temp_sample;

    /**
     * Basic distortion algorithm :
     * y=(1+a*sgn(x)*(1-exp(-b*abs(x)))
     * a is the wet level aka the mix between dry(no effect) and wet(only effect)
     * b is the distortion level
     *
     * Dynamic plot (GEOGEBRA) : https://www.geogebra.org/graphing/z8wzf8et
     */

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        temp_sample = (double) sgn((double) buff[sample])
            * (1.0 - exp((-((double) dist_level + 1.0) / (double) DIST_ATTENUATOR) * fabs((double) buff[sample])
                             / (double) INT16_MAX));

        // Clipper
        if (temp_sample > INT16_MAX)temp_sample = INT16_MAX;
        if (temp_sample < INT16_MIN) temp_sample = INT16_MIN;

        buff[sample] = (Sint16) ((double) buff[sample] * (1.0 - (double) wet / 100.0)
            + ((double) wet / 100.0) * temp_sample * (double) INT16_MAX);

    }

    return 0;
}

int amp_mod(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, Waveform wave, Uint8 duty, Uint8 mod_level)
{
    if (buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if (mod_level > 100 || freq < 0 || wave > TRI || duty > 100)
    {
        sys_print_error("Parameter is out of range");
        return -1;
    }

    double temp_sample;
    static Uint64 lfo_phase;

    Oscillator *lfo = alloc_osc(buffer_length);
    if (lfo == NULL)
    {
        sys_print_error("Osc is NULL");
        return -1;
    }

    lfo->wave = wave;
    lfo->duty = duty;
    lfo->detune = 0;
    lfo->amp = INT16_MAX;
    lfo->onoff = ON;
    lfo->freq = freq;

    if (osc_fill_buffer(lfo, buffer_length, sample_rate, lfo_phase))return -1;
    lfo_phase = (lfo_phase + buffer_length);

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        temp_sample = (double) lfo->buffer[sample];
        temp_sample /= (lfo->amp * 2);
        temp_sample += 1;
        buff[sample] = (Sint16) ((double) buff[sample] * (1 - temp_sample * (mod_level / 100.0)));
    }

    free_osc(lfo);

    return 0;
}

int flanger(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, double delay, Uint8 lfo_range, Uint8 depth, Waveform wave)
{
    if (buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if (depth > 100 || freq < 0 || depth > 100 || lfo_range > 100
        || delay > (1000.0 * (double) MAX_SAMPLE_DELAY_LINE / (double) sample_rate))
    {
        sys_print_error("Parameter is out of range");
        return -1;
    }

    Uint64 ind, actual_ind;
    static Uint64 lfo_phase;
    static Sint16 delay_line[MAX_SAMPLE_DELAY_LINE];
    static Uint32 cursor;

    Oscillator *lfo = alloc_osc(buffer_length);
    if (lfo == NULL)
    {
        sys_print_error("Osc is NULL");
        return -1;
    }

    // Fill delay_line
    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        cursor = (cursor + 1u) & (MAX_SAMPLE_DELAY_LINE - 1u);  // Increment cursor, avoid delay_line array overflow
        delay_line[cursor] = buff[sample];
    }

    lfo->wave = wave;
    lfo->duty = 50;
    lfo->detune = 0;
    lfo->amp = (Uint16) (((double) lfo_range / 100.0) * (double) delay);
    lfo->onoff = ON;
    lfo->freq = freq;

    if (osc_fill_buffer(lfo, buffer_length, sample_rate, lfo_phase))
    {
        free_osc(lfo);
        return -1;
    }
    lfo_phase = lfo_phase + buffer_length;

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        actual_ind = cursor - buffer_length + sample;
        ind = (actual_ind - (lfo->buffer[sample] + lfo->amp + (int) (delay * 0.001 * (double) sample_rate)))
            & (MAX_SAMPLE_DELAY_LINE - 1u);
        buff[sample] =
            (Sint16) ((double) buff[sample] - (((double) depth / 100.0) * (double) delay_line[ind]));
    }

    free_osc(lfo);

    return 0;
}

int lfo_filter(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, Filter_type filter_type, Uint16 filter_freq, double lfo_freq, double resonance, Waveform wave, Uint8 duty, Uint16 filter_excursion)
{
    if (buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if (lfo_freq < 0)
    {
        sys_print_error("Parameter is out of range");
        return -1;
    }

    static Uint64 lfo_phase;
    static sf_biquad_state_st filter_state;
    Filter_param filter_param;
    sf_sample_st st_buff[buffer_length];

    filter_param.filter_type = filter_type;
    filter_param.resonance = resonance;

    Oscillator *lfo = alloc_osc(buffer_length);
    if (lfo == NULL)
    {
        sys_print_error("Osc is NULL");
        return -1;
    }

    lfo->wave = wave;
    lfo->duty = duty;
    lfo->detune = 0;
    lfo->amp = filter_excursion;
    lfo->onoff = ON;
    lfo->freq = lfo_freq;

    if (osc_fill_buffer(lfo, buffer_length, sample_rate, lfo_phase))return -1;
    lfo_phase = (lfo_phase + buffer_length);

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        // Convert to float < 1 to work with the library filter code
        st_buff[sample].L = (double) (buff[sample]) / 32768.0;
        st_buff[sample].R = 0;
    }

    for (Uint16 sample = 0; sample < buffer_length; sample += LFO_FILTER_SAMPLE_INCREMENT)
    {
        // Mod filter freq with LFO
        filter_param.cutoff_freq =
            (filter_freq + lfo->buffer[sample] > 0) ? (Uint16) (filter_freq + lfo->buffer[sample]) : 0;

        // Compute filter coefficients with new frequency
        if (compute_filter_coeffs(&filter_param, sample_rate, &filter_state))return -1;

        // Apply filter
        sf_biquad_process(&filter_state, LFO_FILTER_SAMPLE_INCREMENT, &st_buff[sample], &st_buff[sample]);
    }

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        buff[sample] = (Sint16) (st_buff[sample].L * 32767.0); // Convert back to full range Sint16
    }

    free_osc(lfo);

    return 0;
}

int biquad(Audio_Buffer buff, Uint16 buffer_length, sf_biquad_state_st *state)
{
    if (buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if (state == NULL)
    {
        sys_print_error("State object (=filter coefficients) is NULL");
        return -1;
    }

    if (buffer_length == 0)
    {
        sys_print_error("Buffer length is zero");
        return -1;
    }

    sf_sample_st st_buff[buffer_length];

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        // Convert to float < 1 to work with the library filter code
        st_buff[sample].L = (float) (buff[sample]) / 32768.0f;
        st_buff[sample].R = 0;
    }

    sf_biquad_process(state, buffer_length, st_buff, st_buff);

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        buff[sample] = (Sint16) (st_buff[sample].L * 32767.0f); // Convert back to full range Sint16
    }

    return 0;
}

int compute_filter_coeffs(Filter_param *filter_param, Uint32 sample_rate, sf_biquad_state_st *state)
{
    if (filter_param == NULL)
    {
        sys_print_error("System parameters is NULL");
        return -1;
    }

    if (state == NULL)
    {
        sys_print_error("State object (=filter coefficients) is NULL");
        return -1;
    }

    switch (filter_param->filter_type)
    {
        case LOWPASS:sf_lowpass(state, sample_rate, (float) filter_param->cutoff_freq, (float) filter_param->resonance);
            break;
        case HIGHPASS:sf_highpass(state, sample_rate, (float) filter_param->cutoff_freq, (float) filter_param->resonance);
            break;
        case BANDPASS:sf_bandpass(state, sample_rate, (float) filter_param->cutoff_freq, (float) filter_param->resonance);
            break;
        case NOTCH:sf_notch(state, sample_rate, (float) filter_param->cutoff_freq, (float) filter_param->resonance);
            break;
        default :sys_print_error("Filter type is unknown");
            return -1;
    }

    return 0;
}

Effect_core *alloc_effect_core()
{
    Effect_core *ec = (Effect_core *) malloc(sizeof(Effect_core));
    if (ec == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    ec->filter_state = (sf_biquad_state_st *) malloc(sizeof(sf_biquad_state_st));
    if (ec->filter_state == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    return ec;
}

int free_effect_core(Effect_core *ec)
{
    free(ec->filter_state);
    free(ec);
    return 0;
}