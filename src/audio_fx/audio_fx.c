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
    if(buff == NULL)
    {
        sys_print_error("Audio buffer is NULL");
        return -1;
    }

    if(dist_level > 100 || wet > 100)
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
    for(Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        if(buff[sample] > 0) buff[sample] = (Sint16)(buff[sample]*(1-((double)wet/100) + ((double)wet/100)*(double)(1 - exp(-((double)dist_level/2)*buff[sample]))));
        else buff[sample] = (Sint16)(buff[sample]*(1-((double)wet/100) + ((double)wet/100)*(double)(-1 + exp(((double)dist_level/2)*buff[sample]))));
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

    if(mod_level > 100 || freq < 0)
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

    lfo->wave=SIN;
    lfo->duty=100;
    lfo->detune=0;
    lfo->amp=INT16_MAX;
    lfo->onoff=ON;
    lfo->freq=freq;

    if(osc_fill_buffer(lfo,buffer_length,sample_rate,lfo_phase))return -1;
    lfo_phase = (lfo_phase + buffer_length);

    for(Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        temp_sample = (double)lfo->buffer[sample];
        temp_sample /= (lfo->amp * 2);
        temp_sample += 1;
        buff[sample] = (Sint16)((double)buff[sample] * (1 - temp_sample * (mod_level / 100.0)));
    }

    free_osc(lfo);

    return 0;
}