/**
 * \file osc.c
 * \brief Oscillator functions.
 *
 *
 * Here are implemented the oscillator's related functions
 */

#include <math.h>
#include <SDL2/SDL_stdinc.h>
#include "osc.h"


static const double chromatic_ratio = 1.059463094359295264562;

int osc_fill_buffer(const Oscillator *osc, Sint16 *buffer, Uint16 buffer_length, Uint64 sample_rate, Uint64 phase)
{
    if(osc == NULL)
    {
        perror("osc parameter is NULL\n");
        return -1;
    }

    if(osc->amp > INT16_MAX)
    {
        perror("osc amplitude passed maximum, risk of audio buffer overflow\n");
        return -1;
    }

    // Calculate actual frequency based on detune value
    Uint16 detuned_freq = (Uint16)(osc->freq * pow(chromatic_ratio, osc->detune));

    double offset = 0;
    double nb_samples_in_period=0;

    switch (osc->wave)
    {
        case SIN:

            for (Uint16 sample = 0; sample < buffer_length; ++sample)
            {
                // Fill the buffer with a sine wave based on it's frequency, amplitude and phase
                buffer[sample] = (Sint16)(osc->amp * (sin((sample + phase) * detuned_freq * 2 * M_PI / sample_rate)));
            }
            break;

        case SQR:


            // Calculate signal offset (average value)
            offset = (osc->duty / 100.0) * osc->amp + (1.0 - (osc->duty / 100.0)) * -osc->amp;

            nb_samples_in_period = (double)sample_rate / detuned_freq;

            for (Uint16 sample = 0; sample < buffer_length; ++sample)
            {
                // Fill the buffer with a square wave based on it's frequency, amplitude, phase, and duty cycle
                buffer[sample] = (fmod((sample + phase), nb_samples_in_period) < ((osc->duty / 100.0) * nb_samples_in_period)) ? osc->amp : (Sint16)-osc->amp;

                // Remove offset to center signal on 0, stay on signed 16 bits representation
                /*if(((Uint32)buffer[sample] - (Uint32)offset) > INT16_MAX)
                {
                    buffer[sample] = INT16_MAX;
                }
                else if(((Uint32)buffer[sample] - (Uint32)offset) < INT16_MIN)
                {
                    buffer[sample] = INT16_MIN;
                }
                else buffer[sample] -= (Uint16)offset;*/
            }
            break;

        case TRI:

            nb_samples_in_period = (double)sample_rate / detuned_freq;

            for (Uint16 sample = 0; sample < buffer_length; ++sample)
            {
                // Fill the buffer with a triangle wave based on it's frequency, amplitude and phase
                double mod = fmod((sample + phase), nb_samples_in_period);
                double mul =
                buffer[sample] = (fmod((sample + phase), nb_samples_in_period) < (nb_samples_in_period / 2))
                        ? (Sint16) 2 * (Uint16)mod * osc->amp / (Sint16)nb_samples_in_period - osc->amp / (Uint16)2
                        : (Sint16) - 2 * (Uint16)mod * osc->amp / (Sint16)nb_samples_in_period + (Uint16)(osc->amp * 1.5);
            }
            break;

        case SAW:

            break;

        default:
            return -1; // if waveform is unknown
    }
    return 0;
}

Osc_Buffer* alloc_osc_buffer(Uint16 buff_nb_samples)
{
    Osc_Buffer *osc_buff = (Osc_Buffer *) calloc(buff_nb_samples, sizeof(Osc_Buffer));
    if(osc_buff == NULL)
    {
        perror("memory allocation error\n");
        return NULL;
    }

    return osc_buff;
}

int free_osc_buffer(Sint16 *osc_buff)
{
    free(osc_buff);
    return 0;
}