/**
 * \file sys_param.c
 * \brief System parameters data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the system parameters, and the related functions
 */

#include "sys_param.h"

int copy_osc_sys_param_to_notes_osc(Sys_param *sys_param_to_copy, Polyphony p[])
{
    if (sys_param_to_copy == NULL)
    {
        sys_print_error("sys_param_to_copy parameter is NULL");
        return -1;
    }
    if (p == NULL)
    {
        sys_print_error("Polyphony parameter is NULL");
        return -1;
    }

    for (int i = 0; i < POLYPHONY_MAX; ++i)
    {
        p[i]->osc1->onoff = sys_param_to_copy->osc1->onoff;
        p[i]->osc1->amp = sys_param_to_copy->osc1->amp;
        p[i]->osc1->detune = sys_param_to_copy->osc1->detune;
        p[i]->osc1->duty = sys_param_to_copy->osc1->duty;
        p[i]->osc1->wave = sys_param_to_copy->osc1->wave;

        p[i]->osc2->onoff = sys_param_to_copy->osc2->onoff;
        p[i]->osc2->amp = sys_param_to_copy->osc2->amp;
        p[i]->osc2->detune = sys_param_to_copy->osc2->detune;
        p[i]->osc2->duty = sys_param_to_copy->osc2->duty;
        p[i]->osc2->wave = sys_param_to_copy->osc2->wave;

        p[i]->osc3->onoff = sys_param_to_copy->osc3->onoff;
        p[i]->osc3->amp = sys_param_to_copy->osc3->amp;
        p[i]->osc3->detune = sys_param_to_copy->osc3->detune;
        p[i]->osc3->duty = sys_param_to_copy->osc3->duty;
        p[i]->osc3->wave = sys_param_to_copy->osc3->wave;

    }
    return 0;
}

Sys_param *alloc_sys_param()
{
    Uint16 buff_nb_samples = 1;   // Not needed as sys param oscillators are just used to store parameters,
    // therefore their buffers are useless

    Sys_param *sp = (Sys_param *) malloc(sizeof(Sys_param));
    if (sp == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    sp->osc1 = alloc_osc(buff_nb_samples);
    sp->osc2 = alloc_osc(buff_nb_samples);
    sp->osc3 = alloc_osc(buff_nb_samples);
    if ((sp->osc1 == NULL) || (sp->osc2 == NULL) || (sp->osc3 == NULL))
    {
        return NULL;
    }

    sp->env = (Envelope *) malloc(sizeof(Envelope));
    if (sp->env == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    sp->amp_mod_param = (Amp_mod_param *) malloc(sizeof(Amp_mod_param));
    if (sp->amp_mod_param == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    sp->dist_param = (Distortion_param *) malloc(sizeof(Distortion_param));
    if (sp->dist_param == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    sp->filter_param = (Filter_param *) malloc(sizeof(Filter_param));
    if (sp->filter_param == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    sp->flanger_param = (Flanger_param *) malloc(sizeof(Flanger_param));
    if (sp->flanger_param == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    return sp;
}

int free_sys_param(Sys_param *sys_param_to_free)
{
    free_osc(sys_param_to_free->osc1);
    free_osc(sys_param_to_free->osc2);
    free_osc(sys_param_to_free->osc3);
    free(sys_param_to_free->env);
    free(sys_param_to_free->amp_mod_param);
    free(sys_param_to_free->dist_param);
    free(sys_param_to_free->filter_param);
    free(sys_param_to_free->flanger_param);
    free(sys_param_to_free);
    return 0;
}