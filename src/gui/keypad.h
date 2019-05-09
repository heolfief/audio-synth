//
// Created by robindsj on 09/05/19.
//

#ifndef AUDIO_SYNTH_SRC_GUI_KEYPAD_H_
#define AUDIO_SYNTH_SRC_GUI_KEYPAD_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/audio_core.h"
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "tinyfiledialogs.h"
#include "../sys_param/xml/preset_xml.h"
#include "../midi/midi.h"
#include <SDL_events.h>


#endif //AUDIO_SYNTH_SRC_GUI_KEYPAD_H_


typedef struct
{

}key;

int keypress(SDL_KeyboardEvent *key);