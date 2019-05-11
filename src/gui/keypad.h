//
// Created by robindsj on 09/05/19.
//

#ifndef AUDIO_SYNTH_SRC_GUI_KEYPAD_H
#define AUDIO_SYNTH_SRC_GUI_KEYPAD_H

#define OCTAVE_GAP      12

#define SI_KEY      SDLK_m
#define SI_NOTE     71

#define LA_KEY      SDLK_l
#define LA_NOTE     69

#define SOL_KEY      SDLK_k
#define SOL_NOTE     67

#define FA_KEY      SDLK_j
#define FA_NOTE     65

#define MI_KEY      SDLK_h
#define MI_NOTE     64

#define RE_KEY      SDLK_g
#define RE_NOTE     62

#define DO_KEY      SDLK_f
#define DO_NOTE     60

#define LAd_KEY      SDLK_p
#define LAd_NOTE     70

#define SOLd_KEY      SDLK_o
#define SOLd_NOTE     68

#define FAd_KEY      SDLK_i
#define FAd_NOTE     66

#define REd_KEY      SDLK_y
#define REd_NOTE     63

#define DOd_KEY      SDLK_t
#define DOd_NOTE     61

#define OCTAVE_R     SDLK_d
#define OCTAVE_L     SDLK_q
#define RESET_KEY       SDLK_r

#define OCTAVE_MAX      3
#define OCTAVE_MIN      -3

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/audio_core.h"
#include "../system/error_handler.h"
#include "../midi/midi.h"
#include "../gui/gui.h"

/**
 * \fn int keypress(SDL_Event *event, Core *ac)
 * \brief Function to play with keyboard, connect the key pressed with the note to play
 *
 * \param event The key and if is it press or release, *ac the core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int keypress(SDL_Event *event, Core *ac, Gui_SDL_objects* gui);

/**
 * \fn int keyrelease(SDL_Event *event, Core *ac)
 * \brief Function to play with keyboard, connect the key release with the note to stop
 *
 * \param event The key and if is it press or release, *ac the core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int keyrelease(SDL_Event *event, Core *ac);

#endif //AUDIO_SYNTH_SRC_GUI_KEYPAD_H
