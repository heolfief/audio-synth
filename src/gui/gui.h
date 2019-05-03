/**
 * \file gui.h
 * \brief Graphical user interface data structure and function definition.
 *
 *
 * Here are defined the data structure of the gui, and the related functions
 */

#ifndef AUDIO_SYNTH_GUI_H
#define AUDIO_SYNTH_GUI_H

#define APPLICATION_NAME "audio_synth"

#define APPLICATION_IMAGE_BACKGROUND "../src/gui/Figs/bg_fix_3.BMP"

#define APPLICATION_IMAGE_SWITCH_ON "../src/gui/Figs/toggle_on.png"
#define APPLICATION_IMAGE_SWITCH_OFF "../src/gui/Figs/toggle_off.png"
#define APPLICATION_IMAGE_SWITCH_WIDTH 38
#define APPLICATION_IMAGE_SWITCH_HEIGHT 19

#define APPLICATION_IMAGE_POT "../src/gui/Figs/pot.png"
#define APPLICATION_IMAGE_POT_WIDTH 45
#define APPLICATION_IMAGE_POT_HEIGHT 45

#define POT_INCREMENT 2

#define NUMBER_OF_SWITCHES 9
#define NUMBER_OF_POTS 1

#define APPLICATION_WINDOW_WIDTH 1300
#define APPLICATION_WINDOW_HEIGHT 810

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/audio_core.h"
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "SDL_Button.h"

/**
 * \struct Switch
 * \brief define a graphical Switch
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
} Switch;

/**
 * \struct Potentiometer
 * \brief define a graphical potentiometer
 *
 */
typedef struct
{
  SDL_Button_t *sdl_pot;      /*!<the SDL related objects for the potentiometer */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  char *img;                  /*!<the image of the potentiometer */
  Uint8 percent;              /*!<the percentage set by the user of the potentiometer */
  void *param;                /*!<the parameter set by the potentiometer */
  Sint64 paramMAX;            /*!<the max value of the parameter set by the potentiometer, when percent is 100% */
  Sint64 paramMIN;            /*!<the min value of the parameter set by the potentiometer, when percent is 0% */
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
  SDL_Rect background;
  SDL_Event event;
  Uint8 application_quit;
  Mouse_position *mouse_position;
  Switch *switches;
  Potentiometer *pots;
} Gui_SDL_objects;

/**
 * \fn int init_gui(Gui_SDL_objects *gui)
 * \brief Function to initialize GUI (open application window)
 *
 * \param gui The Gui_SDL_objects to init
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int init_gui(Gui_SDL_objects *gui);

/**
 * \fn void exit_gui(Gui_SDL_objects *gui)
 * \brief Function to exit GUI (close application window)
 *
 * \param gui The Gui_SDL_objects to exit
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

/**
 * \fn int gui_update(Gui_SDL_objects *gui)
 * \brief Function to update the display of the GUI
 *
 * \param gui The Gui_SDL_objects to display
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int gui_update(Gui_SDL_objects *gui);

/**
 * \fn SDL_Button_t *gui_create_button(int x_location, int y_location, int button_width, int button_height, char *path_to_image)
 * \brief Function to create (allocate) a SDL_Button_t
 *
 * \param x_location The x location of the button
 * \param y_location The y location of the button
 * \param button_width The width of the button
 * \param button_height The height of the button
 * \param path_to_image The path to the new button image
 *
 * \return 0 if everything went OK, -1 otherwise
 */
SDL_Button_t *gui_create_button(int x_location, int y_location, int button_width, int button_height, char *path_to_image);

/**
 * \fn int gui_set_button_image(SDL_Button_t *button, char *path_to_image)
 * \brief Function to modify the SDL_Button_t image
 *
 * \param button The SDL_Button_t button
 * \param path_to_image The path to the new button image
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int gui_set_switch_image(SDL_Button_t *button, char *path_to_image);

/**
 * \fn int create_switches_map(Gui_SDL_objects *gui, Sys_param *sys_param)
 * \brief Function to place and initialize GUI switches
 *
 * \param gui The Gui_SDL_objects
 * \param sys_param The system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_switches_map(Gui_SDL_objects *gui, Sys_param *sys_param);

/**
 * \fn int create_pots_map(Gui_SDL_objects *gui, Sys_param *sys_param)
 * \brief Function to place and initialize GUI potentiometers
 *
 * \param gui The Gui_SDL_objects
 * \param sys_param The system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_pots_map(Gui_SDL_objects *gui, Sys_param *sys_param);

/**
 * \fn int process_buttons(Gui_SDL_objects *gui)
 * \brief Function to check buttons status, change parameter accordingly and update button image
 *
 * \param gui The Gui_SDL_objects
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_switches(Gui_SDL_objects *gui, Core *audio_core);

/**
 * \fn int process_pots(Gui_SDL_objects *gui)
 * \brief Function to check pots status, change parameter accordingly and set image rotation
 *
 * \param gui The Gui_SDL_objects
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_pots(Gui_SDL_objects *gui, Core *audio_core);

#endif //AUDIO_SYNTH_GUI_H
