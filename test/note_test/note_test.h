/**
 * \file note_test.h
 * \brief Note test functions definition.
 *
 *
 * Here are defined the test functions for the note
 */

#ifndef AUDIO_SYNTH_NOTE_TEST_H
#define AUDIO_SYNTH_NOTE_TEST_H

#include "note/note.h"

/**
 * \fn int setup_note(void **state)
 * \brief Function to allocate and test allocation of a note
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_note(void **state);

/**
 * \fn int teardown_note(void **state)
 * \brief Function to deallocate a note
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_note(void **state);

/**
 * \fn void note_on_test(void **state)
 * \brief Function to test note_on function
 */
void test_note_on(void **state);

/**
 * \fn void note_off_test(void **state)
 * \brief Function to test note_off function
 */
void test_note_off(void **state);

/**
 * \fn void test_update_envelope(void **state)
 * \brief Function to test update_envelope function
 */
void test_update_envelope(void **state);

/**
 * \fn void test_note_fill_buffer(void **state)
 * \brief Function to test note_fill_buffer function
 */
void test_note_fill_buffer(void **state);

/**
 * \fn void test_get_freq_from_note_nbr(void **state)
 * \brief Function to test get_freq_from_note_nbr function
 */
void test_get_freq_from_note_nbr(void **state);

#endif //AUDIO_SYNTH_NOTE_TEST_H
