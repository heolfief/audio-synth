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

int write_wav_file(int bufferLength, Audio_Buffer buffer, SNDFILE *sndFile);


int open_wav_file(const char *filePath, int sampleRate, SNDFILE *sndFile);

int close_wav_file(SNDFILE *sndFile);












#endif //AUDIO_SYNTH_WAV_H



