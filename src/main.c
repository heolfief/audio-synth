/**
 * \file main.c
 * \brief Main program
 *
 */


#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "sys_param/sys_param.h"
#include "core/note/polyphony.h"
#include "gui/gui.h"
#include "audio/audio.h"
#include "system/error_handler.h"

// Global audio variable defined in audio_core.h [TEMPORARY, JUST NEEDED FOR HARDCODING OF MARIO SOUND]
extern Polyphony *note_array;

// Global system parameters changed by the GUI
Sys_param* sys_param = NULL;

// JUST A TEST
Uint16 mario_freq[7]={660, 660, 660, 510, 660, 770, 380};
Uint16 mario_delay[7]={80, 200, 250, 80, 250, 450, 450};


int main(int argc, char *argv[])
{
    SDL_AudioSpec as;

    sys_param = alloc_sys_param();
    if(sys_param == NULL) exit(EXIT_FAILURE);

    // Default parameters. If changed, memory allocation needs to be redone
    sys_param->sample_rate         = 48000;
    sys_param->audio_buffer_length = 1024;


    // Audio core init
    if(init_core() != 0){
        sys_print_error("Failed initializing audio core");
        exit(EXIT_FAILURE);
    }

#ifndef VALGRIND

    set_audio_spec(&as);

    // SDL initialisations
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        sys_print_error("Failed initializing SDL");
        exit(EXIT_FAILURE);
    }

    if(SDL_OpenAudio(&as, NULL) != 0)
    {
        sys_print_error("Failed opening audio");
        exit(EXIT_FAILURE);
    }

    // Hard coded system parameters, will be changed by the GUI in the future
    sys_param->env->attack   = 0.001;
    sys_param->env->decay    = 0.01;
    sys_param->env->sustain  = 0.5;
    sys_param->env->release  = 0.2;

    sys_param->osc1->amp     = 32000;
    sys_param->osc1->wave    = SQR;
    sys_param->osc1->detune  = 0;
    sys_param->osc1->duty    = 50;
    sys_param->osc1->onoff   = ON;

    sys_param->osc2->amp     = 5000;
    sys_param->osc2->wave    = SIN;
    sys_param->osc2->detune  = 0;
    sys_param->osc2->duty    = 50;
    sys_param->osc2->onoff   = ON;

    sys_param->osc3->amp     = 32000;
    sys_param->osc3->wave    = TRI;
    sys_param->osc3->detune  = -12;
    sys_param->osc3->duty    = 50;
    sys_param->osc3->onoff   = ON;

    // Each time oscillator parameters changed, this function needs to be called
    copy_osc_sys_param_to_notes_osc(sys_param, note_array);


    // Hard coded note data, will be changed by reading MIDI files in the future
    note_array[0]->freq = 440;
    note_array[0]->onoff = OFF;
    note_array[0]->velocity_amp = 1;
    note_array[0]->master_onoff = OFF;


    SDL_PauseAudio(0);                      // Play audio (pause = off)


    for(int i = 0; i < 7; ++i)
    {
        note_array[0]->freq = mario_freq[i];
        note_on(note_array[0]);
        SDL_Delay(100);
        note_off(note_array[0]);
        SDL_Delay(mario_delay[i]);
    }

    SDL_Delay(2000);

    SDL_CloseAudio();
    SDL_Quit();

#endif

    // Free all the data
    quit_core();
    free_sys_param(sys_param);

    return 0;
}