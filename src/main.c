/**
 * \file main.c
 * \brief Main program
 *
 */

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "sys_param/sys_param.h"
#include "core/note/polyphony.h"
#include "gui/gui.h"
#include "audio/audio.h"
#include "system/error_handler.h"
#include "sys_param/xml/preset_xml.h"
#include "midi/midi.h"

// JUST A TEST
Uint16 test_freq[20] = {87, 87, 87, 87, 87, 87, 87, 87, 87, 175, 175, 175, 175, 175, 175};
Uint16 test_length[20] = {150, 150, 150, 150, 150, 150, 150, 150, 150, 100, 100, 100, 100, 100, 100};
Uint16 test_delay[20] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 100, 100, 100, 100, 100, 100};

int main(int argc, char *argv[])
{
    SDL_AudioSpec as;
    Core *audio_core;
    int fork_pid;
    int fork_status;
    int exit_flag = 0;

    MIDI_PERIPHERAL *midi_peripheral = alloc_midi_peripheral();
    if (midi_peripheral == NULL)
    {
        sys_print_error("Failed allocating memory for MIDI peripheral");
        exit(EXIT_FAILURE);
    }

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

    midi_peripheral = open_midi_peripheral();
    if (midi_peripheral == NULL)
    {
        sys_print_error("Failed opening MIDI device. Aborting.");
        exit(EXIT_FAILURE);
    }

    SDL_PauseAudio(0);                      // Play audio (pause = off)

    int i =0;
    while (i < 100)        // temporary --> wait for 100 MIDI events then exit program
    {
        if (process_midi_input(midi_peripheral, audio_core))exit(EXIT_FAILURE);
        i++;
    }


    SDL_CloseAudio();
    SDL_Quit();

#endif

    // Free all the data
    free_core(audio_core);
    free_midi_peripheral(midi_peripheral);

    return 0;
}