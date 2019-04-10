/**
 * \file sys_param.h
 * \brief System parameters data structure and function definition.
 *
 *
 * Here are defined the data structure of the system parameters, and the related functions.
 * Theses parameters are meant to be changed by the GUI.
 */

#ifndef AUDIO_SYNTH_SYS_PARAM_H
#define AUDIO_SYNTH_SYS_PARAM_H

#include <SDL2/SDL_stdinc.h>
#include "../core/note/polyphony.h"
#include "../audio_fx/audio_fx.h"
#include "../system/error_handler.h"

/**
 * \struct Sys_param
 * \brief define the system parameters, meant to be changed by the GUI
 *
 *
 */
typedef struct
{
  Uint16 sample_rate;                            /*!<the sample rate of the audio system */
  Uint16 audio_buffer_length;                    /*!<the length of the audio buffer of the audio system */
  Oscillator *osc1;                              /*!<the first oscillator */
  Oscillator *osc2;                              /*!<the second oscillator */
  Oscillator *osc3;                              /*!<the third oscillator */
  Envelope *env;                                 /*!<the sound envelope */
  Amp_mod_param *amp_mod_param;                  /*!<the amplitude modulation parameters */
  Distortion_param *dist_param;                  /*!<the distortion parameters */
  Filter_param *filter_param;                    /*!<the filter parameter */
} Sys_param;

/**
 * \fn int copy_osc_sys_param_to_notes_osc(Sys_param *sys_param_to_copy, Polyphony p[])
 * \brief Function to copy oscillator settings to notes oscillators settings
 *
 * \param sys_param_to_copy The system parameters to copy to the note oscillators
 * \param p The Polyphony array to copy settings to
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int copy_osc_sys_param_to_notes_osc(Sys_param *sys_param_to_copy, Polyphony p[]);

/**
 * \fn Sys_param *alloc_sys_param()
 * \brief Function to allocate memory for system parameters
 *
 * \return the allocated Sys_param
 */
Sys_param *alloc_sys_param();

/**
 * \fn int free_sys_param(Sys_param *sys_param_to_free)
 * \brief Function to free memory of system parameters
 *
 * \param sys_param_to_free The system parameters to free
 *
 * \return 0
 */
int free_sys_param(Sys_param *sys_param_to_free);

#endif //AUDIO_SYNTH_SYS_PARAM_H
