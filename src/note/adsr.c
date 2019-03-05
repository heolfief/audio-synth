/**
 * \file note.c
 * \brief ADSR envelope filter data structure and function implementation.
 *
 *
 * Here are implemented the data structure of an ADSR envelope filter, and the related functions
 */

#include "adsr.h"

int update_envelope(Note *n, Envelope *env)
{
    if(env->sustain < 0 || env->sustain > 1)
    {
        fprintf(stderr, "Envelope parameter 'sustain' is out of range at  %s (%d)\n", __FILE__, __LINE__);
        return -1;
    }

    if(n->onoff == ON)                                                  // If note just started
    {
        n->master_onoff = ON;
        n->lifetime = 0;
        n->deathtime = 0;
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

            if(n->onoff == OFF)                                         // If note is in release phase
            {
                n->deathtime = n->lifetime;                             // Save deathtime
            }
        }

        if(n->onoff == OFF && n->env_amp != 0)                          // If note is in release phase
        {
            n->env_amp = - (env->sustain / (double)env->release) * (double)(n->lifetime - n->deathtime) + env->sustain;

            if(n->env_amp >= 0)                                         // When env_amp is zero, put master_onoff OFF
            {
                n->master_onoff = OFF;
            }
        }
    }

    return 0;
}