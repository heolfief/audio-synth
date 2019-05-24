/**
 * \file wav_test.h
 * \brief Wav test functions definitions.
 *
 *
 * Here are defined the test functions for the wav functions
 */


#ifndef AUDIO_SYNTH_TEST_WAV_TEST_WAV_TEST_H_
#define AUDIO_SYNTH_TEST_WAV_TEST_WAV_TEST_H_

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "core/audio_core.h"
#include "sys_param/sys_param.h"
#include "audio/wav.h"


/**
 * \fn int setup_wav(void **state)
 * \brief Function to allocate and test allocation of the wav file
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_wav(void **state);

/**
 * \fn int teardown_wav(void **state)
 * \brief Function to deallocate the wav file
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_wav(void **state);

/**
 * \fn void test_write_wav_file(void **state)
 * \brief Function to test write_wav_file function
 */
void test_write_wav_file(void **state);



#endif //AUDIO_SYNTH_TEST_WAV_TEST_WAV_TEST_H_
