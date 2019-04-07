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
#include "sys_param/xml/preset_xml.h"

// JUST A TEST
Uint16 mario_freq[7]={660, 660, 660, 510, 660, 770, 380};
Uint16 mario_delay[7]={80, 200, 250, 80, 250, 450, 450};


int main(int argc, char *argv[])
{
    SDL_AudioSpec as;
    Core audio_core;

    audio_core.sys_param = alloc_sys_param();
    if(audio_core.sys_param == NULL) exit(EXIT_FAILURE);

    // Default parameters. If changed, memory allocation needs to be redone
    audio_core.sys_param->sample_rate         = 48000;
    audio_core.sys_param->audio_buffer_length = 1024;


    // Audio core init
    if(init_core(&audio_core) != 0){
        sys_print_error("Failed initializing audio core");
        exit(EXIT_FAILURE);
    }

    if(load_preset("default.prst", audio_core.sys_param))
    {
        sys_print_error("Failed loading preset");
        exit(EXIT_FAILURE);
    }

    save_preset("save_test.prst", audio_core.sys_param);

#ifndef VALGRIND

    set_audio_spec(&as, &audio_core);

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

    // Each time oscillator parameters changed, this function needs to be called
    copy_osc_sys_param_to_notes_osc(audio_core.sys_param, audio_core.note_array);


    // Hard coded note data, will be changed by reading MIDI files in the future
    audio_core.note_array[0]->freq = 440;
    audio_core.note_array[0]->onoff = OFF;
    audio_core.note_array[0]->velocity_amp = 1;
    audio_core.note_array[0]->master_onoff = OFF;


    SDL_PauseAudio(0);                      // Play audio (pause = off)


    for(int i = 0; i < 7; ++i)
    {
        audio_core.note_array[0]->freq = mario_freq[i];
        note_on(audio_core.note_array[0]);
        SDL_Delay(100);
        note_off(audio_core.note_array[0]);
        SDL_Delay(mario_delay[i]);
    }

    SDL_Delay(2000);

    SDL_CloseAudio();
    SDL_Quit();

#endif

    // Free all the data
    quit_core(&audio_core);
    free_sys_param(audio_core.sys_param);

    return 0;
}