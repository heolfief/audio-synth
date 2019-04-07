/**
 * \file polyphony_test.c
 * \brief Polyphony test functions.
 *
 *
 * Here are implemented the test functions for polyphony
 */

#include "polyphony_test.h"

#define TEST_SAMPLE_RATE 48000
#define TEST_AUDIO_BUFF_SIZE 1024

int setup_polyphony(void **state)
{
    Polyphony *note_array = NULL;
    note_array = alloc_polyphony(TEST_AUDIO_BUFF_SIZE);
    if (note_array == NULL)
    {
        return -1;
    }

    *state = note_array;
    return 0;
}

int teardown_polyphony(void **state)
{
    free_polyphony(*state);
    return 0;
}

void test_find_free_note(void **state)
{
    Polyphony *note_array = *state;

    //Test error handling
    assert_int_equal(find_free_note(NULL), -1);

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        note_array[i]->master_onoff = OFF;
        note_array[i]->onoff = OFF;
    }

    note_array[0]->master_onoff = ON;
    note_array[1]->master_onoff = ON;
    note_array[2]->master_onoff = ON;
    note_array[3]->master_onoff = ON;
    note_array[4]->master_onoff = ON;
    note_array[5]->master_onoff = ON;

    //Test finding of free (OFF) note
    assert_int_equal(find_free_note(note_array), 6);

    note_array[6]->master_onoff = ON;
    assert_int_equal(find_free_note(note_array), 7);

    note_array[2]->master_onoff = OFF;
    assert_int_equal(find_free_note(note_array), 2);

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        note_array[i]->master_onoff = ON;
    }
    assert_int_equal(find_free_note(note_array), -1);
}

void test_polyphony_fill_buffer(void **state)
{
    Polyphony *note_array = *state;
    Envelope env = {.attack = 0, .decay =0, .sustain =1, .release =0};
    int return_value = 1, temp_mix, nbr_active_notes;

    Audio_Buffer audio_buff = NULL;
    audio_buff = alloc_audio_buffer(TEST_AUDIO_BUFF_SIZE);
    assert_int_not_equal(audio_buff, NULL);
    if (audio_buff == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        osc_init_default_values(note_array[i]->osc1, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
        osc_init_default_values(note_array[i]->osc2, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
        osc_init_default_values(note_array[i]->osc3, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);
    }

    //Test error handling
    return_value = polyphony_fill_buffer(audio_buff, NULL, TEST_AUDIO_BUFF_SIZE, &env, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, -1);

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        note_array[i]->master_onoff = OFF;
        note_array[i]->onoff = OFF;
        note_array[i]->lifetime = 0;
        note_array[i]->deathtime = 0;
    }

    return_value = polyphony_fill_buffer(audio_buff, note_array, TEST_AUDIO_BUFF_SIZE, &env, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, 0);

    for (Uint16 sample = 0; sample < TEST_AUDIO_BUFF_SIZE; ++sample)
    {
        assert_int_equal(audio_buff[sample], 0);
    }

    note_array[2]->master_onoff = ON;
    note_array[5]->master_onoff = ON;
    note_array[4]->master_onoff = ON;
    note_array[2]->onoff = ON;
    note_array[5]->onoff = ON;
    note_array[4]->onoff = ON;

    return_value = polyphony_fill_buffer(audio_buff, note_array, TEST_AUDIO_BUFF_SIZE, &env, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, 0);

    free_audio_buffer(audio_buff);
}