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
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"

/**
 * \fn int distortion(Audio_Buffer buff, Uint16 buffer_length, Uint8 dist_level, Uint8 wet)
 * \brief Function to apply distortion to an audio buffer
 *
 * \param buff the Audio_Buffer object to apply distortion to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param dist_level the distortion level in percents
 * \param wet the balance bettwen dry(no effect) and wet(only effect) in percent
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int distortion(Audio_Buffer buff, Uint16 buffer_length, Uint8 dist_level, Uint8 wet);

#endif //AUDIO_SYNTH_AUDIO_FX_H
