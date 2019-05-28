//
// Created by vincent on 24/05/19.
//

#include <stdlib.h>
#include "midi_list_test.h"

int setup_midiData(void **state)
{
    midiList * midi_List = initList();

    if (midi_List == NULL){
        return -1;
    }
    *state = midi_List;
    return 0 ;
    
}

int teardown_midiData(void **state)
{
    //free midiList

    freeList(*state);
    free(*state);
    return 0;
}

void test_next_midiData(void **state){
    midiList * m = *state;

         m->current =  new_note_list(9,9,ON_NOTE,9,m->current);
         m->first = m->current;
         void * test = m;
         assert_non_null(m);

         m->current = new_note_list(8,8,OFF_NOTE,8,m->current);

         next(m);

         assert_ptr_equal(test,m);


}





