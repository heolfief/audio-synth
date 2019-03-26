/**
 * \file gui.h
 * \brief Graphical user interface data structure and function definition.
 *
 *
 * Here are defined the data structure of the gui, and the related functions
 */

#ifndef AUDIO_SYNTH_GUI_H
#define AUDIO_SYNTH_GUI_H

#include <SDL2/SDL_stdinc.h>
#include "../oscillator/osc.h"
#include "../system/error_handler.h"



/**
 * \struct Switch
 * \brief define a graphical switch
 *
 * A Potentiometer is defined with : it's x and y position on the screen, the percentages set of the potentiometer,
 * the image of the potentiometer, the parameter it controls, and the min and max value of ths parameter
 */
typedef struct{
    Uint16      posX;        /*!<the X position on the screen (in pixels) */
    Uint16      posY;        /*!<the Y position on the screen (in pixels) */
    char*       img;         /*!<the image of the switch */
    OnOff       onoff;       /*!<the percentage set by the user of the switch */
    void*       param;       /*!<the parameter set by the switch */
}Switch;

/**
 * \struct Potentiometer
 * \brief define a graphical potentiometer
 *
 * A Potentiometer is defined with : it's x and y position on the screen, the percentages set of the potentiometer,
 * the image of the potentiometer, the parameter it controls, and the min and max value of ths parameter
 */
typedef struct{
    Uint16      posX;        /*!<the X position on the screen (in pixels) */
    Uint16      posY;        /*!<the Y position on the screen (in pixels) */
    char*       img;         /*!<the image of the potentiometer */
    Uint8       percent;     /*!<the percentage set by the user of the potentiometer */
    void*       param;       /*!<the parameter set by the potentiometer */
    Sint64      paramMAX;    /*!<the max value of the parameter set by the potentiometer, when percent is 100% */
    Sint64      paramMIN;    /*!<the min value of the parameter set by the potentiometer, when percent is 0% */
}Potentiometer;


#endif //AUDIO_SYNTH_GUI_H
