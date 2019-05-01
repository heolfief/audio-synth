/**
 * \file polyphony_test.h
 * \brief Polyphony test functions definition.
 *
 *
 * Here are defined the test functions for polyphony
 */

#ifndef AUDIO_SYNTH_POLYPHONY_TEST_H
#define AUDIO_SYNTH_POLYPHONY_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "core/note/polyphony.h"

/**
 * \fn int setup_polyphony(void **state)
 * \brief Function to allocate and test allocation of a polyphony array
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_polyphony(void **state);

/**
 * \fn int teardown_polyphony(void **state)
 * \brief Function to deallocate a polyphony array
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_polyphony(void **state);

/**
 * \fn void test_find_free_note(void **state)
 * \brief Function to test find_free_note function
 */
void test_find_free_note(void **state);

/**
 * \fn void test_find_note_from_id(void **state)
 * \brief Function to test find_note_from_id function
 */
void test_find_note_from_id(void **state);

/**
 * \fn test_polyphony_fill_buffer(void **state)
 * \brief Function to test polyphony_fill_buffer function
 */
void test_polyphony_fill_buffer(void **state);

#endif //AUDIO_SYNTH_POLYPHONY_TEST_H
