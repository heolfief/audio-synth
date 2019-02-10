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

Uint8 osc_fill_buffer(const Oscillator *osc, Sint16 *buffer, Uint16 buffer_length, Uint64 sample_rate, Uint64 phase)
{
    // Calculate actual frequency based on detune value
    Uint16 detuned_freq = osc->freq * (Uint16)pow(chromatic_ratio, osc->detune);

    switch (osc->wave)
    {
        case SIN:

            for (Uint16 i = 0; i < buffer_length; ++i)
            {
                // Fill the buffer with a sine wave based on it's frequency, amplitude and phase
                buffer[i] = (Sint16)(osc->amp * (sin((i + phase) * detuned_freq * 2 * M_PI / sample_rate)));
            }
            break;

        case SQR:

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