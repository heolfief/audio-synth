/**
 * \file gui.h
 * \brief Graphical user interface data structure and function definition.
 *
 *
 * Here are defined the data structure of the gui, and the related functions
 */

#ifndef AUDIO_SYNTH_GUI_H
#define AUDIO_SYNTH_GUI_H

#define NAME_APPLICATION "audio_synth"
#define IMAGE_APPLICATION_BACKGROUND    "../src/gui/Figs/background.png"
#define WIDTH_APPLICATION_WINDOW        1300
#define HEIGHT_APPLICATION_WINDOW       816

#define NUMBER_OF_SWITCHES 11
#define NUMBER_OF_MS_SWITCHES 8
#define NUMBER_OF_POTS 32
#define NUMBER_OF_LEDS 8

#define NUMBER_OF_BUTTONS 3

#define IMAGE_SWITCH_ON                 "../src/gui/Figs/switch_on.png"
#define IMAGE_SWITCH_OFF                "../src/gui/Figs/switch_off.png"
#define WIDTH_SWITCH                    40
#define HEIGHT_SWITCH                   20

#define IMAGE_MS_SWITCH_WAVE_SIN        "../src/gui/Figs/sinus.png"
#define IMAGE_MS_SWITCH_WAVE_SQR        "../src/gui/Figs/square.png"
#define IMAGE_MS_SWITCH_WAVE_TRI        "../src/gui/Figs/triangle.png"
#define IMAGE_MS_SWITCH_TYPE_LP         "../src/gui/Figs/lowpass.png"
#define IMAGE_MS_SWITCH_TYPE_HP         "../src/gui/Figs/highpass.png"
#define IMAGE_MS_SWITCH_TYPE_BP         "../src/gui/Figs/bandpass.png"
#define IMAGE_MS_SWITCH_TYPE_NOTCH      "../src/gui/Figs/notch.png"
#define WIDTH_MS_SWITCH_WIDTH           60
#define HEIGHT_MS_SWITCH                28

#define IMAGE_POT_SMALL                 "../src/gui/Figs/small_pot.png"
#define WIDTH_POT_SMALL                 45
#define HEIGHT_POT_SMALL                46

#define IMAGE_POT_LARGE                 "../src/gui/Figs/big_pot.png"
#define WIDTH_POT_LARGE                 65
#define HEIGHT_POT_LARGE                65

#define IMAGE_BUTTON_LOAD_PRESSED       "../src/gui/Figs/load_clicked.png"
#define IMAGE_BUTTON_LOAD_UNPRESSED     "../src/gui/Figs/load.png"
#define WIDTH_BUTTON_LOAD               60
#define HEIGHT_BUTTON_LOAD              19

#define IMAGE_BUTTON_SAVE_PRESSED       "../src/gui/Figs/save_clicked.png"
#define IMAGE_BUTTON_SAVE_UNPRESSED     "../src/gui/Figs/save.png"
#define WIDTH_BUTTON_SAVE               60
#define HEIGHT_BUTTON_SAVE              19

#define IMAGE_BUTTON_MIDI_STANDBY       "../src/gui/Figs/bt_midi_standby.png"
#define IMAGE_BUTTON_MIDI_CONNECTED     "../src/gui/Figs/bt_midi_connected.png"
#define WIDTH_BUTTON_MIDI               66
#define HEIGHT_BUTTON_MIDI              30

#define IMAGE_MS_SWITCH_MAX_STATES      4
#define POT_INCREMENT                   1

#define IMAGE_LED_GREEN                 "../src/gui/Figs/green_jauge.png"
#define IMAGE_LED_ORANGE                "../src/gui/Figs/orange_jauge.png"
#define IMAGE_LED_RED                   "../src/gui/Figs/red_jauge.png"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/audio_core.h"
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "SDL_Button.h"
#include "tinyfiledialogs.h"
#include "../sys_param/xml/preset_xml.h"
#include "../midi/midi.h"

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
  OnOff onoff;                /*!<the on/off value of the switch */
  void *param;                /*!<the parameter set by the switch */
} Switch;

/**
 * \struct Multi_state_Switch
 * \brief define a graphical Multi state switch
 */
