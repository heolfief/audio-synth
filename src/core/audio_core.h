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
#include "note/polyphony.h"
#include "../audio_fx/audio_fx.h"

/**
 * \struct Core
 * \brief define an audio core
 *
 * An audio core is consisted of a buffer containing final audio data to be played by the soundcard, the system parameters,
 * the polyphony array of the system and the phase of the system.
 */
typedef struct
{
  Polyphony *note_array;       /*!<the polyphony array of the system */
  Audio_Buffer master_audio;   /*!<the master audio buffer */
  Sys_param *sys_param;        /*!<the system parameters */
  Uint64 phase;                /*!<the phase of the oscillators */
  Effect_core *effect_core;     /*!<the structure containing effect related objects */
} Core;

/**
 * \fn Core alloc_core()
 * \brief Allocate an audio core
 *
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 *
 * \return The allocated Core
 */
Core* alloc_core(Uint16 buffer_length);

/**
 * \fn int free_core(Core* ac)
 * \brief Function to free audio core memory
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int free_core(Core *ac);

/**
 * \fn int synthesis_fill_buffer(Core* ac)
 * \brief Function to fill master audio buffer with audio synthesis
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int synthesis_fill_buffer(Core *ac);

/**
 * \fn int master_audio_fill_buffer(Core* ac)
 * \brief Function to fill master audio buffer with audio synthesis and effects
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int master_audio_fill_buffer(Core *ac);

/**
 * \fn int master_effects(Core* ac)
 * \brief Function to apply effects to master audio buffer
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int master_effects(Core *ac);

#endif //AUDIO_SYNTH_AUDIO_CORE_H
