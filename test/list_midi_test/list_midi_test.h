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







#endif //AUDIO_SYNTH_TEST_LIST_MIDI_TEST_LIST_MIDI_TEST_H_
