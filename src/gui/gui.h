/**
 * \file gui.h
 * \brief Graphical user interface data structure and function definition.
 *
 *
 * Here are defined the data structure of the gui, and the related functions
 */

#ifndef AUDIO_SYNTH_GUI_H
#define AUDIO_SYNTH_GUI_H

#define NAME_APPLICATION                "INSWAVE"
#define IMAGE_APPLICATION_BACKGROUND    "../src/gui/Figs/background.png"
#define WIDTH_APPLICATION_WINDOW        1300
#define HEIGHT_APPLICATION_WINDOW       816

#define NUMBER_OF_SWITCHES              11
#define NUMBER_OF_MS_SWITCHES           8
#define NUMBER_OF_POTS                  32
#define NUMBER_OF_BUTTONS               9

#define NUMBER_OF_SWITCHES              11
#define NUMBER_OF_MS_SWITCHES           8
#define NUMBER_OF_POTS                  32
#define NUMBER_OF_LEDS                  8
#define NUMBER_OF_TEXTS                 2

#define NUMBER_OF_TOUCH 12

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

#define IMAGE_POT_BIG                   "../src/gui/Figs/big_pot.png"
#define WIDTH_POT_BIG                   65
#define HEIGHT_POT_BIG                  65
#define BIG_POT                         1
#define SMALL_POT                       0

#define IMAGE_BUTTON_LOAD_PRESSED       "../src/gui/Figs/load_clicked.png"
#define IMAGE_BUTTON_LOAD_UNPRESSED     "../src/gui/Figs/load.png"
#define WIDTH_BUTTON_LOAD               60
#define HEIGHT_BUTTON_LOAD              19

#define IMAGE_BUTTON_SAVE_PRESSED       "../src/gui/Figs/save_clicked.png"
#define IMAGE_BUTTON_SAVE_UNPRESSED     "../src/gui/Figs/save.png"
#define WIDTH_BUTTON_SAVE               60
#define HEIGHT_BUTTON_SAVE              19

#define IMAGE_BUTTON_MIDI_STANDBY       "../src/gui/Figs/bt_keyboard_MIDI.png"
#define IMAGE_BUTTON_MIDI_CONNECTED     "../src/gui/Figs/bt_midi_connected.png"
#define WIDTH_BUTTON_MIDI               75
#define HEIGHT_BUTTON_MIDI              52

#define IMAGE_BUTTON_RECORD_UNPRESSED    "../src/gui/Figs/record_button.png"
#define IMAGE_BUTTON_RECORD_PRESSED      "../src/gui/Figs/record_pressed.png"
#define WIDTH_BUTTON_RECORD             50
#define HEIGHT_BUTTON_RECORD            50

#define IMAGE_BUTTON_STOP_UNPRESSED     "../src/gui/Figs/stop_button.png"
#define IMAGE_BUTTON_STOP_PRESSED       "../src/gui/Figs/stop_pressed.png"
#define WIDTH_BUTTON_STOP               60
#define HEIGHT_BUTTON_STOP              60

#define IMAGE_BUTTON_MIDI_PLAY_UNPRESSED     "../src/gui/Figs/button_play_MIDI.png"
#define IMAGE_BUTTON_MIDI_PLAY_PRESSED       "../src/gui/Figs/play_on.png"
#define WIDTH_BUTTON_MIDI_PLAY               30
#define HEIGHT_BUTTON_MIDI_PLAY              34

#define IMAGE_BUTTON_MIDI_PAUSE_UNPRESSED     "../src/gui/Figs/button_pause_MIDI.png"
#define IMAGE_BUTTON_MIDI_PAUSE_PRESSED       "../src/gui/Figs/pause_on.png"
#define WIDTH_BUTTON_MIDI_PAUSE              30
#define HEIGHT_BUTTON_MIDI_PAUSE              33

#define IMAGE_BUTTON_MIDI_STOP_UNPRESSED     "../src/gui/Figs/button_stop_MIDI.png"
#define IMAGE_BUTTON_MIDI_STOP_PRESSED       "../src/gui/Figs/stop_on.png"
#define WIDTH_BUTTON_MIDI_STOP               30
#define HEIGHT_BUTTON_MIDI_STOP              30

#define FONT_PRESET_NAME                "../src/gui/Figs/Minion_Pro_Bold.ttf"
#define SIZE_FONT_PRESET_NAME           17
#define COLOR_R_FONT_PRESET_NAME        151
#define COLOR_G_FONT_PRESET_NAME        187
#define COLOR_B_FONT_PRESET_NAME        186
#define LOCATION_X_PRESET_NAME          119
#define LOCATION_Y_PRESET_NAME          705
#define LOCATION_X_MIDI_TEXT            296
#define LOCATION_Y_MIDI_TEXT            680

