/**
 * \file wav.h
 * \brief WAV recording functions definition.
 *
 *
 * Here are defined the WAV Files recording related audio functions
 */

#ifndef AUDIO_SYNTH_WAV_H
#define AUDIO_SYNTH_WAV_H

#include <SDL2/SDL.h>
#include <sndfile.h>
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "../core/audio_core.h"

/**
 *  \fn int write_wav_file(int bufferLength, Audio_Buffer buffer, SNDFILE *sndFile)
 *  \brief This function is called when the recording is on inside the callback of the core.
 *
 *  \param bufferLength an int indicating the length of the buffer
 *  \param buffer A pointer to the audio data buffer.
 *  \param sndFile    The opened sound file where the data will be recorded.
 *
 *  \return 0 if all went well
 */
int write_wav_file(int bufferLength, Audio_Buffer buffer, SNDFILE *sndFile);

/**
 *  \fn int open_wav_file(const char *filePath, Core *ac);
 *  \brief This function is called at the start of the recording to prepare the file.
 *
 *  \param filePath is a char giving us the path of the file to record
 *  \param ac a pointer to the audio core
 *
 *  \return 0 if all went well
 */
int open_wav_file(const char *filePath, Core *ac);

/**
 *  \fn int close_wav_file(SNDFILE *sndFile);
 *  \brief This function is called at the end of the recording to close the files.
 *
 *  \param sndFile is a pointer to the sound file that needs closing
 *
 *  \return 0 if all went well
 */
int close_wav_file(SNDFILE *sndFile);

#endif //AUDIO_SYNTH_WAV_H



