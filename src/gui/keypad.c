//
// Created by robindsj on 09/05/19.
//
#include "keypad.h"
int octave = 0;

int keypress(SDL_Event *event, Core *ac, Gui_SDL_objects *gui)
{
    Uint8 *uint8_param;

    if (event == NULL || ac == NULL || gui == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    switch (event->key.keysym.sym)
    {
        case SDLK_KP_PLUS:

            uint8_param = gui->pots[13].param;
            for (int i = 0; i < 10; ++i)
            {
                if ((*uint8_param + 1) < 100)
                {
                    (*uint8_param)++;
                    gui->pots[13].percent++;
                }
            }
            if (gui_update(gui))return -1;
            break;

        case SDLK_KP_MINUS:

            uint8_param = gui->pots[13].param;
            for (int i = 0; i < 10; ++i)
            {
                if ((*uint8_param - 1) > 0)
                {
                    (*uint8_param)--;
                    gui->pots[13].percent--;
                    if (gui_update(gui))return -1;
                }
            }
            break;

        case OCTAVE_R:
            for (int i = 20; i < 110; ++i)
            {
                midi_note_OFF(ac, i);
            }
            if (octave <= OCTAVE_MAX)
            {
                octave++;
            }

            break;

        case OCTAVE_L:
            for (int i = 20; i < 110; ++i)
            {
                midi_note_OFF(ac, i);
            }
            if (octave <= OCTAVE_MIN)
            {
                octave--;
            }
            break;

        case SI_KEY:midi_note_ON(ac, SI_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case LA_KEY:midi_note_ON(ac, LA_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case MI_KEY:midi_note_ON(ac, MI_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case LAd_KEY:midi_note_ON(ac, LAd_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case SOL_KEY:midi_note_ON(ac, SOL_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case SOLd_KEY:midi_note_ON(ac, SOLd_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case FA_KEY:midi_note_ON(ac, FA_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case FAd_KEY:midi_note_ON(ac, FAd_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case RE_KEY:midi_note_ON(ac, RE_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case REd_KEY:midi_note_ON(ac, REd_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case DO_KEY:midi_note_ON(ac, DO_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case DOd_KEY:midi_note_ON(ac, DOd_NOTE + OCTAVE_GAP * octave, 127);
            break;

        case RESET_KEY:
            for (int i = 20; i < 110; ++i)
            {
                midi_note_OFF(ac, i);
            }
            break;

    }

    return 0;
}

int keyrelease(SDL_Event *event, Core *ac)
{
    if (event == NULL || ac == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    switch (event->key.keysym.sym)
    {
        case SI_KEY:midi_note_OFF(ac, SI_NOTE + OCTAVE_GAP * octave);
            break;

        case LA_KEY:midi_note_OFF(ac, LA_NOTE + OCTAVE_GAP * octave);
            break;

        case MI_KEY:midi_note_OFF(ac, MI_NOTE + OCTAVE_GAP * octave);
            break;

        case LAd_KEY:midi_note_OFF(ac, LAd_NOTE + OCTAVE_GAP * octave);
            break;

        case SOL_KEY:midi_note_OFF(ac, SOL_NOTE + OCTAVE_GAP * octave);
            break;

        case SOLd_KEY:midi_note_OFF(ac, SOLd_NOTE + OCTAVE_GAP * octave);
            break;

        case FA_KEY:midi_note_OFF(ac, FA_NOTE + OCTAVE_GAP * octave);
            break;

        case FAd_KEY:midi_note_OFF(ac, FAd_NOTE + OCTAVE_GAP * octave);
            break;

        case RE_KEY:midi_note_OFF(ac, RE_NOTE + OCTAVE_GAP * octave);
            break;

        case REd_KEY:midi_note_OFF(ac, REd_NOTE + OCTAVE_GAP * octave);
            break;

        case DO_KEY:midi_note_OFF(ac, DO_NOTE + OCTAVE_GAP * octave);
            break;

        case DOd_KEY:midi_note_OFF(ac, DOd_NOTE + OCTAVE_GAP * octave);
            break;

    }
    return 0;
}