#define IMAGE_MS_SWITCH_MAX_STATES      4
#define POT_INCREMENT                   1

#define IMAGE_LED_ON_GREEN                 "../src/gui/Figs/led_on_green.png"
#define IMAGE_LED_ON_ORANGE                "../src/gui/Figs/led_on_orange.png"
#define IMAGE_LED_ON_RED                   "../src/gui/Figs/led_on_red.png"
#define IMAGE_LED_OFF_RED                   "../src/gui/Figs/led_off_red.png"
#define IMAGE_LED_OFF_ORANGE                "../src/gui/Figs/led_off_orange.png"
#define IMAGE_LED_OFF_GREEN                 "../src/gui/Figs/led_off_green.png"
#define WIDTH_LED                       25
#define HEIGHT_LED                      25

#define TOUCH_ON        "../src/gui/Figs/touch_on.png"
#define TOUCH_OFF       "../src/gui/Figs/touch_off.png"
#define WIDTH_TOUCH        23
#define HEIGHT_TOUCH        35

#define ICON_IMAGE      "../src/gui/Figs/logo.png"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/audio_core.h"
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "SDL_Button.h"
#include "tinyfiledialogs.h"
#include "../sys_param/xml/preset_xml.h"
#include "../audio/wav.h"
#include "../midi/midi_keyboard.h"

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
  SDL_Texture *texture;/*!<the SDL texture of the potentiometer */
  Uint8 size;                  /*!<the size of the pot. Can be small (0) or big (1) */
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
<<<<<<< HEAD
 * \struct Text
 * \brief define an SDL text
 *
 */
typedef struct
{
  TTF_Font *font;             /*!<the text font */
  SDL_Color color;            /*!<the text color */
  SDL_Surface *text_surface;  /*!<the SDL surface of the text */
  SDL_Rect rect;              /*!<the SDL rectangle associated with the text */
} Text;

/**
* \struct Led
* \brief define a graphical LED
*
*/
typedef struct
{
  OnOff OnOffLed;             /*!<the parameter of the led to know if it's on or not*/
  SDL_Button_t *sdl_Led;      /*!<the SDL related objects for the Led */
  SDL_Texture *texture;       /*!<the SDL texture of the Led */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  char *img_led_green;        /*!<the image of the Green Led */
  char *img_led_orange;       /*!<the image of the Orange Led */
  char *img_led_red;          /*!<the image of the Red Led */
  char *img_led_off;          /*!<the image of the Led Off */
  char img_on[33];
} Led;

/**
* \struct Touch
* \brief define a graphical touch
*
*/
typedef struct
{
  OnOff OnOffTouch;           /*!<the parameter of the Touch to know if it's on or not*/
  SDL_Button_t *sdl_Touch;    /*!<the SDL related objects for the Touch */
  SDL_Texture *texture;       /*!<the SDL texture of the Touch */
  Uint16 posX;                /*!<the X position on the screen (in pixels) */
  Uint16 posY;                /*!<the Y position on the screen (in pixels) */
  Uint16 width;               /*!<the width (in pixels) */
  Uint16 height;              /*!<the height (in pixels) */
  char *img_touch_on;         /*!<the image of the Green Led */
  char *img_touch_off;        /*!<the image of the Orange Led */
} Touch;

/**
 * \struct Gui
 * \brief define a Gui structure
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
  Switch *switches;
  Multi_state_Switch *ms_switches;
  Potentiometer *pots;
  Button *buttons;
  Text *texts;
  Led *Leds;
  Touch *touch;
} Gui;

/**
 * \fn int init_gui(Gui *gui)
 * \brief Function to initialize GUI (open application window)
 *
 * \param gui The Gui object to init
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int init_gui(Gui *gui);

/**
 * \fn void exit_gui(Gui *gui)
 * \brief Function to exit GUI (close application window)
 *
 * \param gui The Gui object to exit
 */
void exit_gui(Gui *gui);

/**
 * \fn Gui *alloc_gui()
 * \brief Function to allocate memory for a Gui
 *
 * \return the allocated Gui
 */
Gui *alloc_gui();

/**
 * \fn int free_gui(Gui *gui)
 * \brief Function to free memory of an Gui
 *
 * \param gui The Gui object to free
 *
 * \return 0
 */
int free_gui(Gui *gui);

