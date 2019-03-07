/**
 * \file note_test.c
 * \brief Note test functions.
 *
 *
 * Here are implemented the test functions for the note
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "note_test.h"

#define TEST_SAMPLE_RATE 48000
#define TEST_AUDIO_BUFF_SIZE 1024

int setup_note(void **state)
{
    Note *n = NULL;
    n = alloc_note(TEST_AUDIO_BUFF_SIZE);
    if(n == NULL)
    {
        return -1;
    }

    osc_init_default_values(n->osc1,TEST_AUDIO_BUFF_SIZE,TEST_SAMPLE_RATE);
    osc_init_default_values(n->osc2,TEST_AUDIO_BUFF_SIZE,TEST_SAMPLE_RATE);
    osc_init_default_values(n->osc3,TEST_AUDIO_BUFF_SIZE,TEST_SAMPLE_RATE);

    *state = n;
    return 0;
}

int teardown_note(void **state)
{
    free_note(*state);
    return 0;
}

void test_note_on(void **state)
{
    Note *n = *state;

    n->onoff = OFF;

    int return_value = note_on(n);

    assert_int_equal(return_value, 0);
    assert_int_equal(n->onoff, ON);

    return_value = note_on(NULL);

    assert_int_equal(return_value, -1);
}

void test_note_off(void **state)
{
    Note *n = *state;

    n->onoff = ON;
    n->lifetime = 50;
    n->deathtime = 0;

    int return_value = note_off(n);

    assert_int_equal(return_value, 0);
    assert_int_equal(n->onoff, OFF);
    assert_int_equal(n->deathtime, 50);

    return_value = note_off(NULL);

    assert_int_equal(return_value, -1);
}

void test_update_envelope(void **state)
{
    Note *n = *state;
    Envelope env = {.attack = 4, .decay =2, .sustain =0.5, .release =2};
    int return_value=-1;

    double env_known_values[15]= {0,0.25,0.5,0.75,1,0.75,0.5,0.5,0.5,0.5,0.5,0.25,0,0,0};

    n->lifetime = 0;
    n->deathtime=0;
    n->master_onoff = OFF;
    n->velocity_amp = 1;
    note_on(n);

    for(int sample = 0; sample < 15; ++sample)
    {
        return_value = update_envelope(n,&env);
        assert_int_equal(return_value, 0);

        if(sample == 10)note_off(n);

        assert_int_equal(n->env_amp*100, env_known_values[sample]*100);
        n->lifetime++;
    }

    // Out of range test
    env.sustain = -0.2;
    return_value = update_envelope(n,&env);
    assert_int_equal(return_value, -1);

    // Out of range test
    env.sustain = 1.2;
    return_value = update_envelope(n,&env);
    assert_int_equal(return_value, -1);
}

void test_note_fill_buffer(void **state)
{
    Note *n = *state;
    Envelope env = {.attack = 4, .decay =2, .sustain =0.5, .release =2};
    int return_value=0;

    // NULL test
    return_value = note_fill_buffer(NULL, TEST_AUDIO_BUFF_SIZE, &env, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, -1);

    n->lifetime = 0;
    note_on(n);

    return_value = note_fill_buffer(n, TEST_AUDIO_BUFF_SIZE, &env, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, 0);
    assert_int_equal(n->lifetime, TEST_AUDIO_BUFF_SIZE-1);

}