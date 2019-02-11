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

typedef Sint16 Osc_Buffer;

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
 * \enum OscONOFF
 * \brief defines ON and OFF values for an oscillator
 *
 */
typedef enum{
    OFF,                 /*!< Oscillator is OFF */
    ON,                  /*!< Oscillator is ON */
} OscONOFF;

/**
 * \struct Oscillator
 * \brief define an oscillator
 *
 * An oscillator is defined with : wave, frequency, amplitude, detune, dutycycle and on/off value
 */
typedef struct{
    Waveform wave;       /*!<the waveform type */
    Uint16   freq;       /*!<the frequency */
    Uint16   amp;        /*!<the amplitude */
    Sint8    detune;     /*!<the detune in number of notes */
    Sint8    duty;       /*!<the dutycyle in percents (if available for the selected waveform) */
    OscONOFF onoff;      /*!<the on/off value */
}Oscillator;


/**
 * \fn Uint8 osc_fill_buffer(const Oscillator *osc, Sint16 *buffer, Uint16 buffer_length, Uint64 sample_rate)
 * \brief Function to fill audio buffer with oscillator wave
 *
 * \param osc The oscillator structure
 * \param buffer The audio buffer to write audio samples to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int osc_fill_buffer(const Oscillator *osc, Sint16 *buffer, Uint16 buffer_length, Uint64 sample_rate, Uint64 phase);

/**
 * \fn int alloc_osc_buffer(Sint16 *osc_buff, Uint16 buff_size)
 * \brief Function to allocate memory for an oscillator audio buffer
 *
 * \param buff_nb_samples The number of samples in the audio buffer
 *
 * \return the allocated address
 */
Osc_Buffer* alloc_osc_buffer(Uint16 buff_nb_samples);

/**
 * \fn int free_osc_buffer(Sint16 *osc_buff)
 * \brief Function to free memory of an oscillator audio buffer
 *
 * \param osc_buff The oscillator audio buffer
 *
 * \return 0
 */
int free_osc_buffer(Sint16 *osc_buff);


#endif //AUDIO_SYNTH_OSC_H
