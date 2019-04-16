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
Uint16 europe_freq[20] =   {587, 880, 784, 880, 587, 932, 880, 932, 880, 784};
Uint16 europe_length[20] = {800, 100, 100, 400, 800, 100, 100, 200, 200, 800};
Uint16 europe_delay[20] =  {400, 100, 100, 400, 400, 100, 100, 200, 200, 400};

int main(int argc, char *argv[])
{
    SDL_AudioSpec as;
    Core* audio_core;

    // Default parameters. If buffer_len changed, core memory allocation needs to be redone
    int sample_rate = 48000;
    int buffer_len = 1024;

    // Audio core init
    audio_core = alloc_core(buffer_len);
    if (audio_core == NULL)
    {
        sys_print_error("Failed initializing audio core");
        exit(EXIT_FAILURE);
    }

    audio_core->sys_param->sample_rate = sample_rate;

    if (load_preset("default.prst", audio_core->sys_param))
    {
        sys_print_error("Failed loading preset");
        exit(EXIT_FAILURE);
    }

    save_preset("save_test.prst", audio_core->sys_param);

#ifndef VALGRIND

    set_audio_spec(&as, audio_core);

    // SDL initialisations
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        sys_print_error("Failed initializing SDL");
        exit(EXIT_FAILURE);
    }

    if (SDL_OpenAudio(&as, NULL) != 0)
    {
        sys_print_error("Failed opening audio");
        exit(EXIT_FAILURE);
    }

    // Each time oscillator parameters changed, this function needs to be called
    if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

    // Each time a filter parameter is changed, this function needs to be called
    if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

    // Hard coded note data, will be changed by reading MIDI files in the future
    audio_core->note_array[0]->freq = 440;
    audio_core->note_array[0]->onoff = OFF;
    audio_core->note_array[0]->velocity_amp = 1;
    audio_core->note_array[0]->master_onoff = OFF;

    SDL_PauseAudio(0);                      // Play audio (pause = off)

    for (int i = 0; i < 10; ++i)
    {
        audio_core->note_array[0]->freq = europe_freq[i];
        note_on(audio_core->note_array[0]);
        SDL_Delay((int)((double)europe_length[i]/1.5));
        note_off(audio_core->note_array[0]);
        SDL_Delay(europe_delay[i]);
    }

    SDL_Delay(2000);

    SDL_CloseAudio();
    SDL_Quit();

#endif

    // Free all the data
    free_core(audio_core);

    return 0;
}