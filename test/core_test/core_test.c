/**
 * \file core_test.c
 * \brief Core test functions.
 *
 *
 * Here are implemented the test functions for audio core
 */

#include "core_test.h"

#define TEST_SAMPLE_RATE 48000
#define TEST_AUDIO_BUFF_SIZE 1024

int setup_core(void **state)
{
    Envelope env = {.attack = 0, .decay = 0, .sustain = 1, .release = 0};

    Core *ac = alloc_core(TEST_AUDIO_BUFF_SIZE);
    if (ac == NULL)
    {
        sys_print_error_test("Memory allocation error");
        return -1;
    }

    ac->sys_param->sample_rate = TEST_SAMPLE_RATE;

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        osc_init_default_values(ac->note_array[i]->osc1, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
        osc_init_default_values(ac->note_array[i]->osc2, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
        osc_init_default_values(ac->note_array[i]->osc3, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);

        ac->note_array[i]->master_onoff = OFF;
        ac->note_array[i]->onoff = OFF;
        ac->note_array[i]->lifetime = 0;
        ac->note_array[i]->deathtime = 0;
    }

    ac->sys_param->env->attack = env.attack;
    ac->sys_param->env->decay = env.decay;
    ac->sys_param->env->sustain = env.sustain;
    ac->sys_param->env->release = env.release;
    ac->sys_param->dist_param->wet=50;
    ac->sys_param->dist_param->dist_level=50;
    ac->sys_param->amp_mod_param->mod_level=50;
    ac->sys_param->amp_mod_param->freq=440;
    ac->sys_param->filter_param->resonance=20;
    ac->sys_param->filter_param->filter_type=LOWPASS;
    ac->sys_param->filter_param->cutoff_freq=440;


    *state = ac;

    return 0;
}

int teardown_core(void **state)
{
    Core *ac = *state;

    // Error handling behaviour test
    assert_int_equal(free_core(NULL), -1);

    if (free_core(ac))return -1;

    return 0;
}

void test_master_audio_fill_buffer(void **state)
{
    Core *ac = *state;

    // Error behaviour test
    assert_int_equal(master_audio_fill_buffer(NULL), -1);

    // Normal behaviour test
    assert_int_equal(master_audio_fill_buffer(*state), 0);

    // Error behaviour test
    assert_int_equal(synthesis_fill_buffer(NULL), -1);
}

void test_fx(void **state)
{
    Core *ac = *state;

    memset(ac->master_audio, 0, TEST_AUDIO_BUFF_SIZE);
    ac->effect_core->filter_state->a1 = 0;
    ac->effect_core->filter_state->a2 = 0;
    ac->effect_core->filter_state->b0 = 0;
    ac->effect_core->filter_state->b1 = 0;
    ac->effect_core->filter_state->b0 = 0;
    ac->effect_core->filter_state->xn1.L = 0;
    ac->effect_core->filter_state->xn1.R = 0;
    ac->effect_core->filter_state->xn2.L = 0;
    ac->effect_core->filter_state->xn2.R = 0;
    ac->effect_core->filter_state->yn1.L = 0;
    ac->effect_core->filter_state->yn1.R = 0;
    ac->effect_core->filter_state->yn2.L = 0;
    ac->effect_core->filter_state->yn2.R = 0;

    /*
     * MASTER EFFECTS
     */
    // Error behaviour test
    assert_int_equal(master_effects(NULL), -1);

    // Normal behaviour test
    assert_int_equal(master_effects(ac), 0);


    /*
     * DISTORTION
     */
    // Error behaviour test
    assert_int_equal(distortion(NULL, TEST_AUDIO_BUFF_SIZE, 0, 0), -1);

    for (Uint16 sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample)
    {
        ac->master_audio[sample] = 5;
    }

    // Normal behaviour test
    assert_int_equal(distortion(ac->master_audio, TEST_AUDIO_BUFF_SIZE, 50, 50), 0);

    for (Uint16 sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample)
    {
        ac->master_audio[sample] = -5;
    }

    // Normal behaviour test
    assert_int_equal(distortion(ac->master_audio, TEST_AUDIO_BUFF_SIZE, 50, 50), 0);

    // Out of range parameters behaviour test
    assert_int_equal(distortion(ac->master_audio, TEST_AUDIO_BUFF_SIZE, 101, 0), -1);
    assert_int_equal(distortion(ac->master_audio, TEST_AUDIO_BUFF_SIZE, 5, 101), -1);
    assert_int_equal(distortion(ac->master_audio, TEST_AUDIO_BUFF_SIZE, 210, 158), -1);


    /*
     * AMPLITUDE MODULATION
     */
    // Error behaviour test
    assert_int_equal(amp_mod(NULL, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, 0), -1);

    // Normal behaviour test
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, 0), 0);

    // Out of range parameters behaviour test
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, -5, 0), -1);
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, 101), -1);
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, -50, 185), -1);


    /*
    * FILTER
    */
    ac->sys_param->filter_param->cutoff_freq = 440;
    ac->sys_param->filter_param->resonance = 10;

    // Error behaviour test
    assert_int_equal(compute_filter_coeffs(ac->sys_param->filter_param, ac->sys_param->sample_rate, NULL), -1);
    assert_int_equal(compute_filter_coeffs(NULL, ac->sys_param->sample_rate, ac->effect_core->filter_state), -1);
    assert_int_equal(biquad(NULL, TEST_AUDIO_BUFF_SIZE, ac->effect_core->filter_state), -1);
    assert_int_equal(biquad(ac->master_audio, TEST_AUDIO_BUFF_SIZE, NULL), -1);
    assert_int_equal(biquad(ac->master_audio, 0, ac->effect_core->filter_state), -1);

    for (Filter_type filter_type = LOWPASS; filter_type <= NOTCH; ++filter_type)
    {
        ac->sys_param->filter_param->filter_type = filter_type;
        assert_int_equal(compute_filter_coeffs(ac->sys_param->filter_param, ac->sys_param->sample_rate, ac->effect_core->filter_state), 0);

        // Normal behaviour test
        assert_int_equal(biquad(ac->master_audio, TEST_AUDIO_BUFF_SIZE, ac->effect_core->filter_state), 0);
    }
    ac->sys_param->filter_param->filter_type = 120; // unknown filter type
    assert_int_equal(compute_filter_coeffs(ac->sys_param->filter_param, ac->sys_param->sample_rate, ac->effect_core->filter_state), -1);
}