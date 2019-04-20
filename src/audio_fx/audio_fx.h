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
#include "ext_effects/biquad.h"

#define MAX_SAMPLE_DELAY_LINE 16384
#define LFO_FILTER_SAMPLE_INCREMENT 64  // Needs to be power of two, this is the equivalent to the refresh rate in samples of the filter LFO

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
 * \struct Filter_param
 * \brief define the filter parameters
 *
 */
typedef struct
{
  OnOff onoff;                            /*!<master on off of the effect */
  Filter_type filter_type;                       /*!<the type of the filter */
  Uint16 cutoff_freq;                            /*!<the frequency cutoff of the filter */
  double resonance;                              /*!<the resonance of the filter */
} Filter_param;

/**
 * \struct Distortion_param
 * \brief define the distortion parameters
 *
 */
typedef struct
{
  OnOff onoff;                            /*!<master on off of the effect */
  Uint8 dist_level;                       /*!<the distortion level in percent */
  Uint8 wet;                              /*!<the balance between dry(no effect) and wet(only effect) in percent */
} Distortion_param;

/**
 * \struct Lfo_filter_param
 * \brief define the LFO modulated filter parameters
 *
 */
typedef struct
{
  OnOff onoff;                            /*!<master on off of the effect */
  Filter_type filter_type;                /*!<the filter type (LOWPASS, HIGHPASS, BANDPASS, NOTCH */
  Uint16 filter_freq;                     /*!<the center frequency of the filter */
  double lfo_freq;                        /*!<the frequency of the modulation */
  double resonance;                       /*!<the resonance of the filter */
  Waveform wave;                          /*!<the waveform of the LFO */
  Uint8 duty;                             /*!<the duty cycle of the LFO */
  Uint16 filter_excursion;                /*!<the excursion of the modulated filter in Hz */
} Lfo_filter_param;

/**
 * \struct Amp_mod_param
 * \brief define the amplitude modulation parameters
 *
 */
typedef struct
{
  OnOff onoff;                            /*!<master on off of the effect */
  Uint8 mod_level;                        /*!<the depth or effect level in percents */
  double freq;                            /*!<the frequency of the modulation */
  Waveform wave;                          /*!<the waveform of the LFO */
  Uint8 duty;                             /*!<the duty cycle of the LFO */
} Amp_mod_param;

/**
 * \struct Flanger_param
 * \brief define the flanger parameters
 *
 */
typedef struct
{
  OnOff onoff;                            /*!<master on off of the effect */
  Waveform lfo_wave;                      /*!<the waveform of the LFO */
  double lfo_freq;                        /*!<the frequency of the LFO */
  Uint8 lfo_range;                        /*!<the range of the LFO in percents */
  double delay;                           /*!<the delay time in milliseconds */
  Uint8 depth;                            /*!<the depth of the effect in percent */
} Flanger_param;

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
 * \fn int amp_mod(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, Waveform wave, Uint8 duty, Uint8 mod_level)
 * \brief Function to apply amplitude modulation to an audio buffer
 *
 *  Volume is modulated by an LFO
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param freq the frequency of the modulation
 * \param wave the waveform type of the LFO
 * \param duty the duty cycle of the waveform in percents
 * \param mod_level the depth or effect level in percents
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int amp_mod(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, Waveform wave, Uint8 duty, Uint8 mod_level);

/**
 * \fn int flanger(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, double delay, Uint8 lfo_range, Uint8 depth, Waveform wave)
 * \brief Function to apply a flanger effect (delay effect) to an audio buffer
 *
 *  Delay is modulated by an LFO
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param freq the frequency of the modulation
 * \param delay the delay value in milliseconds used for the flanging effect
 * \param lfo_range the range of the low frequency oscillator in percents
 * \param depth the depth of the effect in percents
 * \param wave the waveform type of the LFO
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int flanger(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, double freq, double delay, Uint8 lfo_range, Uint8 depth, Waveform wave);

/**
 * \fn int lfo_filter(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, Filter_type filter_type, Uint16 filter_freq, double lfo_freq, double resonance, Waveform wave, Uint8 duty, Uint16 filter_excursion)
 * \brief Function to apply a biquad filter to an audio buffer, moded by an LFO
 *
 *  depending on the filter coefficients, could be either a lowpass, highpass or bandpass filter
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param filter_type the filter type (LOWPASS, HIGHPASS, BANDPASS, NOTCH)
 * \param filter_freq the center frequency of the filter in Hz
 * \param lfo_freq the frequency of the modulation
 * \param resonance the resonance of the filter
 * \param wave the waveform type of the LFO
 * \param duty the duty cycle of the waveform in percents
 * \param filter_excursion the filter excursion in Hz
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int lfo_filter(Audio_Buffer buff, Uint16 buffer_length, Uint32 sample_rate, Filter_type filter_type, Uint16 filter_freq, double lfo_freq, double resonance, Waveform wave, Uint8 duty, Uint16 filter_excursion);

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
Effect_core *alloc_effect_core();

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
