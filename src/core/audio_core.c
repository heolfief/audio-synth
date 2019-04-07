/**
 * \file audio_core.c
 * \brief Audio core and functions implementation.
 *
 *
 * Here are implemented the audio core, which contains sound synthesis and effects
 */

#include "audio_core.h"
#include "../audio_fx/audio_fx.h"


int init_core(Core* ac)
{
    int ret = 0;

    // Core memory allocation
    ac->note_array = alloc_polyphony(ac->sys_param->audio_buffer_length);
    if(ac->note_array == NULL) ret = -1;

    ac->master_audio = alloc_audio_buffer(ac->sys_param->audio_buffer_length);
    if(ac->master_audio == NULL) ret = -1;

    return ret;
}

int quit_core(Core* ac)
{
    if(free_polyphony(ac->note_array))return -1;
    if(free_audio_buffer(ac->master_audio))return -1;

    return 0;
}

int synthesis_fill_buffer(Core* ac)
{
    return polyphony_fill_buffer(ac->master_audio, ac->note_array, ac->sys_param->audio_buffer_length, ac->sys_param->env, ac->sys_param->sample_rate, ac->phase);
}

int master_audio_fill_buffer(Core* ac)
{
    int ret;

    ret = synthesis_fill_buffer(ac);
    if (ret == -1) return -1;

    ret = master_effects(ac);
    if (ret == -1) return -1;

    return 0;
}

int master_effects(Core* ac)
{
    double headroom = 0.8;

    // Leave headroom
    for(Uint16 sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample) ac->master_audio[sample] = (Sint16)(headroom*ac->master_audio[sample]);

    // Apply each effect to master audio buffer
    if(distortion(ac->master_audio,ac->sys_param->audio_buffer_length,80,0))return -1;

    if(amp_mod(ac->master_audio,ac->sys_param->audio_buffer_length,ac->sys_param->sample_rate,15,50))return -1;

    return 0;
}