//
// Created by robindsj on 09/05/19.
//
#include "keypad.h"
int octave =0;

    int keypress(SDL_Event *event, Core *ac){

        /* Is it a release or a press? */
        if( event->key.type == SDL_KEYUP )
            printf( "Release:- " );
        else
            printf( "Press:- " );

        /* Print the hardware scancode first */
        printf( "Scancode: 0x%02X", event->key.keysym.scancode );

        printf( "\n" );

            switch(event->key.keysym.sym)
            {
                case OCTAVE_R:
                    if (octave>=OCTAVE_MAX){
                        sys_print_error("Octave max atteinte");
                        return -1;
}
                        octave++;
                    break;

                   case OCTAVE_L:
                    if (octave<=OCTAVE_MIN) {
                        sys_print_error("Octave min atteinte");
                        return -1;

                    }

                        octave--;
                    break;

                case SI_KEY:
                midi_note_ON(ac, SI_NOTE+OCTAVE_GAP*octave, 127);
                printf("LA");
                    break;

                    case LA_KEY:
                midi_note_ON(ac, LA_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case MI_KEY:
                midi_note_ON(ac, MI_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case LAd_KEY:
                midi_note_ON(ac, LAd_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case SOL_KEY:
                midi_note_ON(ac, SOL_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case SOLd_KEY:
                midi_note_ON(ac, SOLd_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case FA_KEY:
                midi_note_ON(ac, FA_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case FAd_KEY:
                midi_note_ON(ac, FAd_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case RE_KEY:
                midi_note_ON(ac, RE_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case REd_KEY:
                midi_note_ON(ac, REd_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case DO_KEY:
                midi_note_ON(ac, DO_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                    case DOd_KEY:
                midi_note_ON(ac, DOd_NOTE+OCTAVE_GAP*octave, 127);
                    break;

                case RESET_KEY:
                    for (int i = 20; i < 110; ++i)
                    {
                        midi_note_OFF(ac, i);
                    }
                    break;




            }



return 1;
    }

int keyrelease(SDL_Event *event, Core *ac)
{
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
    return 1;
}
