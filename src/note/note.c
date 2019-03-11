/**
 * \file note.c
 * \brief Note data structure and function implementation.
 *
 *
 * Here are implemented the data structure of a note, and the related functions
 */

#include "note.h"


Uint16 get_freq_from_note_nbr(Sint8 note_nbr, Uint16 ref_freq)
{
    static const double chromatic_ratio = 1.059463094359295264562;

    // Calculate actual frequency based on note number, from reference frequency
    return (Uint16)(ref_freq * pow(chromatic_ratio, note_nbr));
}

int note_on(Note *n)
{
    if(n == NULL)
    {
        print_error("Note parameter is NULL");
        return -1;
    }

    n->onoff = ON;

    return 0;
}

int note_off(Note *n)
{
    if(n == NULL)
    {
        print_error("Note parameter is NULL");
        return -1;
    }

    n->onoff = OFF;
    n->deathtime = n->lifetime;

    return 0;
}

int note_fill_buffer(Note *n, Uint16 buffer_length, const Envelope *env, Uint64 sample_rate, Uint64 phase)
{
    if(n == NULL)
    {
        print_error("Note parameter is NULL");
        return -1;
    }

    // Apply frequency to oscillators
    n->osc1->freq = n->freq;
    n->osc2->freq = n->freq;
    n->osc3->freq = n->freq;

    // Fill the oscillators buffers
    osc_fill_buffer(n->osc1, buffer_length, sample_rate, phase);
    osc_fill_buffer(n->osc2, buffer_length, sample_rate, phase);
    osc_fill_buffer(n->osc3, buffer_length, sample_rate, phase);

    for(Uint16 sample = 0; sample < buffer_length; ++sample)
    {
        // Mix the 3 oscillators
        n->buffer[sample] = (Sint16)(n->osc1->buffer[sample] / 3 + n->osc2->buffer[sample] / 3 + n->osc3->buffer[sample] / 3);

        // Apply the note velocity
        n->buffer[sample] = (Sint16)((double)n->buffer[sample] * n->velocity_amp);

        // Add one sample to the note lifetime
        n->lifetime++;

        // Process the envelope calculation for the sample
        update_envelope(n,env);

        // Apply the envelope
        n->buffer[sample] = (Sint16)((double)n->buffer[sample] * n->env_amp);
    }
    return 0;
}

int update_envelope(Note *n, const Envelope *env)
{
    if(env->sustain < 0 || env->sustain > 1)
    {
        print_error("Envelope parameter 'sustain' is out of range");
        return -1;
    }

    if(n->onoff == ON && n->master_onoff == OFF)                        // If note just started
    {
        n->master_onoff = ON;
        n->lifetime = 0;                                                // Reset lifetime
        n->deathtime = 0;                                               // Reset deathtime
        n->env_amp = 0;
    }

    if(n->master_onoff == ON)
    {
        if(n->lifetime >= 0 && n->lifetime < env->attack)               // If note is in attack phase
        {
            n->env_amp = (double)n->lifetime / (double)env->attack;     // Linear increase from 0 to 1
        }

        if(n->lifetime >= env->attack && n->lifetime < (env->decay + env->attack))      // If note is in decay phase
        {
            n->env_amp = (double)1.0 + ((double)(n->lifetime - env->attack) * ((env->sustain - (double)1.0) / (double)env->decay));     // Linear decrease from 1 to sustain
        }

        if(n->lifetime >= (env->decay + env->attack) && n->onoff != OFF)// If note is in sustain phase
        {
            n->env_amp = env->sustain;                                  // Constant amplitude
        }

        if(n->onoff == OFF)                                             // If note is in release phase
        {
            n->env_amp = - (env->sustain / (double)env->release) * (double)(n->lifetime - n->deathtime) + env->sustain;

            if(n->env_amp <= 0)                                         // When env_amp is zero, put master_onoff OFF
            {
                n->master_onoff = OFF;
            }
        }
    }

    return 0;
}

Note *alloc_note(Uint16 buff_nb_samples)
{
    Note *note_allocated = (Note*)malloc(sizeof(Note));
    if(note_allocated == NULL)
    {
        print_error("Memory allocation error");
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
        print_error("Memory allocation error");
        return NULL;
    }

    return note_buff;
}

int free_note_buffer(Note_Buffer note_buff)
{
    free(note_buff);
    return 0;
}