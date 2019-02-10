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
    Uint16 detuned_freq = (Uint16)(osc->freq * (double)pow(chromatic_ratio, osc->detune));

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
            for (Uint16 sample = 0; sample < buffer_length; ++sample)
            {
                // Fill the buffer with a square wave based on it's frequency, amplitude, phase, and duty cycle
                buffer[sample] = (((sample + phase) * 2 * detuned_freq/sample_rate) % 2) ? osc->amp : (Sint16)-osc->amp;
            }
            break;

        case TRI:

            break;

        case SAW:

            break;
        default:
            return -1; // if waveform is unknown
    }
    return 0;
}