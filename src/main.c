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

int main(int argc, char *argv[])
{
    SDL_AudioSpec as;
    Core *audio_core;
    MIDI_Peripheral_fd midi_peripheral;
    Gui_SDL_objects *gui;

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

    gui = alloc_gui_sdl_objects();
    if (gui == NULL)
    {
        sys_print_error("Failed allocating memory to gui");
        exit(EXIT_FAILURE);
    }

    if (load_preset("default.prst", audio_core->sys_param))
    {
        sys_print_error("Failed loading preset");
        exit(EXIT_FAILURE);
    }

    save_preset("save_test.prst", audio_core->sys_param);

#ifndef VALGRIND

    midi_peripheral = open_midi_peripheral();
    if (midi_peripheral == -1)
    {
        sys_print_error("Failed opening MIDI device. Aborting.");
        exit(EXIT_FAILURE);
    }

    set_audio_spec(&as, audio_core);

    // SDL initialisations
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        sys_print_error("Failed initializing SDL");
        exit(EXIT_FAILURE);
    }

    if (init_gui(gui))exit(EXIT_FAILURE);
    if (create_switches_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_pots_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (load_sys_param_to_gui(gui, audio_core->sys_param))exit((EXIT_FAILURE));
    if (gui_update(gui))exit(EXIT_FAILURE);

    if (SDL_OpenAudio(&as, NULL) != 0)
    {
        sys_print_error("Failed opening audio");
        exit(EXIT_FAILURE);
    }

    // Each time oscillator parameters changed, this function needs to be called
    if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

    // Each time a filter parameter is changed, this function needs to be called
    if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

    SDL_PauseAudio(0);                      // Play audio (pause = off)

    while (!gui->application_quit)
    {
        if (process_midi_input(midi_peripheral, audio_core))exit(EXIT_FAILURE);

        while (SDL_PollEvent(&gui->event))
        {
            if (process_switches(gui, audio_core))exit(EXIT_FAILURE);
            if (process_pots(gui, audio_core))exit(EXIT_FAILURE);

            switch (gui->event.type)
            {
                case SDL_QUIT:

                    gui->application_quit = SDL_TRUE;
                    break;

                case SDL_KEYDOWN:

//                    printf("Key down\n");
                    break;

                case SDL_KEYUP:

//                    printf("Key up\n");
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    printf("Mouse clic on x=%d, y=%d\n", gui->event.button.x, gui->event.button.y);
                    break;

                case SDL_MOUSEWHEEL:

//                    SDL_GetMouseState(&gui->mouse_position->x, &gui->mouse_position->y);
//                    printf("Mouse is on x=%d, y=%d\n", gui->mouse_position->x, gui->mouse_position->y);
//                    printf("Mouse wheel direction %d\n", gui->event.wheel.y);
                    break;
            }
        }
    }

    exit_gui(gui);

    SDL_CloseAudio();
    SDL_Quit();

    close_midi_peripheral(midi_peripheral);

#endif

    // Free all the data
    free_gui_sdl_objects(gui);
    free_core(audio_core);

    return 0;
}