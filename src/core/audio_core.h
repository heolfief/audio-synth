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
 * \fn
 * \brief
 *
 * \param param description
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
 * \fn int synthesis_fill_buffer(Uint64 phase)
 * \brief Function Fill master audio buffer with audio synthesis
 *
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int synthesis_fill_buffer(Uint64 phase);


#endif //AUDIO_SYNTH_AUDIO_CORE_H
