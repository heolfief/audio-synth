/**
 * \file note.c
 * \brief Note data structure and function implementation.
 *
 *
 * Here are implemented the data structure of a note, and the related functions
 */

#include <SDL2/SDL_stdinc.h>
#include "note.h"
#include "../oscillator/osc.h"


Note_Buffer alloc_note_buffer(Uint16 buff_nb_samples)
{
    Note_Buffer note_buff = (Note_Buffer) calloc(buff_nb_samples, sizeof(Note_Buffer));
    if(note_buff == NULL)
    {
        perror("memory allocation error\n");
        return NULL;
    }

    return note_buff;
}

int free_note_buffer(Note_Buffer note_buff)
{
    free(note_buff);
    return 0;
}