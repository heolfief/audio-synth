/**
 * \file audio_core.c
 * \brief Audio core and functions implementation.
 *
 *
 * Here are implemented the audio core, which contains sound synthesis and effects
 */

#include "audio_core.h"

// Global parameters defined in main.c
Polyphony *note_array;
Audio_Buffer master_audio;
extern Sys_param* sys_param;

int quit_core()
{
    int ret;

    ret = free_polyphony(note_array);
    ret += free_audio_buffer(master_audio);

    return ret == 0 ? 0 : -1;
}

int init_core()
{
    int ret = 0;

    // Core memory allocation
    note_array = alloc_polyphony(sys_param->audio_buffer_length);
    if(note_array == NULL) ret = -1;

    master_audio = alloc_audio_buffer(sys_param->audio_buffer_length);
    if(master_audio == NULL) ret = -1;

    return ret;
}

int synthesis_fill_buffer(Uint64 phase)
{
    return polyphony_fill_buffer(master_audio, note_array, sys_param->audio_buffer_length, sys_param->env, sys_param->sample_rate, phase);
}