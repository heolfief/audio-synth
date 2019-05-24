//
// Created by vincent on 24/05/19.
//

#include "midi_list.h"

int setup_midiData(void **state)
{
    midiData * midi_info = NULL;
    midi_info = initList();
    if (midi_info == NULL){
        return -1;
    }
    state = midi_info;
    return 0 ;
    
}

int teardown_midiData(void **state)
{
    freeNodeList(*state);
    return 0;
}