typedef struct
{
  SDL_Button_t *sdl_button;   /*!<the SDL related objects for the button */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  Uint8 number_of_states;     /*!<the number of different possible states */
  Uint8 curr_state;           /*!<the current state value of the switch */
  void *param;                /*!<the parameter set by the switch */
  char *img[IMAGE_MS_SWITCH_MAX_STATES]; /*!<the images of the different states */
} Multi_state_Switch;

/**
 * \struct Button
 * \brief define a graphical Button
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
  OnOff pressed;              /*!<whether is the button is pressed or not */
} Button;

/**
 * \struct Potentiometer
 * \brief define a graphical potentiometer
 *
 */
typedef struct
{
  SDL_Button_t *sdl_pot;      /*!<the SDL related objects for the potentiometer */
  SDL_Texture *texture;       /*!<the SDL texture of the potentiometer */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  char *img;                  /*!<the image of the potentiometer */
  Uint8 percent;              /*!<the percentage set by the user of the potentiometer */
  void *param;                /*!<the parameter set by the potentiometer */
  double paramMAX;            /*!<the max value of the parameter set by the potentiometer, when percent is 100% */
  double paramMIN;            /*!<the min value of the parameter set by the potentiometer, when percent is 0% */
} Potentiometer;

/**
* \struct Led
* \brief define a graphical LED
*
*/
typedef struct
{
  SDL_Button_t *sdl_Led;      /*!<the SDL related objects for the Led */
  SDL_Texture *texture;       /*!<the SDL texture of the Led */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  char *img_led_green;        /*!<the image of the Green Led */
  char *img_led_orange;       /*!<the image of the Orange Led */
  char *img_led_red;          /*!<the image of the Red Led */
} LED;


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
  Multi_state_Switch *ms_switches;
  Potentiometer *pots;
  Button *buttons;
  LED *Leds;
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
 * \fn int create_buttons_map(Gui_SDL_objects *gui)
 * \brief Function to place and initialize GUI buttons
 *
 * \param gui The Gui_SDL_objects
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_buttons_map(Gui_SDL_objects *gui);

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
 * \brief Function to check switches status, change parameter accordingly and update switch image
 *
 * \param gui The Gui_SDL_objects
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_switches(Gui_SDL_objects *gui, Core *audio_core);

/**
 * \fn int process_buttons(Gui_SDL_objects *gui, Core *audio_core, MIDI_Peripheral_fd* midi_peripheral)
 * \brief Function to check buttons status, change parameter accordingly and update button image
 *
 * \param gui The Gui_SDL_objects
 * \param audio_core The system's audio core
 * \param midi_peripheral the MIDI peripheral file descriptor address
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_buttons(Gui_SDL_objects *gui, Core *audio_core, MIDI_Peripheral_fd *midi_peripheral);

/**
 * \fn int process_pots(Gui_SDL_objects *gui)
 * \brief Function to check pots status, change parameter accordingly and set image rotation
 *
 * \param gui The Gui_SDL_objects
 * \param audio_core The system's audio core
 * \param mouse_is_down Flag for mouse button pressed down
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_pots(Gui_SDL_objects *gui, Core *audio_core, Uint8 mouse_is_down);

/**
 * \fn int change_pot_percent(Gui_SDL_objects *gui, int potnbr, Uint8 mouse_is_down)
 * \brief Function to check change pot percent according to mouse movement or mousewheel
 *
 * \param gui The Gui_SDL_objects
 * \param potnbr the number of the pot being processed
 * \param mouse_is_down flag if mouse button is pressed
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int change_pot_percent(Gui_SDL_objects *gui, int potnbr, Uint8 mouse_is_down);

/**
 * \fn int load_sys_param_to_gui(Gui_SDL_objects *gui, Sys_param *sys_param)
 * \brief Function to load all the system parameters to the GUI (set pots and switches rotation/status accordingly)
 *
 * \param gui The Gui_SDL_objects
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int load_sys_param_to_gui(Gui_SDL_objects *gui, Sys_param *sys_param);

/**
 * \fn int levelVUMeter(Audio_Buffer *average_level_audio)

 * \brief Function to compute with the "ln" function the average audio level in order to adapt it to our number of "LEDs" forming our VUMeter.
 *
 *
 * \param Audio_Buffer The average_level_audio
 *
 * \return returns an int between 1 and 8, to know which LED to light up and -1 if something goes wrong
 */
short int levelVUMeter(Audio_Buffer *average_level_audio);

#endif //AUDIO_SYNTH_GUI_H
