/**
 * \file osc.h
 * \brief Oscillator data structure and function definition.
 *
 *
 * Here are defined the data structure of the oscillator, and the related functions
 */

#ifndef AUDIO_SYNTH_OSC_H
#define AUDIO_SYNTH_OSC_H

#include <SDL2/SDL_stdinc.h>

/**
 * \enum Waveform
 * \brief various waveform types
 *
 * This enum defines the various waveform types : sine, square, triangle and sawtooth
 */
typedef enum{
    SIN,                 /*!< Sinusoidal waveform */
    SQR,                 /*!< Square waveform */
    TRI,                 /*!< Triangle waveform */
    SAW                  /*!< Sawtooth waveform */
} Waveform;

/**
 * \struct Oscillator
 * \brief define an oscillator
 *
 * An oscillator is defined with : wave, frequency, amplitude, detune and dutycycle
 */
typedef struct{
    Waveform wave;       /*!<the waveform type */
    Uint16   freq;       /*!<the frequency */
    Uint16   amp;        /*!<the amplitude */
    Sint8    detune;     /*!<the detune in number of notes */
    Sint8    duty;       /*!<the dutycyle (if available for the selected waveform */
}Oscillator;


/**
 * \fn Uint8 osc_fill_buffer(const Oscillator *osc, Sint16 *buffer, Uint16 buffer_length, Uint64 sample_rate)
 * \brief Function to fill audio buffer with oscillator wave
 *
 * \param osc The oscillator structure
 * \param buffer The audio buffer to write audio samples to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
Uint8 osc_fill_buffer(const Oscillator *osc, Sint16 *buffer, Uint16 buffer_length, Uint64 sample_rate);


#endif //AUDIO_SYNTH_OSC_H
