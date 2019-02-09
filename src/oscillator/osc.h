/**
 * \file osc.c
 * \brief Oscillator data structure and function definition.
 *
 * Programme de test pour l'objet de gestion des chaînes de caractères Str_t.
 *
 */

#ifndef AUDIO_SYNTH_OSC_H
#define AUDIO_SYNTH_OSC_H

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
 * An oscillator is defined with : wave, frequency, amplitude, detune
 */
typedef struct{
    Waveform wave;       /*!<the waveform type */
    Uint16 freq;         /*!<the frequency */
    Uint16 amp;          /*!<the amplitude */
    Sint8 detune;        /*!<the detune in number of notes */
}Oscillator;

#endif //AUDIO_SYNTH_OSC_H
