/**
 * \file polyphony.c
 * \brief Polyphony data structure and function implementation.
 *
 *
 * Here are implemented the data structure of a polyphony, and the related functions
 */

#include "polyphony.h"

int find_free_note(Polyphony *p)
{
    if (p == NULL)
    {
        sys_print_error("Parameter p is NULL");
        return -1;
    }
    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        if (p[i]->master_onoff == OFF)return i;
    }
    sys_print_error("No free note found for polyphony");
    return -1;
}

int find_note_from_id(Polyphony *p, Uint8 id)
{
    if (p == NULL)
    {
        sys_print_error("Parameter p is NULL");
        return -1;
    }
    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        if (p[i]->midi_id == id)return i;
    }

    return -1;
}

int polyphony_fill_buffer(Audio_Buffer audio_buff, Polyphony *p, Uint16 buffer_length, const Envelope *env, Uint64 sample_rate, Uint64 phase)
{
    double temp_mix = 0;

    if (p == NULL)
    {
        sys_print_error("Polyphony parameter is NULL");
        return -1;
    }

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        // Fill all the note buffers
        if (note_fill_buffer(p[i], buffer_length, env, sample_rate, phase))return -1;
    }

    // Mix all the note buffers based on number of active notes
    for (Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        temp_mix = 0;

        // Mix all the notes buffer fo the sample
        for (int i = 0; i < POLYPHONY_MAX; ++i)
        {
            if (p[i]->master_onoff == ON)
            {
                temp_mix += (double) p[i]->buffer[sample];
            }
        }
        // Get amplitude back within data range
        if (temp_mix > (double) INT16_MAX)
        {
            temp_mix = temp_mix * (double) INT16_MAX / temp_mix - 1;
        }
        else if (temp_mix < (double) INT16_MIN)
        {
            temp_mix = temp_mix * (-(double) INT16_MIN) / temp_mix + 1;
        }
        audio_buff[sample] = (Sint16) temp_mix;
    }

    return 0;
}

Polyphony *alloc_polyphony(Uint16 buff_nb_samples)
{
    Polyphony *note_array = NULL;
    note_array = (Polyphony *) calloc(POLYPHONY_MAX, sizeof(Polyphony));
    if (note_array == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        note_array[i] = alloc_note(buff_nb_samples);
        if (note_array[i] == NULL)
        {
            sys_print_error("Memory allocation error");
            return NULL;
        }
    }
    return note_array;
}

int free_polyphony(Polyphony *p)
{
    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        free_note(p[i]);
    }
    free(p);
    return 0;
}

Audio_Buffer alloc_audio_buffer(Uint16 buff_nb_samples)
{
    Audio_Buffer audio_buff = (Note_Buffer) calloc(buff_nb_samples, sizeof(Audio_Buffer));
    if (audio_buff == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    return audio_buff;
}

int free_audio_buffer(Audio_Buffer audio_buff)
{
    free(audio_buff);
    return 0;
}