//
// Created by vincent on 24/05/19.
//

#include "midi_list.h"

int setup_midiData(void **state)
{
    midiData * midi_info = NULL;
    midiList * midi_List = initList();

    if (midi_List == NULL){
        return -1;
    }
    *state = midi_List;
    return 0 ;
    
}

int teardown_midiData(void **state)
{

    freeList(*state);
    return 0;
}
/*
void test_midiData_fill_struct(void **state){
    midiData * midi_info = *state;
    int return_value =5;
    midi_info->midiEvent = OFF_NOTE;
    midi_info->delay = 5;
    midi_info->midiNote = 5;
    midi_info->attack = 5;
    midi_info->next = midi_info;
    midiData * test = initList();

    assert_ptr_equal(midifill_midiData(5,5,OFF_NOTE,5,midi_info),midi_info);


}
*/
void test_next_midiData(void **state){
    midiList * m = *state;

    m->current =  new_note_list(9,9,ON_NOTE,9,NULL);

    void * test = m;
    assert_non_null(m);

    m->current = new_note_list(8,8,OFF_NOTE,8,m->current);
    m->first = m->current;
    m->current = m->current->next;

    assert_ptr_equal(test,m);


}