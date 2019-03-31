/**
 * \file audio_core.h
 * \brief Audio core functions definition.
 *
 *
 * Here are defined the audio core, which contains sound synthesis and effects
 */

#ifndef AUDIO_SYNTH_AUDIO_CORE_H
#define AUDIO_SYNTH_AUDIO_CORE_H

#include <SDL2/SDL_stdinc.h>
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "../audio/audio.h"
#include "note/polyphony.h"


/**
 * \fn int init_core()
 * \brief Initialize audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int init_core();

/**
 * \fn int quit_core()
 * \brief Function to quit and desallocate audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int quit_core();

/**
 * \fn int synthesis_fill_buffer()
 * \brief Function to fill master audio buffer with audio synthesis
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int synthesis_fill_buffer();

/**
 * \fn int master_effects()
 * \brief Function to apply effects to master audio buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int master_effects();

#endif //AUDIO_SYNTH_AUDIO_CORE_H
