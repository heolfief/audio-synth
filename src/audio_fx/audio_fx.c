/**
 * \file audio_fx.c
 * \brief Audio effects data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the audio effects, and the related functions
 */

#include "audio_fx.h"

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

    /**
     * Basic distortion algorithm :
     * y=(1+a*sgn(x)*(1-exp(-b*abs(x)))
     * a is the wet level aka the mix bettwen dry(no effect) and wet(only effect)
     * b is the distortion level
     *
     * Dynamic plot (GEOGEBRA) : https://www.geogebra.org/graphing/z8wzf8et
     */
    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        if (buff[sample] > 0)
        {
            buff[sample] = (Sint16) (buff[sample] * (1 - ((double) wet / 100)
                + ((double) wet / 100) * (double) (1 - exp(-((double) dist_level / 2) * buff[sample]))));
        }
        else
        {
            buff[sample] = (Sint16) (buff[sample] * (1 - ((double) wet / 100)
                + ((double) wet / 100) * (double) (-1 + exp(((double) dist_level / 2) * buff[sample]))));
        }
    }

    return 0;
}

int amp_mod(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, Uint8 mod_level)
{
    if (buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if (mod_level > 100 || freq < 0)
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

    lfo->wave = SIN;
    lfo->duty = 100;
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

    if (depth > 100 || freq < 0 || depth > 100 || lfo_range > 100 || delay > (1000.0 * (double)MAX_SAMPLE_DELAY_LINE/(double)sample_rate))
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
        cursor = (cursor + 1) & (MAX_SAMPLE_DELAY_LINE - 1);  // Increment cursor, avoid delay_line array overflow
        delay_line[cursor] = buff[sample];
    }

    lfo->wave = wave;
    lfo->duty = 50;
    lfo->detune = 0;
    lfo->amp = (Uint16) (((double) lfo_range / 100.0) * (double) delay);
    lfo->onoff = ON;
    lfo->freq = freq;

    if (osc_fill_buffer(lfo, buffer_length, sample_rate, lfo_phase))return -1;
    lfo_phase = lfo_phase + buffer_length;

    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        actual_ind = cursor - buffer_length + sample;
        ind = (actual_ind - (lfo->buffer[sample] + lfo->amp + (int) (delay * 0.001 * (double) sample_rate)))
            & (MAX_SAMPLE_DELAY_LINE - 1);
        buff[sample] =
            (Sint16) ((double) buff[sample] - (((double) depth / 100.0) * (double) delay_line[ind]));
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