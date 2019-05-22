//
// Created by vincent on 21/05/19.
//

#ifndef AUDIO_SYNTH_TEST_LIST_MIDI_TEST_LIST_MIDI_TEST_H_
#define AUDIO_SYNTH_TEST_LIST_MIDI_TEST_LIST_MIDI_TEST_H_

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "Listmidi/listmidi.h"
#include "midi/midi_file.h"


/**
 * \fn int setup_midiList(void **state)
 * \brief Function to allocate and test allocation of the midiList
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_midiList (void ** state);

/**
 * \fn int teardown_midiList(void **state)
 * \brief Function to deallocate the midiList
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_midiList(void **state);

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













#endif //AUDIO_SYNTH_TEST_LIST_MIDI_TEST_LIST_MIDI_TEST_H_
