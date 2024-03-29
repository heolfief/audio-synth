/**
 * \file core_test.h
 * \brief Core test functions definition.
 *
 *
 * Here are defined the test functions for audio core
 */

#ifndef AUDIO_SYNTH_CORE_TEST_H
#define AUDIO_SYNTH_CORE_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "core/audio_core.h"
#include "sys_param/sys_param.h"

/**
 * \fn int setup_core(void **state)
 * \brief Function to allocate and test allocation of the audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_core(void **state);

/**
 * \fn int teardown_core(void **state)
 * \brief Function to deallocate the audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_core(void **state);

/**
 * \fn void test_core_fill_buffer(void **state)
 * \brief Function to test master_audio_fill_buffer function
 */
void test_master_audio_fill_buffer(void **state);

/**
 * \fn void test_fx(void **state)
 * \brief Function to test master_effects and all effects functions
 */
void test_fx(void **state);

/**
 * \fn void test_flanger(void **state)
 * \brief Function to test flanger effect function
 */
void test_flanger(void **state);

/**
 * \fn void test_distortion(void **state)
 * \brief Function to test distortion effect function
 */
void test_distortion(void **state);

/**
 * \fn void test_amp_mod(void **state)
 * \brief Function to test amp_mod effect function
 */
void test_amp_mod(void **state);

/**
 * \fn void test_filter(void **state)
 * \brief Function to test filter effect function
 */
void test_filter(void **state);

/**
 * \fn void test_lfo_filter(void **state)
 * \brief Function to test lfo_filter effect function
 */
void test_lfo_filter(void **state);

/**
 * \fn void test_delay(void **state)
 * \brief Function to test delay effect function
 */
void test_delay(void **state);

#endif //AUDIO_SYNTH_CORE_TEST_H
