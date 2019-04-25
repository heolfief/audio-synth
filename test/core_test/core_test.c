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

    ac->sys_param->dist_param->onoff = ON;
    ac->sys_param->dist_param->wet = 50;
    ac->sys_param->dist_param->dist_level = 50;

    ac->sys_param->amp_mod_param->onoff = ON;
    ac->sys_param->amp_mod_param->mod_level = 50;
    ac->sys_param->amp_mod_param->freq = 440;
    ac->sys_param->amp_mod_param->wave = SIN;
    ac->sys_param->amp_mod_param->duty = 50;

    ac->sys_param->filter_param->onoff = ON;
    ac->sys_param->filter_param->resonance = 20;
    ac->sys_param->filter_param->filter_type = LOWPASS;
    ac->sys_param->filter_param->cutoff_freq = 440;

    ac->sys_param->flanger_param->onoff = ON;
    ac->sys_param->flanger_param->lfo_wave = SIN;
    ac->sys_param->flanger_param->lfo_freq = 1;
    ac->sys_param->flanger_param->lfo_range = 100;
    ac->sys_param->flanger_param->delay = 2;
    ac->sys_param->flanger_param->depth = 100;

    ac->sys_param->delay_param->onoff = ON;
    ac->sys_param->delay_param->delay = 250;
    ac->sys_param->delay_param->feedback = 50;

    ac->sys_param->lfo_filter_param->onoff = ON;
    ac->sys_param->lfo_filter_param->filter_excursion = 100;
    ac->sys_param->lfo_filter_param->duty = 50;
    ac->sys_param->lfo_filter_param->wave = SIN;
    ac->sys_param->lfo_filter_param->resonance = 2;
    ac->sys_param->lfo_filter_param->lfo_freq = 2;
    ac->sys_param->lfo_filter_param->filter_freq = 200;
    ac->sys_param->lfo_filter_param->filter_type = LOWPASS;

    memset(ac->master_audio, 0, TEST_AUDIO_BUFF_SIZE);
    ac->effect_core->filter_state->a1 = 0;
    ac->effect_core->filter_state->a2 = 0;
    ac->effect_core->filter_state->b0 = 0;
    ac->effect_core->filter_state->b1 = 0;
    ac->effect_core->filter_state->b2 = 0;
    ac->effect_core->filter_state->xn1.L = 0;
    ac->effect_core->filter_state->xn1.R = 0;
    ac->effect_core->filter_state->xn2.L = 0;
    ac->effect_core->filter_state->xn2.R = 0;
    ac->effect_core->filter_state->yn1.L = 0;
    ac->effect_core->filter_state->yn1.R = 0;
    ac->effect_core->filter_state->yn2.L = 0;
    ac->effect_core->filter_state->yn2.R = 0;

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
    assert_int_equal(master_audio_fill_buffer(ac), 0);


    // Error behaviour test
    assert_int_equal(synthesis_fill_buffer(NULL), -1);
}

void test_fx(void **state)
{
    Core *ac = *state;

    // Error behaviour test
    assert_int_equal(master_effects(NULL), -1);


    // Normal behaviour test
    assert_int_equal(master_effects(ac), 0);
}

void test_flanger(void **state)
{
    Core *ac = *state;

    // Error behaviour test
    assert_int_equal(flanger(NULL, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 1, 1, 100, 100, SIN), -1);

    for (Uint16 sample = 0; sample < ac->sys_param->audio_buffer_length; ++sample)
    {
        ac->master_audio[sample] = -5;
    }

    // Normal behaviour test
    assert_int_equal(flanger(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 1, 1, 100, 100, SIN), 0);

    // Out of range parameters behaviour test
    assert_int_equal(flanger(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, -5, 1, 100, 100, SIN), -1);
    assert_int_equal(flanger(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 5, 5000, 100, 100, SIN), -1);
    assert_int_equal(flanger(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 5, 1, 101, 100, SIN), -1);
    assert_int_equal(flanger(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 5, 1, 100, 101, SIN), -1);
    assert_int_equal(flanger(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 5, 1, 100, 100, 9), -1);
}

void test_distortion(void **state)
{
    Core *ac = *state;

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
}

void test_amp_mod(void **state)
{
    Core *ac = *state;

    // Error behaviour test
    assert_int_equal(amp_mod(NULL, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, SIN, 50, 0), -1);

    // Normal behaviour test
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, SIN, 50, 0), 0);

    // Out of range parameters behaviour test
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, -5, SIN, 50, 0), -1);
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, SIN, 50, 101), -1);
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, -50, SIN, 50, 185), -1);
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, 45, 50, 0), -1);
    assert_int_equal(amp_mod(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0, SIN, 102, 0), -1);
}

void test_filter(void **state)
{
    Core *ac = *state;

    ac->sys_param->filter_param->
        cutoff_freq = 440;
    ac->sys_param->filter_param->
        resonance = 10;

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

void test_lfo_filter(void **state)
{
    Core *ac = *state;

    // Error behaviour test
    assert_int_equal(lfo_filter(NULL, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, LOWPASS, 1000, 2.5, 10, SIN, 50, 50), -1);
    assert_int_equal(lfo_filter(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 10, 1000, 2.5, 10, SIN, 50, 50), -1);
    assert_int_equal(lfo_filter(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, LOWPASS, 1000, 2.5, 10, 16, 50, 50), -1);
    assert_int_equal(lfo_filter(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, LOWPASS, 1000, -35, 10, SIN, 50, 50), -1);

    // Normal behaviour test
    assert_int_equal(lfo_filter(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, LOWPASS, 1000, 5, 10, SIN, 50, 50), 0);
}

void test_delay(void **state)
{
    Core *ac = *state;

    // Error behaviour test
    assert_int_equal(delay(NULL, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 100, 50), -1);
    assert_int_equal(delay(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 500000, 50), -1);
    assert_int_equal(delay(ac->master_audio, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 100, 101), -1);

    // Normal behaviour test
    assert_int_equal(biquad(ac->master_audio, TEST_AUDIO_BUFF_SIZE, ac->effect_core->filter_state), 0);
}