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

typedef Sint16 *Osc_Buffer;

/**
 * \enum Waveform
 * \brief various waveform types
 *
 * This enum defines the various waveform types : sine, square and triangle
 */
typedef enum{
    SIN,                 /*!< Sinusoidal waveform */
    SQR,                 /*!< Square waveform */
    TRI,                 /*!< Triangle waveform */
} Waveform;

/**
 * \enum ONOFF
 * \brief defines ON and OFF values
 *
 */
typedef enum{
    OFF,                 /*!< object is OFF */
    ON,                  /*!< object is ON */
} OnOff;

/**
 * \struct Oscillator
 * \brief define an oscillator
 *
 * An oscillator is defined with : wave, frequency, amplitude, detune, dutycycle and on/off value
 * It is associated with it's own buffer to store the audio samples it created
 */
typedef struct{
    Waveform    wave;       /*!<the waveform type */
    Uint16      freq;       /*!<the frequency */
    Uint16      amp;        /*!<the amplitude */
    Sint8       detune;     /*!<the detune in number of notes */
    Sint8       duty;       /*!<the dutycyle in percents (if available for the selected waveform) */
    OnOff       onoff;      /*!<the on/off value */
    Osc_Buffer  buffer;     /*!<the audio data buffer of the oscillator */
}Oscillator;


/**
 * \fn int osc_fill_buffer(const Oscillator *osc, Osc_Buffer buffer, Uint16 buffer_length, Uint64 sample_rate, Uint64 phase)
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
int osc_fill_buffer(const Oscillator *osc, Osc_Buffer buffer, Uint16 buffer_length, Uint64 sample_rate, Uint64 phase);

/**
 * \fn Osc_Buffer alloc_osc_buffer(Uint16 buff_nb_samples)
 * \brief Function to allocate memory for an oscillator audio buffer
 *
 * \param buff_nb_samples The number of samples in the audio buffer
 *
 * \return the allocated Osc_buffer
 */
Osc_Buffer alloc_osc_buffer(Uint16 buff_nb_samples);

/**
 * \fn int free_osc_buffer(Osc_Buffer osc_buff)
 * \brief Function to free memory of an oscillator audio buffer
 *
 * \param osc_buff The oscillator audio buffer
 *
 * \return 0
 */
int free_osc_buffer(Osc_Buffer osc_buff);


#endif //AUDIO_SYNTH_OSC_H
