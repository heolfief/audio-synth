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
    Core *ac = NULL;

    assert_int_equal(init_core(NULL), -1);

    ac = (Core *) malloc(sizeof(Core));
    if (ac == NULL)
    {
        sys_print_error_test("Memory allocation error");
        return -1;
    }

    ac->sys_param = alloc_sys_param();
    if (ac->sys_param == NULL) return -1;
    ac->sys_param->sample_rate = TEST_SAMPLE_RATE;
    ac->sys_param->audio_buffer_length = TEST_AUDIO_BUFF_SIZE;

    if (init_core(ac))return -1;

    *state = ac;

    return 0;
}

int teardown_core(void **state)
{
    Core *ac = *state;

    assert_int_equal(quit_core(NULL), -1);

    free_sys_param(ac->sys_param);

    if (quit_core(ac))return -1;

    free(ac);

    return 0;
}

void test_master_audio_fill_buffer(void **state)
{
    Core *ac = *state;
    Envelope env = {.attack = 0, .decay =0, .sustain =1, .release =0};

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        osc_init_default_values(ac->note_array[i]->osc1, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
        osc_init_default_values(ac->note_array[i]->osc2, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
        osc_init_default_values(ac->note_array[i]->osc3, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);

        ac->note_array[i]->master_onoff = OFF;
        ac->note_array[i]->onoff = OFF;
        ac->note_array[i]->lifetime = 0;
        ac->note_array[i]->deathtime = 0;
        ac->sys_param->env->attack = env.attack;
        ac->sys_param->env->decay = env.decay;
        ac->sys_param->env->sustain = env.sustain;
        ac->sys_param->env->release = env.release;
    }

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

    // Normal behaviour test
    assert_int_equal(distortion(ac->master_audio, TEST_AUDIO_BUFF_SIZE, 0, 0), 0);

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
}