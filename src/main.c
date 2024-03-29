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
#include <sndfile.h>

#include "sys_param/sys_param.h"
#include "core/note/polyphony.h"
#include "gui/gui.h"
#include "audio/audio.h"
#include "system/error_handler.h"
#include "sys_param/xml/preset_xml.h"
#include "midi/midi_keyboard.h"
#include "gui/keypad.h"
#include "core/audio_core.h"
#include "audio/wav.h"
#include "midi/midi_file.h"

int main(int argc, char *argv[])
{
    SDL_AudioSpec as;
    Core *audio_core;
    Gui *gui;
    MIDI_Peripheral_fd midi_peripheral = -1;
    Uint8 mouse_is_down = 0;
    Uint32 currentTime;

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

    gui = alloc_gui();
    if (gui == NULL)
    {
        sys_print_error("Failed allocating memory to gui");
        exit(EXIT_FAILURE);
    }

    if (load_preset("default.prst", audio_core->sys_param, RELATIVE_PATH_MODE))
    {
        sys_print_error("Failed loading preset");
        exit(EXIT_FAILURE);
    }

#ifndef VALGRIND

    set_audio_spec(&as, audio_core);

    // SDL initialisations
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        sys_print_error("Failed initializing SDL");
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0)
    {
        sys_print_error("Failed initializing SDL TTF");
        exit(EXIT_FAILURE);
    }

    //Initialize the GUI
    if (init_gui(gui))exit(EXIT_FAILURE);

    //create maps for the different SDL elements
    if (create_switches_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_pots_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_buttons_map(gui))exit(EXIT_FAILURE);
    if (create_Text_map(gui))exit(EXIT_FAILURE);
    if (create_Leds_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_touch_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);

    //load the system parameters to the GUI, to set the different sound parameters
    if (load_sys_param_to_gui(gui, audio_core->sys_param))exit((EXIT_FAILURE));

    //updates the GUI with the new parameters loaded
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

    SDL_PauseAudio(SDL_FALSE);              // Play audio (pause = off)

    //Loops that keeps running until the user exits the app
    while (!gui->application_quit)
    {
        currentTime = SDL_GetTicks();       // Get time from SDL init in ms

        controlMidi(currentTime, audio_core);

        //checks if the buffer has been updated and process the leds of the VUmeter
        if (audio_core->buffer_is_new)
        {
            if (process_leds(gui, audio_core))exit(EXIT_FAILURE);
        }

        if (midi_peripheral != -1)
        {
            if (process_midi_input(&midi_peripheral, audio_core))exit(EXIT_FAILURE);

            if (midi_peripheral == -2)
            {
                midi_peripheral = -1;
                gui->buttons[2].pressed = 0;
                if (gui_set_switch_image(gui->buttons[2].sdl_button, gui->buttons[2].imgoff))return -1;
                if (gui_update(gui))return -1;
                tinyfd_messageBox(NULL, "MIDI device disconnected", "ok", "info", 1);
            }
        }

        //loop waiting for an SDL event like a keyboard touch or mouse movements
        while (SDL_PollEvent(&gui->event))
        {
            if (process_switches(gui, audio_core))exit(EXIT_FAILURE);
            if (process_pots(gui, audio_core, mouse_is_down))exit(EXIT_FAILURE);
            if (process_buttons(gui, audio_core, &midi_peripheral))exit(EXIT_FAILURE);

            switch (gui->event.type)
            {
                case SDL_QUIT:

                    for (int i = 0; i < POLYPHONY_MAX; i++)
                    {
                        note_off(audio_core->note_array[i]);
                        audio_core->note_array[i]->master_onoff = OFF;
                    }
                    if (prompt_quit())
                    {
                        printf("Quit asked. Closing...\n");
                        gui->application_quit = SDL_TRUE;
                    }
                    break;

                case SDL_KEYDOWN:

                    if (gui->event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        for (int i = 0; i < POLYPHONY_MAX; i++)
                        {
                            note_off(audio_core->note_array[i]);
                            audio_core->note_array[i]->master_onoff = OFF;
                        }
                        if (prompt_quit())
                        {
                            printf("Quit asked. Closing...\n");
                            gui->application_quit = SDL_TRUE;

                        }
                    }
                    if (keypress(&gui->event, audio_core, gui))exit(EXIT_FAILURE);
                    break;

                case SDL_KEYUP:

                    if (keyrelease(&gui->event, audio_core, gui))exit(EXIT_FAILURE);
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    mouse_is_down = 1;
                    break;

                case SDL_MOUSEBUTTONUP:

                    mouse_is_down = 0;
                    break;
            }
        }
        SDL_Delay(0.1);
    }

    //switching off the recording session in case the user forgot to stop
    if (audio_core->record_param->RecordOnOff)
    {
        audio_core->record_param->RecordOnOff = OFF;
        close_wav_file(audio_core->record_param->sndFile);
    }

    exit_gui(gui);

    TTF_Quit();
    SDL_CloseAudio();
    SDL_Quit();

    close_midi_peripheral(midi_peripheral);

#endif

    // Free all the data
    free_gui(gui);
    free_core(audio_core);

    return 0;
}