/**
 * \file audio.h
 * \brief Audio (SDL related) functions definition.
 *
 *
 * Here are defined the SDL related audio functions
 */

#ifndef AUDIO_SYNTH_AUDIO_H
#define AUDIO_SYNTH_AUDIO_H

#include <SDL2/SDL.h>
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "../core/audio_core.h"

/**
 *  \fn void func_callback(void *unused, Uint8 *stream, int len)
 *  \brief This function is called when the audio device needs more data.
 *
 *  \param userdata An application-specific parameter saved in
 *                  the SDL_AudioSpec structure
 *                  Here Core structure is passed
 *  \param stream A pointer to the audio data buffer.
 *  \param len    The length of that buffer in bytes.
 *
 *  Once the callback returns, the buffer will no longer be valid.
 *  Stereo samples are stored in a LRLRLR ordering.
 *
 *  You can choose to avoid callbacks and use SDL_QueueAudio() instead, if
 *  you like. Just open your audio device with a NULL callback.
 */
void func_callback(void *userdata, Uint8 *stream, int len);

/**
 * \fn int set_audio_spec(SDL_AudioSpec *as, const Core* ac)
 * \brief Function to setup SDL audio spec
 *
 * This function sets the SDL audio spec to MONO, signed 16bits (little indian) audio sample data
 * with sample rate and buffer length as set in system parameters
 *
 * \param as The SDL_AudioSpec structure
 * \param ac The audio core structure of the system

 *
 * \return 0 if everything went OK, -1 otherwise
 */
int set_audio_spec(SDL_AudioSpec *as, const Core* ac);

#endif //AUDIO_SYNTH_AUDIO_H
