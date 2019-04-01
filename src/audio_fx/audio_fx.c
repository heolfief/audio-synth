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