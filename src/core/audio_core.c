/**
 * \file audio_core.c
 * \brief Audio core and functions implementation.
 *
 *
 * Here are implemented the audio core, which contains sound synthesis and effects
 */

#include "audio_core.h"
#include "../audio_fx/audio_fx.h"

// Global parameters defined in main.c and audio.c
Polyphony *note_array;
Audio_Buffer master_audio;
extern Sys_param* sys_param;
extern Uint64 phase;

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

int quit_core()
{
    int ret;

    ret = free_polyphony(note_array);
    ret += free_audio_buffer(master_audio);

    return ret == 0 ? 0 : -1;
}

int synthesis_fill_buffer()
{
    return polyphony_fill_buffer(master_audio, note_array, sys_param->audio_buffer_length, sys_param->env, sys_param->sample_rate, phase);
}

int master_audio_fill_buffer()
{
    int ret;

    ret = synthesis_fill_buffer();
    if (ret == -1) return -1;

    ret = master_effects();
    if (ret == -1) return -1;

    return 0;
}

int master_effects()
{
    double headroom = 0.8;

    // Leave headroom
    for(Uint16 sample = 0; sample < sys_param->audio_buffer_length; ++sample) master_audio[sample] = (Sint16)(headroom*master_audio[sample]);

    // Apply each effect to master audio buffer
    if(distortion(master_audio,sys_param->audio_buffer_length,80,0))return -1;

    if(amp_mod(master_audio,sys_param->audio_buffer_length,sys_param->sample_rate,15,50))return -1;

    return 0;
}