/**
 * \fn int gui_update(Gui *gui)
 * \brief Function to update the display of the GUI
 *
 * \param gui The Gui object to display
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int gui_update(Gui *gui);

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
 * \fn int create_Text_map(Gui *gui)
 * \brief Function to place and initialize text
 *
 * \param gui The Gui object
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_Text_map(Gui *gui);

/**
 * \fn int create_switches_map(Gui *gui, Sys_param *sys_param)
 * \brief Function to place and initialize GUI switches
 *
 * \param gui The Gui object
 * \param sys_param The system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_switches_map(Gui *gui, Sys_param *sys_param);

/**
 * \fn int create_leds_map(Gui *gui, Sys_param *sys_param)
 * \brief Function to place and initialize GUI leds
 *
 * \param gui The Gui object
 * \param sys_param The system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */

int create_Leds_map(Gui *gui, Sys_param *sys_param);
/**
 * \fn int create_touch_map(Gui *gui, Sys_param *sys_param)
 * \brief Function to place and initialize GUI touch
 *
 * \param gui The Gui object
 * \param sys_param The system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */

int create_touch_map(Gui *gui, Sys_param *sys_param);
/**
 * \fn int create_buttons_map(Gui *gui)
 * \brief Function to place and initialize GUI buttons
 *
 * \param gui The Gui object
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_buttons_map(Gui *gui);

/**
 * \fn int create_pots_map(Gui *gui, Sys_param *sys_param)
 * \brief Function to place and initialize GUI potentiometers
 *
 * \param gui The Gui object
 * \param sys_param The system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int create_pots_map(Gui *gui, Sys_param *sys_param);

/**
 * \fn int process_buttons(Gui *gui)
 * \brief Function to check switches status, change parameter accordingly and update switch image
 *
 * \param gui The Gui object
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_switches(Gui *gui, Core *audio_core);

/**
 * \fn int process_buttons(Gui *gui, Core *audio_core, MIDI_Peripheral_fd* midi_peripheral)
 * \brief Function to check buttons status, change parameter accordingly and update button image
 *
 * \param gui The Gui object
 * \param audio_core The system's audio core
 * \param midi_peripheral the MIDI peripheral file descriptor address
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_buttons(Gui *gui, Core *audio_core, MIDI_Peripheral_fd *midi_peripheral);

/**
 * \fn int process_pots(Gui *gui)
 * \brief Function to check pots status, change parameter accordingly and set image rotation
 *
 * \param gui The Gui object
 * \param audio_core The system's audio core
 * \param mouse_is_down Flag for mouse button pressed down
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_pots(Gui *gui, Core *audio_core, Uint8 mouse_is_down);



/**
 * \fn int process_leds(Gui *gui)
 * \brief Function to check leds status, change image accordingly and free the sdl and texture of the led if not on
 *
 * \param gui The Gui object
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_leds(Gui *gui, Core *audio_core);

/**
 * \fn int process_touch(Gui *gui)
 * \brief Function to turn on touch, change image accordingly and free the sdl and texture of the led if not on
 *
 * \param gui The Gui object
 * \param audio_core The system's audio core
 * \param id the note played
 * \param is the note starting or stopping
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_touch(Gui *gui, Uint8 id, Uint8 mode);

/**
 * \fn int change_pot_percent(Gui *gui, int potnbr, Uint8 mouse_is_down)
 * \brief Function to check change pot percent according to mouse movement or mousewheel
 *
 * \param gui The Gui object
 * \param potnbr the number of the pot being processed
 * \param mouse_is_down flag if mouse button is pressed
 *
 * \return 0 if everything went OK, -1 otherwise
 */
 int change_pot_percent(Gui *gui, int potnbr, Uint8 mouse_is_down);

/**
 * \fn int load_sys_param_to_gui(Gui *gui, Sys_param *sys_param)
 * \brief Function to load all the system parameters to the GUI (set pots and switches rotation/status accordingly)
 *
 * \param gui The Gui object
 * \param audio_core The system's audio core
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int load_sys_param_to_gui(Gui *gui, Sys_param *sys_param);

/**
 * \fn int prompt_quit()
 * \brief Function to prompt the user with exit message
 *
 * \return 1 if yes, 0 if no
 */
Uint8 prompt_quit();

/**
 * \fn Sint8 levelVUMeter(Audio_Buffer *average_level_audio)

 * \brief Function to compute with the "ln" function the average audio level in order to adapt it to our number of "LEDs" forming our VUMeter.
 *
 *
 * \param Audio_Buffer The average_level_audio
 *
 * \return returns an int between 1 and 8, to know which LED to light up and -1 if something goes wrong
 */
Sint8 levelVUMeter(Audio_Buffer average_audio_level);

#endif //AUDIO_SYNTH_GUI_H
