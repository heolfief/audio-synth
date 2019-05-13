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
#include "midi/midi_keyboard.h"
#include "gui/keypad.h"
#include "core/audio_core.h"
#include "midi/midi_file.h"
#include "Listmidi/listmidi.h"
#include "fichier/fichier.h"




int main(int argc, char *argv[])
{

    FILE *test = openFile("../src/fichier_midi/mario2.mid", "r+", RETOUR);
    Header *H = (Header *) malloc(sizeof(Header));
    fillHeaderRead(H, test);
    setAsBeginDataRange(test);
    int size = getSizeDataRange(test);
    u_int8_t *MidiData = readDataRange(size, test);
    list *clairdelune = playDataRange(MidiData, H, size);
    printList(clairdelune);
    midiList *n;
    n = clairdelune->first;
    int g = 1;

    SDL_AudioSpec as;
    Core *audio_core;
    Gui_SDL_objects *gui;
    MIDI_Peripheral_fd midi_peripheral = -1;
    Uint8 mouse_is_down = 0;
    Uint32 lastTime = 0, currentTime;



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

    if (load_preset("default.prst", audio_core->sys_param, RELATIVE_PATH_MODE))
    {
        sys_print_error("Failed loading preset");
        exit(EXIT_FAILURE);
    }

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

    if (init_gui(gui))exit(EXIT_FAILURE);
    if (create_switches_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_pots_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_buttons_map(gui))exit(EXIT_FAILURE);
    if (create_Text_map(gui))exit(EXIT_FAILURE);
    if (create_Leds_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
    if (create_Touch_map(gui, audio_core->sys_param))exit(EXIT_FAILURE);
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

    SDL_PauseAudio(SDL_FALSE);              // Play audio (pause = off)







    while (!gui->application_quit)
    {
        currentTime = SDL_GetTicks();       // Get time from SDL init in ms



        // TEMP : 1000ms delay
        if (currentTime > lastTime + n->delay)  // If time has passed
        {
            lastTime = currentTime;

            if (n->midiEvent == 1)
            {
                midi_note_ON(audio_core, n->midiNote, n->attack);
            }
            else if (n->midiEvent == 0)
            {
                midi_note_OFF(audio_core, n->midiNote);
            }

            if (n->next != NULL)
            {
                n = n->next;
            }
            else
            {


            }
        }
        if (audio_core->buffer_is_new) process_leds(gui, audio_core);

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

        while (SDL_PollEvent(&gui->event))
        {

            if (process_switches(gui, audio_core))exit(EXIT_FAILURE);
            if (process_pots(gui, audio_core, mouse_is_down))exit(EXIT_FAILURE);
            if (process_buttons(gui, audio_core, &midi_peripheral))exit(EXIT_FAILURE);

            switch (gui->event.type)
            {
                case SDL_QUIT:

                    if (prompt_quit())
                    {
                        printf("Quit asked. Closing...\n");
                        gui->application_quit = SDL_TRUE;
                    }
                    break;

                case SDL_KEYDOWN:

                    if (gui->event.key.keysym.sym == SDLK_ESCAPE)
                    {
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
                    //printf("Mouse clic on x=%d, y=%d\n", gui->event.button.x, gui->event.button.y);
                    break;

                case SDL_MOUSEBUTTONUP:

                    mouse_is_down = 0;
                    break;
            }
        }
    }

    exit_gui(gui);

    TTF_Quit();
    SDL_CloseAudio();
    SDL_Quit();

    close_midi_peripheral(midi_peripheral);



    // Free all the data
    free_gui_sdl_objects(gui);
    free_core(audio_core);

    return 0;
}
