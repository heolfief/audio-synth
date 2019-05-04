/**
 * \file audio_core.c
 * \brief Audio core and functions implementation.
 *
 *
 * Here are implemented the audio core, which contains sound synthesis and effects
 */

#include "audio_core.h"

Core *alloc_core(Uint16 buffer_length)
{
    Core *ac = (Core *) malloc(sizeof(Core));
    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return NULL;
    }

    // Core memory allocation
    ac->sys_param = alloc_sys_param();
    if (ac->sys_param == NULL) return NULL;
    ac->sys_param->audio_buffer_length = buffer_length;
    ac->sys_param->master_volume = 100;
    ac->sys_param->master_FX_onoff = ON;

    ac->note_array = alloc_polyphony(buffer_length);
    if (ac->note_array == NULL) return NULL;

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        ac->note_array[i]->onoff = OFF;
        ac->note_array[i]->master_onoff = OFF;
        ac->note_array[i]->midi_id = 0;
        ac->note_array[i]->freq = 0;
        ac->note_array[i]->velocity_amp = 0;
        ac->note_array[i]->env_amp = 0;
        ac->note_array[i]->deathtime = 0;
        ac->note_array[i]->lifetime = 0;
    }

    ac->master_audio = alloc_audio_buffer(buffer_length);
    if (ac->master_audio == NULL) return NULL;

    ac->average_audio_level = alloc_audio_buffer(buffer_length);
    if (ac->average_audio_level == NULL) return NULL;

    ac->effect_core = alloc_effect_core();
    if (ac->effect_core == NULL) return NULL;

    return ac;
}

int free_core(Core *ac)
{
    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    if (free_sys_param(ac->sys_param))return -1;
    if (free_polyphony(ac->note_array))return -1;
    if (free_audio_buffer(ac->master_audio))return -1;
    if (free_audio_buffer(ac->average_audio_level))return -1;
    if (free_effect_core(ac->effect_core))return -1;

    free(ac);

    return 0;
}

int synthesis_fill_buffer(Core *ac)
{
    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    if (polyphony_fill_buffer(ac->master_audio, ac->note_array, ac->sys_param->audio_buffer_length, ac->sys_param->env, ac->sys_param->sample_rate, ac->phase))return -1;

    for (int sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample)
    {
        ac->average_audio_level[sample] = moving_average(ac->master_audio[sample]);
    }

    return 0;
}

int master_audio_fill_buffer(Core *ac)
{
    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    // Soud synthesis
    if (synthesis_fill_buffer(ac))return -1;

    // Apply effects if master FX switch is on
    if (ac->sys_param->master_FX_onoff == ON)
    {
        if (master_effects(ac))return -1;
    }

    // Apply master volume
    for (Uint16 sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample)
    {
        ac->master_audio[sample] =
            (Sint16) ((double) ac->master_audio[sample] * ((double) ac->sys_param->master_volume / 100.0));
    }

    return 0;
}

int master_effects(Core *ac)
{
    double headroom = 0.8;

    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    // Leave headroom
    for (Uint16 sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample)
    {
        ac->master_audio[sample] = (Sint16) (headroom * ac->master_audio[sample]);
    }


    /*
     * Apply each effect to master audio buffer
     */


    if (ac->sys_param->dist_param->onoff == ON)
    {
        if (distortion(ac->master_audio, ac->sys_param->audio_buffer_length, ac->sys_param->dist_param->dist_level, ac->sys_param->dist_param->wet))return -1;
    }

    if (ac->sys_param->delay_param->onoff == ON)
    {
        if (delay(ac->master_audio, ac->sys_param->audio_buffer_length, ac->sys_param->sample_rate, ac->sys_param->delay_param->delay, ac->sys_param->delay_param->feedback))return -1;
    }

    if (ac->sys_param->amp_mod_param->onoff == ON)
    {
        if (amp_mod(ac->master_audio, ac->sys_param->audio_buffer_length, ac->sys_param->sample_rate, ac->sys_param->amp_mod_param->freq, ac->sys_param->amp_mod_param->wave, ac->sys_param->amp_mod_param->duty, ac->sys_param->amp_mod_param->mod_level))return -1;
    }

    if (ac->sys_param->flanger_param->onoff == ON)
    {
        if (flanger(ac->master_audio, ac->sys_param->audio_buffer_length, ac->sys_param->sample_rate, ac->sys_param->flanger_param->lfo_freq, ac->sys_param->flanger_param->delay, ac->sys_param->flanger_param->lfo_range, ac->sys_param->flanger_param->depth, ac->sys_param->flanger_param->lfo_wave))return -1;
    }

    if (ac->sys_param->lfo_filter_param->onoff == ON)
    {
        if (lfo_filter(ac->master_audio, ac->sys_param->audio_buffer_length, ac->sys_param->sample_rate, ac->sys_param->lfo_filter_param->filter_type, ac->sys_param->lfo_filter_param->filter_freq, ac->sys_param->lfo_filter_param->lfo_freq, ac->sys_param->lfo_filter_param->resonance, ac->sys_param->lfo_filter_param->wave, ac->sys_param->lfo_filter_param->duty, ac->sys_param->lfo_filter_param->filter_excursion))return -1;
    }

    if (ac->sys_param->filter_param->onoff == ON)
    {
        if (biquad(ac->master_audio, ac->sys_param->audio_buffer_length, ac->effect_core->filter_state))return -1;
    }

    return 0;
}

Sint16 moving_average(Sint16 sample)
{
    Uint64 mean = 0;
    static Sint16 sample_array[512];
    static Uint32 cursor;

    sample_array[cursor++] = sample;
    cursor &= 0x1FFu;                 // Perform the same as "cursor = cursor % 512;" but speed is highly greater

    for (int i = 0; i < 512; ++i)
    {
        mean += abs(sample_array[i]);
    }

    mean = mean >> 10u;  // same as "mean / 512"

    return mean;
}