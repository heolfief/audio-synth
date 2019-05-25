/**
 * \file midi_list_data_Range_test.c
 * \brief dataRangeList test functions.
 *
 *
 * Here are implemented the test functions for dataRangeList
 */

#include "midi_list_data_Range_test.h"


int setup_dataRangeList(void **state)
{
    dataRangeList * DataRangeList = initdataRangeList();

    if (DataRangeList == NULL){
        return -1;
    }
    *state = DataRangeList;
    return 0 ;

}


int teardown_dataRangeList(void **state)
{
    freeDataRange(*state);
    return 0;
}



void test_next_dataRangeList(void **state)
{
    dataRangeList * m = *state;
   midiList *n = initList();

    for (int i = 0;i<5;i++) // midiList creation
    {
        n->current = new_note_list(i, i, ON_NOTE, i, n->current);

        if (empty(n)){
            n->first = n->current;
        }


    }

   m->currentDataRange = new_Midi_List(n,m->currentDataRange); // go the midiList in Data range list
    assert_non_null(m->currentDataRange);

void *test = m->currentDataRange; // create temp variable to test if the nex is equal to this

    n = initList();
    for (int i = 0; i<5;i++ ){ // midi_test List creation
        n->current = new_note_list(i, i, ON_NOTE, i, n->current);

        if (empty(n)){
            n->first = n->current;
        }

    }
   m->currentDataRange = new_Midi_List(n,m->currentDataRange); // put the seconde midiList in data Range List
    m->firstDataRange = m->currentDataRange;
    assert_non_null(m->firstDataRange);

    nextDataRange(m);
    assert_ptr_equal(m->currentDataRange,test);

}

void test_update_delay_dataRangeList(void **state){
    dataRangeList * m = *state;
    midiList *n = initList();

    for (int i = 0;i<5;i++) // midiList creation
    {
        n->current = new_note_list(i+1, i+1, ON_NOTE, i+1, n->current);

        if (empty(n)){
            n->first = n->current;
        }


    }
    setOnFirst(n);
    m->currentDataRange = new_Midi_List(n,m->currentDataRange); // go the midiList for the first data range list


    m->firstDataRange = m->currentDataRange;

    assert_int_equal(m->currentDataRange->accrued_delay,0); // test before the update

    updateDelayDataRange(m,getCount(m));


    assert_int_equal( m->currentDataRange->accrued_delay,1); // test after the update


}


void test_get_first_note_to_play(void **state){
    dataRangeList * m = *state;
    midiList *n = initList();
    for (int i = 0;i<5;i++) // midiList creation
    {
        n->current = new_note_list(i+1, i+1, ON_NOTE, i+1, n->current);

        if (empty(n)){
            n->first = n->current;
        }


    }
    setOnFirst(n);
    m->currentDataRange = new_Midi_List(n,m->currentDataRange); // go the midiList for the first data range list
    n = initList();
    for (int i = 0; i<5;i++ ){ // midi_test List creation
        n->current = new_note_list(i+5, i+5, ON_NOTE, i+5, n->current);

        if (empty(n)){
            n->first = n->current;
        }

    }
    m->currentDataRange = new_Midi_List(n,m->currentDataRange); // put the seconde midiList in data Range List
    m->firstDataRange = m->currentDataRange;

    updateDelayDataRange(m,getCount(m));


    midiData * g =getFirstNoteToPlay(m,getCount(m));
    assert_int_equal(g->delay,1);
    assert_int_equal(g->midiNote,1);
    updateDelayDataRange(m,getCount(m));
     g =getFirstNoteToPlay(m,getCount(m));
    assert_int_equal(g->delay,2);
    assert_int_equal(g->midiNote,2);




}