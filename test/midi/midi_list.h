//
// Created by vincent on 24/05/19.
//

#ifndef AUDIO_SYNTH_TEST_MIDI_MIDI_LIST_H_
#define AUDIO_SYNTH_TEST_MIDI_MIDI_LIST_H_

#endif //AUDIO_SYNTH_TEST_MIDI_MIDI_LIST_H_

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "Listmidi/listmidi.h"




/**
 * \fn int setup_midiData(void **state)
 * \brief Function to allocate and test allocation of a midiData
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_midiData(void **state);

/**
 * \fn int teardown_midiData(void **state)
 * \brief Function to deallocate a midiData
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_midiData(void **state);

/**
 * \fn void test_midiData_fill_struct(void **state)
 * \brief Function to test fill_midiData function
 */
void test_midiData_fill_struct(void **state);


