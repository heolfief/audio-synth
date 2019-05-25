/**
 * \file midi_list_data_Range_test.h
 * \brief dataRangeList test functions.
 *
 *
 * Here are implemented the test functions for dataRangeList
 */

#ifndef AUDIO_SYNTH_TEST_MIDI_TEST_MIDI_LIST_DATA_RANGE_TEST_H_
#define AUDIO_SYNTH_TEST_MIDI_TEST_MIDI_LIST_DATA_RANGE_TEST_H_


#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/midi/midi_file.h"
#include "../../src/Listmidi/listDataRange.h"
#include "../../src/Listmidi/listmidi.h"
/**
 * \fn int setup_dataRangeList(void **state)
 * \brief Function to allocate and test allocation of a DataRangeList
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int setup_dataRangeList(void **state);

/**
 * \fn int teardown_dataRangeList(void **state)
 * \brief Function to deallocate a DataRangeList
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int teardown_dataRangeList(void **state);

/**
 * \fn void test_next_dataRangeList(void **state)
 * \brief Function to test next dataRangeList function
 */

void test_next_dataRangeList(void **state);

/**
 * \fn void test_update_delay_dataRangeList(void **state)
 * \brief Function to test update delay dataRangeList function
 */
void test_update_delay_dataRangeList(void **state);











#endif //AUDIO_SYNTH_TEST_MIDI_TEST_MIDI_LIST_DATA_RANGE_TEST_H_
