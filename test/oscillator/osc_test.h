/**
 * \file osc_test.h
 * \brief Oscillator test functions definition.
 *
 *
 * Here are defined the test functions for the oscillator
 */

#ifndef AUDIO_SYNTH_OSC_TEST_H
#define AUDIO_SYNTH_OSC_TEST_H

#include "oscillator/osc.h"

/**
 * \fn int setup_osc(void **state)
 * \brief Function to allocate and test allocation of an oscillator
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_osc(void **state);

/**
 * \fn int teardown_osc(void **state)
 * \brief Function to deallocate an oscillator
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_osc(void **state);

/**
 * \fn void test_fill_osc_buffer_zeros(void **state)
 * \brief Function to test filling an oscillator buffer with zeros (osc is off)
 */
void test_fill_osc_buffer_zeros(void **state);

/**
 * \fn void test_fill_osc_buffer_square(void **state)
 * \brief Function to test filling an oscillator buffer with square wave (osc is SQR)
 */
void test_fill_osc_buffer_square(void **state);

/**
 * \fn void test_osc_init_default_values(void **state)
 * \brief Function to test initialization of an oscillator with default values
 *
 * Check if defaults values are thoses defined in osc.h
 */
void test_osc_init_default_values(void **state);


#endif //AUDIO_SYNTH_OSC_TEST_H
