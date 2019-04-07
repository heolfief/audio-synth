/**
 * \file sys_param_test.c
 * \brief System parameters test functions.
 *
 *
 * Here are implemented the test functions for system parameters
 */

#include "sys_param_test.h"

#define TEST_SAMPLE_RATE 48000
#define TEST_AUDIO_BUFF_SIZE 1024

int setup_sys_param(void **state)
{
    Sys_param *sp = NULL;

    sp = alloc_sys_param();
    if (sp == NULL)
    {
        sys_print_error_test("Memory allocation error");
        return -1;
    }

    *state = sp;

    return 0;
}

int teardown_sys_param(void **state)
{
    Sys_param *sp = *state;

    free_sys_param(sp);

    return 0;
}

void test_copy_osc_sys_param_to_notes_osc(void **state)
{
    Sys_param *sp = *state;

    Polyphony *note_array = NULL;
    note_array = alloc_polyphony(TEST_AUDIO_BUFF_SIZE);
    assert_non_null(note_array);

    assert_int_equal(copy_osc_sys_param_to_notes_osc(sp, NULL), -1);
    assert_int_equal(copy_osc_sys_param_to_notes_osc(NULL, note_array), -1);

    sp->osc1->onoff = ON;
    sp->osc1->amp = 15235;
    sp->osc1->detune = -11;
    sp->osc1->duty = 50;
    sp->osc1->wave = TRI;

    sp->osc2->onoff = OFF;
    sp->osc2->amp = 13256;
    sp->osc2->detune = 5;
    sp->osc2->duty = 65;
    sp->osc2->wave = SIN;

    sp->osc3->onoff = ON;
    sp->osc3->amp = 1;
    sp->osc3->detune = 0;
    sp->osc3->duty = 0;
    sp->osc3->wave = SQR;

    assert_int_equal(copy_osc_sys_param_to_notes_osc(sp, note_array), 0);

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        assert_int_equal(note_array[i]->osc1->onoff, sp->osc1->onoff);
        assert_int_equal(note_array[i]->osc1->amp, sp->osc1->amp);
        assert_int_equal(note_array[i]->osc1->detune, sp->osc1->detune);
        assert_int_equal(note_array[i]->osc1->duty, sp->osc1->duty);
        assert_int_equal(note_array[i]->osc1->wave, sp->osc1->wave);

        assert_int_equal(note_array[i]->osc2->onoff, sp->osc2->onoff);
        assert_int_equal(note_array[i]->osc2->amp, sp->osc2->amp);
        assert_int_equal(note_array[i]->osc2->detune, sp->osc2->detune);
        assert_int_equal(note_array[i]->osc2->duty, sp->osc2->duty);
        assert_int_equal(note_array[i]->osc2->wave, sp->osc2->wave);

        assert_int_equal(note_array[i]->osc3->onoff, sp->osc3->onoff);
        assert_int_equal(note_array[i]->osc3->amp, sp->osc3->amp);
        assert_int_equal(note_array[i]->osc3->detune, sp->osc3->detune);
        assert_int_equal(note_array[i]->osc3->duty, sp->osc3->duty);
        assert_int_equal(note_array[i]->osc3->wave, sp->osc3->wave);
    }

    free_polyphony(note_array);
}