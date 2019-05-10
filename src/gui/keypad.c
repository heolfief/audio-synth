//
// Created by robindsj on 09/05/19.
//
#include "keypad.h"


    int keypress(SDL_Event *event, Core *ac){

        /* Is it a release or a press? */
        if( event->key.type == SDL_KEYUP )
            printf( "Release:- " );
        else
            printf( "Press:- " );

        /* Print the hardware scancode first */
        printf( "Scancode: 0x%02X", event->key.keysym.scancode );

        printf( "\n" );
switch (key->keysym.scancode){

    case 0x33:  //SI

        break;

    case 0x0F:  //LA

        break;

    case 0x0E:  //SOL

        break;

    case 0x0D:  //FA

        break;

    case 0x0B:  //MI

        break;

    case 0x0A:  //RE

        break;

    case 0x09:  //DO

        break;

    case 0x17:  //DO#

        break;

    case 0x1C:  //RE#

        break;

    case 0x0C:  //FA#

        break;

    case 0x12:  //SOL#

        break;

    case 0x13:  //LA#

        break;
}
    }


