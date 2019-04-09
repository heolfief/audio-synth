/**
 * \file audio_fx.h
 * \brief Audio effects functions definition.
 *
 *
 * Here are defined the audio effects functions
 */

#ifndef AUDIO_SYNTH_AUDIO_FX_H
#define AUDIO_SYNTH_AUDIO_FX_H

#include <SDL2/SDL_stdinc.h>
#include "../system/error_handler.h"
#include "../core/note/polyphony.h"
#include "biquad.h"

/**
 * \enum Filter_type
 * \brief various waveform types
 *
 * This enum defines the various waveform types : sine, square and triangle
 */
typedef enum
{
  LOWPASS,                  /*!< Lowpass filter */
  HIGHPASS,                 /*!< Highpass filter */
  BANDPASS,                 /*!< Bandpass filter */
  NOTCH,                    /*!< Notch filter */
} Filter_type;

/**
 * \struct Effect_core
 * \brief define an effect core
 *
 * An effect core contains all the objects needed for the effects like for example the filter coefficients
 */
typedef struct
{
  sf_biquad_state_st *filter_state;       /*!<the filter state (coefficients + old data) */
} Effect_core;

/**
 * \struct Effect_core
 * \brief define an effect core
 *
 * An effect core contains all the objects needed for the effects like for example the filter coefficients
 */
typedef struct
{
  Filter_type filter_type;                       /*!<the type of the filter */
  Uint16 cutoff_freq;                            /*!<the frequency cutoff of the filter */
  float resonance;                              /*!<the resonance of the filter */
} Filter_param;


/**
 * \fn int distortion(Audio_Buffer buff, Uint16 buffer_length, Uint8 dist_level, Uint8 wet)
 * \brief Function to apply distortion to an audio buffer
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param dist_level the distortion level in percents
 * \param wet the balance between dry(no effect) and wet(only effect) in percent
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int distortion(Audio_Buffer buff, Uint16 buffer_length, Uint8 dist_level, Uint8 wet);

/**
 * \fn int amp_mod(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, double mod_level)
 * \brief Function to apply amplitude modulation to an audio buffer
 *
 *  Volume is modulated by an LFO
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param freq the frequency of the modulation
 * \param mod_level the distortion level in percents
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int amp_mod(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, Uint8 mod_level);

/**
 * \fn int biquad(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, sf_biquad_state_st *state)
 * \brief Function to apply a biquad filter to an audio buffer
 *
 *  depending on the filter coefficients, could be either a lowpass, highpass or bandpass filter
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param state the sf_biquad_st object containing the filter coefficients
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int biquad(Audio_Buffer buff, Uint16 buffer_length, sf_biquad_state_st *state);

/**
 * \fn int compute_filter_coeffs(Sys_param *sys_param, sf_biquad_state_st *state)
 * \brief Function to compute the filter coefficients based on actual system parameters
 *
 * \param filter_param the filters parameters
 * \param sample_rate The sample rate of the system
 * \param state the sf_biquad_st object containing the filter coefficients
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int compute_filter_coeffs(Filter_param *filter_param, Uint32 sample_rate, sf_biquad_state_st *state);

/**
 * \fn Effect_core* alloc_effect_core()
 * \brief Function to allocate memory for an effect core
 *
 * \return the allocated Effect_core
 */
Effect_core* alloc_effect_core();

/**
 * \fn int free_osc_buffer(Osc_Buffer osc_buff)
 * \brief Function to free memory of an oscillator audio buffer
 *
 * \param ec The effect core
 *
 * \return 0
 */
int free_effect_core(Effect_core *ec);

#endif //AUDIO_SYNTH_AUDIO_FX_H
