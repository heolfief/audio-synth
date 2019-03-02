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

Note *alloc_note(Uint16 buff_nb_samples)
{
    Note *note_allocated = (Note*)malloc(sizeof(Note));
    if(note_allocated == NULL)
    {
        fprintf(stderr, "Memory allocation error at %s (%d)\n", __FILE__, __LINE__);
        return NULL;
    }

    note_allocated->osc1 = alloc_osc(buff_nb_samples);
    note_allocated->osc2 = alloc_osc(buff_nb_samples);
    note_allocated->osc3 = alloc_osc(buff_nb_samples);
    if((note_allocated->osc1 == NULL) || (note_allocated->osc2 == NULL) || (note_allocated->osc3 == NULL))
    {
        return NULL;
    }

    note_allocated->buffer = alloc_note_buffer(buff_nb_samples);
    if(note_allocated->buffer == NULL)
    {
        return NULL;
    }
    return note_allocated;
}
int free_note(Note *note_to_free)
{
    free_osc(note_to_free->osc1);
    free_osc(note_to_free->osc2);
    free_osc(note_to_free->osc3);
    free_note_buffer(note_to_free->buffer);
    free(note_to_free);
    return 0;
}

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