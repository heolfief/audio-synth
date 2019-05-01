/**
 * \file gui.h
 * \brief Graphical user interface data structure and function definition.
 *
 *
 * Here are defined the data structure of the gui, and the related functions
 */

#ifndef AUDIO_SYNTH_GUI_H
#define AUDIO_SYNTH_GUI_H

#define APPLICATION_NAME "Meilleur synthé du monde"

#define APPLICATION_WINDOW_WIDTH 1300
#define APPLICATION_WINDOW_HEIGHT 810

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/audio_core.h"
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "SDL_Button.h"

/**
 * \struct Switch
 * \brief define a graphical switch
 *
 * A Switch is defined with : it's x and y position on the screen,
 * the image of the Switch and the parameter it controls
 */
typedef struct
{
  Uint16 posX;       /*!<the X position on the screen (in pixels) */
  Uint16 posY;       /*!<the Y position on the screen (in pixels) */
  char *img;         /*!<the image of the switch */
  OnOff onoff;       /*!<the state of the switch */
  void *param;       /*!<the parameter set by the switch */
} Switch;

/**
 * \struct Button
 * \brief define a graphical Button
 *
 * A Button is defined with : it's x and y position on the screen,
 * the image of the Button and the parameter it controls
 */
typedef struct
{
  SDL_Button_t *sdl_button;   /*!<the SDL related objects for the button */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  char *imgon;                /*!<the image of the ON button */
  char *imgoff;               /*!<the image of the OFF button */
  OnOff onoff;                /*!<the percentage set by the user of the switch */
  void *param;                /*!<the parameter set by the switch */
} Button;

/**
 * \struct Potentiometer
 * \brief define a graphical potentiometer
 *
 * A Potentiometer is defined with : it's x and y position on the screen, the percentages set of the potentiometer,
 * the image of the potentiometer, the parameter it controls, and the min and max value of ths parameter
 */
typedef struct
{
  Uint16 posX;        /*!<the X position on the screen (in pixels) */
  Uint16 posY;        /*!<the Y position on the screen (in pixels) */
  char *img;         /*!<the image of the potentiometer */
  Uint8 percent;     /*!<the percentage set by the user of the potentiometer */
  void *param;       /*!<the parameter set by the potentiometer */
  Sint64 paramMAX;    /*!<the max value of the parameter set by the potentiometer, when percent is 100% */
  Sint64 paramMIN;    /*!<the min value of the parameter set by the potentiometer, when percent is 0% */
} Potentiometer;

/**
 * \struct Mouse_position
 * \brief define a Gui_SDL_objects structure
 *
 * This structure contains all the SDL GUI data for the application's GUI.
 *
 */
typedef struct
{
  int x;        /*!<the X position of the mouse on the window (in pixels) */
  int y;        /*!<the Y position on the mouse on the window (in pixels) */
} Mouse_position;

/**
 * \struct Gui_SDL_objects
 * \brief define a Gui_SDL_objects structure
 *
 * This structure contains all the SDL GUI data for the application's GUI.
 *
 */
typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Rect rect;
  SDL_Event event;
  Uint8 application_quit;
  Mouse_position *mouse_position;
  Button *test_button;
} Gui_SDL_objects;

/**
 * \fn int init_gui(Gui_SDL_objects *gui)
 * \brief Function to initialize GUI (open application window)
 *
 * \param gui The Gui_SDL_objects to init
 *
 * \return 0
 */
int init_gui(Gui_SDL_objects *gui);

/**
 * \fn void exit_gui(Gui_SDL_objects *gui)
 * \brief Function to exit GUI (close application window)
 *
 * \param gui The Gui_SDL_objects to exit
 *
 * \return 0
 */
void exit_gui(Gui_SDL_objects *gui);

/**
 * \fn Gui_SDL_objects *alloc_gui_sdl_objects()
 * \brief Function to allocate memory for a Gui_SDL_objects
 *
 * \return the allocated Gui_SDL_objects
 */
Gui_SDL_objects *alloc_gui_sdl_objects();

/**
 * \fn int free_gui_sdl_objects(Gui_SDL_objects *gui)
 * \brief Function to free memory of an Gui_SDL_objects
 *
 * \param gui The Gui_SDL_objects to free
 *
 * \return 0
 */
int free_gui_sdl_objects(Gui_SDL_objects *gui);

int gui_set_button_image(SDL_Button_t *button, SDL_Renderer *renderer, char *path_to_image);

SDL_Button_t *gui_create_and_show_button(SDL_Renderer *renderer, int x_location, int y_location, int button_width, int button_height, char *path_to_image);

Button *alloc_button();

int free_button(Button *bt);

#endif //AUDIO_SYNTH_GUI_H
