/**
 * \file sys_param_test.h
 * \brief System parameters test functions definition.
 *
 *
 * Here are defined the test functions for system parameters
 */

#ifndef AUDIO_SYNTH_TEST_SYS_PARAM_TEST_SYS_PARAM_TEST_H_
#define AUDIO_SYNTH_TEST_SYS_PARAM_TEST_SYS_PARAM_TEST_H_

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "sys_param/sys_param.h"

/**
 * \fn int setup_sys_param(void **state)
 * \brief Function to allocate and test allocation of system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_sys_param(void **state);

/**
 * \fn int teardown_sys_param(void **state)
 * \brief Function to deallocate system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_sys_param(void **state);

/**
 * \fn void test_copy_osc_sys_param_to_notes_osc(void **state)
 * \brief Function to test copy_osc_sys_param_to_notes_osc function
 */
void test_copy_osc_sys_param_to_notes_osc(void **state);

#endif //AUDIO_SYNTH_TEST_SYS_PARAM_TEST_SYS_PARAM_TEST_H_
