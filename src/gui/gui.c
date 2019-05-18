/**
 * \file gui.c
 * \brief Graphical user interface data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the gui, and the related functions
 */

#include "gui.h"
#include "math.h"

Sint8 param_is_being_mouse_changed = -1;
char preset_name[100] = {"default"};

static const int switches_location[NUMBER_OF_SWITCHES][2] = {
    {77, 52},         // Switch osc1 OnOff
    {337, 52},        // Switch osc2 OnOff
    {595, 52},        // Switch osc3 OnOff
    {1074, 209},      // Switch master OnOff
    {94, 313},        // Switch master FX OnOff
    {86, 360},        // Switch effect OnOff
    {291, 360},       // Switch effect OnOff
    {497, 360},       // Switch effect OnOff
    {698, 360},       // Switch effect OnOff
    {894, 360},       // Switch effect OnOff
    {1131, 360}       // Switch effect OnOff
};

static const int ms_switches_location[NUMBER_OF_MS_SWITCHES][2] = {
    {134, 99},        // Osc1 wave
    {391, 99},       // Osc2 wave
    {654, 99},       // Osc3 wave
    {482, 400},       // Tremolo wave
    {680, 400},       // Flanger wave
    {866, 413},       // LFO filter type
    {866, 473},       // LFO filter wave
    {1112, 418},      // Filter type
};

static const int pots_location_and_size[NUMBER_OF_POTS][3] = {
    // OSC1
    {72, 164, SMALL_POT},
    {148, 164, SMALL_POT},
    {225, 164, SMALL_POT},

    // OSC 2
    {327, 164, SMALL_POT},
    {403, 164, SMALL_POT},
    {482, 164, SMALL_POT},

    //OSC3
    {584, 164, SMALL_POT},
    {659, 164, SMALL_POT},
    {736, 164, SMALL_POT},

    // Envelope
    {834, 41, BIG_POT},
    {935, 41, BIG_POT},
    {836, 148, BIG_POT},
    {935, 147, BIG_POT},

    // Master
    {1071, 41, BIG_POT},

    // Distortion
    {73, 433, SMALL_POT},
    {166, 433, SMALL_POT},

    // Delay
    {282, 434, SMALL_POT},
    {378, 434, SMALL_POT},

    // Tremolo
    {475, 449, SMALL_POT},
    {535, 447, SMALL_POT},
    {595, 447, SMALL_POT},

    // Flanger
    {795, 377, SMALL_POT},
    {676, 460, SMALL_POT},
    {735, 460, SMALL_POT},
    {795, 460, SMALL_POT},

    // LFO filter
    {972, 377, SMALL_POT},
    {1031, 377, SMALL_POT},
    {937, 461, SMALL_POT},
    {987, 460, SMALL_POT},
    {1037, 460, SMALL_POT},

    // Filter
    {1224, 395, SMALL_POT},
    {1169, 460, SMALL_POT}
};

static const int buttons_location[NUMBER_OF_BUTTONS][2] = {
    {88, 635},
    {88, 670},
    {270, 645},

    //Locations for the record button
    {410, 649},
    //Location for the stop button
    {480, 649}
};

static const int pot_min_max[NUMBER_OF_POTS][2] = {
    // OSC1
    {0, 32000},
    {0, 100},
    {-24, 24},

    // OSC2
    {0, 32000},
    {0, 100},
    {-24, 24},

    // OSC3
    {0, 32000},
    {0, 100},
    {-24, 24},

    // Envelope
    {0, 2},
    {0, 2},
    {0, 1},
    {0, 2},

    // Master
    {0, 100},

    // Distortion
    {0, 100},
    {0, 100},

    // Delay
    {1, 500},
    {0, 100},

    // Tremolo
    {0, 20},
    {0, 100},
    {0, 100},

    // Flanger
    {0, 20},
    {0, 20},
    {0, 100},
    {0, 100},

    // LFO filter
    {0, 10000},
    {0, 5000},
    {0, 20},
    {0, 30},
    {0, 20},

    // Filter
    {0, 10000},
    {0, 20}
};

static const int leds_location[NUMBER_OF_LEDS][2] = {
    //first green Led
    {1212, 173},

    //Second Green Led
    {1212, 153},

    //Third Green Led
    {1212, 134},

    //4th Green Led
    {1212, 115},

    //5th Green Led
    {1212, 94},

    //First Orange Led
    {1212, 75},

    //Second Orange Led
    {1212, 55},

    //ONLY RED Led
    {1212, 35}

};

static const int touch_location[NUMBER_OF_TOUCH][2] = {
    //DO
    {860, 753},

    //DOd
    {890, 710},

    //RE
    {926, 753},

    //REd
    {951, 710},

    //MI
    {985, 753},

    //FA
    {1049, 753},

    //FAd
    {1087, 710},

    //SOL
    {1114, 753},

    //SOLd
    {1146, 710},

    //LA
    {1175, 753},

    //LAd
    {1194, 710},

    //SI
    {1239, 753}

};

static double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static int getSubString(const char *source, char *target, int from, int to)
{
    int length = 0;
    int i = 0, j = 0;

    //get length
    while (source[i++] != '\0')
    {
        length++;
    }

    if (from < 0 || from > length)
    {
        sys_print_error("Invalid \'from\' index");
        return 1;
    }
    if (to > length)
    {
        sys_print_error("Invalid \'to\' index");
        return 1;
    }

    for (i = from, j = 0; i <= to; i++, j++)
    {
        target[j] = source[i];
    }

    //assign NULL at the end of string
    target[j] = '\0';

    return 0;
}

static int extract_file_name_from_path(const char *path, char *out, int extension_lenght)
{
    int i = 0;
    int pos_of_last_slash = -1;

    while (path[i] != '\0')
    {
        if (path[i] == '/') pos_of_last_slash = i;
        ++i;
    }
    if (pos_of_last_slash == -1)
    {
        sys_print_error("/ Not found in path");
        return -1;
    }

    return getSubString(path, out, pos_of_last_slash + 1, strlen(path) - extension_lenght - 2);
}

int init_gui(Gui *gui)
{
    if (SDL_CreateWindowAndRenderer(WIDTH_APPLICATION_WINDOW, HEIGHT_APPLICATION_WINDOW, SDL_WINDOW_SHOWN, &gui->window, &gui->renderer)
        != 0)
    {
        sys_print_SDL_error("ERROR in creating window and renderer");
        return -1;
    }

    gui->texture =
        SDL_CreateTexture(gui->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH_APPLICATION_WINDOW, HEIGHT_APPLICATION_WINDOW);
    if (NULL == gui->texture)
    {
        sys_print_SDL_error("ERROR creating texture");
        return -1;
    }

    SDL_Surface *tmp = IMG_Load(IMAGE_APPLICATION_BACKGROUND); //Loading the image onto the tmp surface
    if (NULL == tmp)
    {
        sys_print_SDL_error("ERROR loading image");
        return -1;
    }

    gui->texture = SDL_CreateTextureFromSurface(gui->renderer, tmp);
    if (NULL == gui->texture)
    {
        sys_print_SDL_error("ERROR creating texture from surface");
        return -1;
    }


    SDL_Surface*    icon;

    icon = IMG_Load(ICON_IMAGE);
    if (icon != 0)
        SDL_SetWindowIcon(gui->window, icon);



// SDL_Quit() and Co
    SDL_FreeSurface(tmp); // Free the surface, not needed anymore
    SDL_FreeSurface(icon);
    SDL_SetRenderTarget(gui->renderer, NULL);

    gui->background.w = WIDTH_APPLICATION_WINDOW;
    gui->background.h = HEIGHT_APPLICATION_WINDOW;

    if (SDL_RenderCopy(gui->renderer, gui->texture, NULL, &gui->background))
    {
        sys_print_SDL_error("Render Copy failed");
        return -1;
    }
    SDL_SetWindowTitle(gui->window, NAME_APPLICATION);
    SDL_RenderPresent(gui->renderer);

    return 0;
}

void exit_gui(Gui *gui)
{
    if (NULL != gui->texture)
    {
        SDL_DestroyTexture(gui->texture);
    }
    if (NULL != gui->renderer)
    {
        SDL_DestroyRenderer(gui->renderer);
    }
    if (NULL != gui->window)
    {
        SDL_DestroyWindow(gui->window);
    }

}

Gui *alloc_gui()
{
    Gui *gui = (Gui *) malloc(sizeof(Gui));
    if (gui == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    Switch *sw = (Switch *) calloc(NUMBER_OF_SWITCHES, sizeof(Switch));
    if (sw == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->switches = sw;

    Multi_state_Switch *mssw = (Multi_state_Switch *) calloc(NUMBER_OF_MS_SWITCHES, sizeof(Multi_state_Switch));
    if (mssw == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->ms_switches = mssw;

    Potentiometer *pot = (Potentiometer *) calloc(NUMBER_OF_POTS, sizeof(Potentiometer));
    if (pot == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->pots = pot;

    Button *bt = (Button *) calloc(NUMBER_OF_BUTTONS, sizeof(Button));
    if (bt == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->buttons = bt;

    Text *txt = (Text *) malloc(sizeof(Text));
    if (txt == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->preset_name = txt;

    Led *led = (Led *) calloc(NUMBER_OF_LEDS, sizeof(Led));
    if (led == NULL)
    {
        sys_print_error("Memory Allocation error");
        return NULL;
    }
    gui->Leds = led;

    Touch *touch = (Touch *) calloc(NUMBER_OF_TOUCH, sizeof(Touch));
    if (touch == NULL)
    {
        sys_print_error("Memory Allocation error");
        return NULL;
    }
    gui->touch = touch;

    return gui;
}

int free_gui(Gui *gui)
{
    free(gui->switches);
    free(gui->ms_switches);
    free(gui->pots);
    free(gui->buttons);
    free(gui->preset_name);
    free(gui->Leds);
    free(gui->touch);
    free(gui);
    return 0;
}

int gui_update(Gui *gui)
{
    // Render background
    if (SDL_RenderCopy(gui->renderer, gui->texture, NULL, &gui->background))
    {
        sys_print_SDL_error("Render Copy failed");
        return -1;
    }

    // For each switch
    for (int i = 0; i < NUMBER_OF_SWITCHES; ++i)
    {
        SDL_Texture
            *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->switches[i].sdl_button->internal_surface);
        if (tmp == NULL)
        {
            sys_print_SDL_error("Failed creating texture");
            return -1;
        }
        if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, gui->switches[i].sdl_button->location_and_size, 0, NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
        SDL_DestroyTexture(tmp);
    }

    // For each led
    for (int i = 0; i < NUMBER_OF_LEDS; ++i)
    {
        SDL_Texture
            *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->Leds[i].sdl_Led->internal_surface);
        if (tmp == NULL)
        {
            sys_print_SDL_error("Failed creating texture");
            return -1;
        }
        if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, gui->Leds[i].sdl_Led->location_and_size, 0, NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
        SDL_DestroyTexture(tmp);
    }


// For each Touch
    for (int i = 0; i < NUMBER_OF_TOUCH; ++i)
    {
        SDL_Texture
            *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->touch[i].sdl_Touch->internal_surface);
        if (tmp == NULL)
        {
            sys_print_SDL_error("Failed creating texture");
            return -1;
        }
        if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, gui->touch[i].sdl_Touch->location_and_size, 0, NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
        SDL_DestroyTexture(tmp);
    }


    // For each multi state switch
    for (int i = 0; i < NUMBER_OF_MS_SWITCHES; ++i)
    {
        SDL_Texture
            *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->ms_switches[i].sdl_button->internal_surface);
        if (tmp == NULL)
        {
            sys_print_SDL_error("Failed creating texture");
            return -1;
        }
        if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, gui->ms_switches[i].sdl_button->location_and_size, 0, NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
        SDL_DestroyTexture(tmp);
    }

    // For each pot
    for (int i = 0; i < NUMBER_OF_POTS; ++i)
    {
        if (SDL_RenderCopyEx(gui->renderer, gui->pots[i].texture, NULL, gui->pots[i].sdl_pot->location_and_size,
                             map(gui->pots[i].percent, 0, 100, 0, 290), NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
    }

    // For each button
    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
    {
        SDL_Texture
            *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->buttons[i].sdl_button->internal_surface);
        if (tmp == NULL)
        {
            sys_print_SDL_error("Failed creating texture");
            return -1;
        }
        if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, gui->buttons[i].sdl_button->location_and_size, 0, NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
        SDL_DestroyTexture(tmp);
    }

    gui->preset_name->rect.x = LOCATION_X_PRESET_NAME - gui->preset_name->text_surface->w / 2;
    gui->preset_name->rect.w = gui->preset_name->text_surface->w;
    gui->preset_name->rect.h = gui->preset_name->text_surface->h;
    SDL_Texture
        *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->preset_name->text_surface);
    if (tmp == NULL)
    {
        sys_print_SDL_error("Failed creating texture");
        return -1;
    }
    if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, &gui->preset_name->rect, 0, NULL, SDL_FLIP_NONE))
    {
        sys_print_SDL_error("Failed RenderCopy");
        return -1;
    }
    SDL_DestroyTexture(tmp);

    SDL_RenderPresent(gui->renderer);
}

SDL_Button_t *gui_create_button(int x_location, int y_location, int button_width, int button_height, char *path_to_image)
{
    SDL_Button_t *button = NULL;

    SDL_Surface *tmp = NULL;
    button = SDL_Button(tmp, x_location, y_location, button_width, button_height);

    gui_set_switch_image(button, path_to_image);

    return button;
}

int gui_set_switch_image(SDL_Button_t *button, char *path_to_image)
{
    button->internal_surface = IMG_Load(path_to_image);
    if (button->internal_surface == NULL)
    {
        sys_print_SDL_error("Failed loading image");
        return -1;
    }
    return 0;
}

int create_Text_map(Gui *gui)
{
    if (gui == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    gui->preset_name->font = TTF_OpenFont(FONT_PRESET_NAME, SIZE_FONT_PRESET_NAME);
    gui->preset_name->color.r = COLOR_R_FONT_PRESET_NAME;
    gui->preset_name->color.g = COLOR_G_FONT_PRESET_NAME;
    gui->preset_name->color.b = COLOR_B_FONT_PRESET_NAME;
    gui->preset_name->color.a = 0;
    gui->preset_name->text_surface =
        TTF_RenderText_Blended(gui->preset_name->font, preset_name, gui->preset_name->color);
    gui->preset_name->rect.x = LOCATION_X_PRESET_NAME - gui->preset_name->text_surface->w / 2;
    gui->preset_name->rect.y = LOCATION_Y_PRESET_NAME;
    gui->preset_name->rect.w = gui->preset_name->text_surface->w;
    gui->preset_name->rect.h = gui->preset_name->text_surface->h;

    return 0;
}

int create_switches_map(Gui *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    for (int sw = 0; sw < NUMBER_OF_SWITCHES; ++sw)
    {
        gui->switches[sw].onoff = OFF;
        gui->switches[sw].imgoff = IMAGE_SWITCH_OFF;
        gui->switches[sw].imgon = IMAGE_SWITCH_ON;
        gui->switches[sw].posX = switches_location[sw][0];
        gui->switches[sw].posY = switches_location[sw][1];
        gui->switches[sw].width = WIDTH_SWITCH;
        gui->switches[sw].height = HEIGHT_SWITCH;
        gui->switches[sw].sdl_button =
            gui_create_button(gui->switches[sw].posX, gui->switches[sw].posY, gui->switches[sw].width, gui->switches[sw].height, gui->switches[sw].imgoff);
    }

    gui->switches[0].param = &sys_param->osc1->onoff;
    gui->switches[1].param = &sys_param->osc2->onoff;
    gui->switches[2].param = &sys_param->osc3->onoff;
    gui->switches[3].param = &sys_param->master_onoff;
    gui->switches[4].param = &sys_param->master_FX_onoff;
    gui->switches[5].param = &sys_param->dist_param->onoff;
    gui->switches[6].param = &sys_param->delay_param->onoff;
    gui->switches[7].param = &sys_param->amp_mod_param->onoff;
    gui->switches[8].param = &sys_param->flanger_param->onoff;
    gui->switches[9].param = &sys_param->lfo_filter_param->onoff;
    gui->switches[10].param = &sys_param->filter_param->onoff;

    gui->ms_switches[0].img[0] = IMAGE_MS_SWITCH_WAVE_SIN;
    gui->ms_switches[0].img[1] = IMAGE_MS_SWITCH_WAVE_SQR;
    gui->ms_switches[0].img[2] = IMAGE_MS_SWITCH_WAVE_TRI;
    gui->ms_switches[0].param = &sys_param->osc1->wave;
    gui->ms_switches[0].number_of_states = 3;

    gui->ms_switches[1].img[0] = IMAGE_MS_SWITCH_WAVE_SIN;
    gui->ms_switches[1].img[1] = IMAGE_MS_SWITCH_WAVE_SQR;
    gui->ms_switches[1].img[2] = IMAGE_MS_SWITCH_WAVE_TRI;
    gui->ms_switches[1].param = &sys_param->osc2->wave;
    gui->ms_switches[1].number_of_states = 3;

    gui->ms_switches[2].img[0] = IMAGE_MS_SWITCH_WAVE_SIN;
    gui->ms_switches[2].img[1] = IMAGE_MS_SWITCH_WAVE_SQR;
    gui->ms_switches[2].img[2] = IMAGE_MS_SWITCH_WAVE_TRI;
    gui->ms_switches[2].param = &sys_param->osc3->wave;
    gui->ms_switches[2].number_of_states = 3;

    gui->ms_switches[3].img[0] = IMAGE_MS_SWITCH_WAVE_SIN;
    gui->ms_switches[3].img[1] = IMAGE_MS_SWITCH_WAVE_SQR;
    gui->ms_switches[3].img[2] = IMAGE_MS_SWITCH_WAVE_TRI;
    gui->ms_switches[3].param = &sys_param->amp_mod_param->wave;
    gui->ms_switches[3].number_of_states = 3;

    gui->ms_switches[4].img[0] = IMAGE_MS_SWITCH_WAVE_SIN;
    gui->ms_switches[4].img[1] = IMAGE_MS_SWITCH_WAVE_SQR;
    gui->ms_switches[4].img[2] = IMAGE_MS_SWITCH_WAVE_TRI;
    gui->ms_switches[4].param = &sys_param->flanger_param->lfo_wave;
    gui->ms_switches[4].number_of_states = 3;

    gui->ms_switches[5].img[0] = IMAGE_MS_SWITCH_TYPE_LP;
    gui->ms_switches[5].img[1] = IMAGE_MS_SWITCH_TYPE_HP;
    gui->ms_switches[5].img[2] = IMAGE_MS_SWITCH_TYPE_BP;
    gui->ms_switches[5].img[3] = IMAGE_MS_SWITCH_TYPE_NOTCH;
    gui->ms_switches[5].param = &sys_param->lfo_filter_param->filter_type;
    gui->ms_switches[5].number_of_states = 4;

    gui->ms_switches[6].img[0] = IMAGE_MS_SWITCH_WAVE_SIN;
    gui->ms_switches[6].img[1] = IMAGE_MS_SWITCH_WAVE_SQR;
    gui->ms_switches[6].img[2] = IMAGE_MS_SWITCH_WAVE_TRI;
    gui->ms_switches[6].param = &sys_param->lfo_filter_param->wave;
    gui->ms_switches[6].number_of_states = 3;

    gui->ms_switches[7].img[0] = IMAGE_MS_SWITCH_TYPE_LP;
    gui->ms_switches[7].img[1] = IMAGE_MS_SWITCH_TYPE_HP;
    gui->ms_switches[7].img[2] = IMAGE_MS_SWITCH_TYPE_BP;
    gui->ms_switches[7].img[3] = IMAGE_MS_SWITCH_TYPE_NOTCH;
    gui->ms_switches[7].param = &sys_param->filter_param->filter_type;
    gui->ms_switches[7].number_of_states = 4;

    for (int mssw = 0; mssw < NUMBER_OF_MS_SWITCHES; ++mssw)
    {
        gui->ms_switches[mssw].curr_state = 0;
        gui->ms_switches[mssw].posX = ms_switches_location[mssw][0];
        gui->ms_switches[mssw].posY = ms_switches_location[mssw][1];
        gui->ms_switches[mssw].width = WIDTH_MS_SWITCH_WIDTH;
        gui->ms_switches[mssw].height = HEIGHT_MS_SWITCH;
        gui->ms_switches[mssw].sdl_button =
            gui_create_button(gui->ms_switches[mssw].posX, gui->ms_switches[mssw].posY, gui->ms_switches[mssw].width, gui->ms_switches[mssw].height, gui->ms_switches[mssw].img[gui->ms_switches[mssw].curr_state]);
    }

    return 0;
}

int create_touch_map(Gui *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    for (int nbtouch = 0; nbtouch < NUMBER_OF_TOUCH; ++nbtouch)
    {
        gui->touch[nbtouch].img_touch_on = TOUCH_ON;
        gui->touch[nbtouch].img_touch_off = TOUCH_OFF;
        gui->touch[nbtouch].posX = touch_location[nbtouch][0];
        gui->touch[nbtouch].posY = touch_location[nbtouch][1];
        gui->touch[nbtouch].width = WIDTH_TOUCH;
        gui->touch[nbtouch].height = HEIGHT_TOUCH;
        gui->touch[nbtouch].sdl_Touch =
            gui_create_button(gui->touch[nbtouch].posX, gui->touch[nbtouch].posY, gui->touch[nbtouch].width, gui->touch[nbtouch].height, gui->touch[nbtouch].img_touch_off);
    }
    return 0;
}

int create_Leds_map(Gui *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    for (int nbLeds = 0; nbLeds < NUMBER_OF_LEDS - 3; ++nbLeds)
    {
        gui->Leds[nbLeds].img_led_green = IMAGE_LED_ON_GREEN;
        gui->Leds[nbLeds].img_led_off = IMAGE_LED_OFF_GREEN;
        gui->Leds[nbLeds].posX = leds_location[nbLeds][0];
        gui->Leds[nbLeds].posY = leds_location[nbLeds][1];
        gui->Leds[nbLeds].width = WIDTH_LED;
        gui->Leds[nbLeds].height = HEIGHT_LED;
        gui->Leds[nbLeds].sdl_Led =
            gui_create_button(gui->Leds[nbLeds].posX, gui->Leds[nbLeds].posY, gui->Leds[nbLeds].width, gui->Leds[nbLeds].height, gui->Leds[nbLeds].img_led_green);
    }

    for (int nbLeds = NUMBER_OF_LEDS - 3; nbLeds < NUMBER_OF_LEDS - 1; ++nbLeds)
    {
        gui->Leds[nbLeds].img_led_orange = IMAGE_LED_ON_ORANGE;
        gui->Leds[nbLeds].img_led_off = IMAGE_LED_OFF_ORANGE;
        gui->Leds[nbLeds].posX = leds_location[nbLeds][0];
        gui->Leds[nbLeds].posY = leds_location[nbLeds][1];
        gui->Leds[nbLeds].width = WIDTH_LED;
        gui->Leds[nbLeds].height = HEIGHT_LED;
        gui->Leds[nbLeds].sdl_Led =
            gui_create_button(gui->Leds[nbLeds].posX, gui->Leds[nbLeds].posY, gui->Leds[nbLeds].width, gui->Leds[nbLeds].height, gui->Leds[nbLeds].img_led_orange);
    }
    for (int nbLeds = NUMBER_OF_LEDS - 1; nbLeds < NUMBER_OF_LEDS; ++nbLeds)
    {
        gui->Leds[nbLeds].img_led_red = IMAGE_LED_ON_RED;
        gui->Leds[nbLeds].img_led_off = IMAGE_LED_OFF_RED;
        gui->Leds[nbLeds].posX = leds_location[nbLeds][0];
        gui->Leds[nbLeds].posY = leds_location[nbLeds][1];
        gui->Leds[nbLeds].width = WIDTH_LED;
        gui->Leds[nbLeds].height = HEIGHT_LED;
        gui->Leds[nbLeds].sdl_Led =
            gui_create_button(gui->Leds[nbLeds].posX, gui->Leds[nbLeds].posY, gui->Leds[nbLeds].width, gui->Leds[nbLeds].height, gui->Leds[nbLeds].img_led_red);
    }
    return 0;

}
int create_buttons_map(Gui *gui)
{
    if (gui == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    gui->buttons[0].imgon = IMAGE_BUTTON_LOAD_PRESSED;
    gui->buttons[0].imgoff = IMAGE_BUTTON_LOAD_UNPRESSED;
    gui->buttons[0].width = WIDTH_BUTTON_SAVE;
    gui->buttons[0].height = HEIGHT_BUTTON_SAVE;

    gui->buttons[1].imgon = IMAGE_BUTTON_SAVE_PRESSED;
    gui->buttons[1].imgoff = IMAGE_BUTTON_SAVE_UNPRESSED;
    gui->buttons[1].width = WIDTH_BUTTON_LOAD;
    gui->buttons[1].height = HEIGHT_BUTTON_LOAD;

    gui->buttons[2].imgon = IMAGE_BUTTON_MIDI_CONNECTED;
    gui->buttons[2].imgoff = IMAGE_BUTTON_MIDI_STANDBY;
    gui->buttons[2].width = WIDTH_BUTTON_MIDI;
    gui->buttons[2].height = HEIGHT_BUTTON_MIDI;

    //Record buttons
    gui->buttons[3].imgon = IMAGE_BUTTON_RECORD_PRESSED;
    gui->buttons[3].imgoff = IMAGE_BUTTON_RECORD_UNPRESSED;
    gui->buttons[3].width = WIDTH_BUTTON_RECORD;
    gui->buttons[3].height = HEIGHT_BUTTON_RECORD;

    //STOP recording button
    gui->buttons[4].imgon = IMAGE_BUTTON_STOP_PRESSED;
    gui->buttons[4].imgoff = IMAGE_BUTTON_STOP_UNPRESSED;
    gui->buttons[4].width = WIDTH_BUTTON_STOP;
    gui->buttons[4].height = HEIGHT_BUTTON_STOP;

    for (int bt = 0; bt < NUMBER_OF_BUTTONS; ++bt)
    {
        gui->buttons[bt].pressed = 0;
        gui->buttons[bt].posX = buttons_location[bt][0];
        gui->buttons[bt].posY = buttons_location[bt][1];
        gui->buttons[bt].sdl_button =
            gui_create_button(gui->buttons[bt].posX, gui->buttons[bt].posY, gui->buttons[bt].width, gui->buttons[bt].height, gui->buttons[bt].imgoff);
    }

    return 0;
}

int create_pots_map(Gui *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    for (int pot = 0; pot < NUMBER_OF_POTS; ++pot)
    {
        gui->pots[pot].size = pots_location_and_size[pot][2];

        if (gui->pots[pot].size == SMALL_POT)
        {
            gui->pots[pot].percent = 0;
            gui->pots[pot].img = IMAGE_POT_SMALL;
            gui->pots[pot].posX = pots_location_and_size[pot][0];
            gui->pots[pot].posY = pots_location_and_size[pot][1];
            gui->pots[pot].paramMIN = pot_min_max[pot][0];
            gui->pots[pot].paramMAX = pot_min_max[pot][1];
            gui->pots[pot].width = WIDTH_POT_SMALL;
            gui->pots[pot].height = HEIGHT_POT_SMALL;
            gui->pots[pot].sdl_pot =
                gui_create_button(gui->pots[pot].posX, gui->pots[pot].posY, gui->pots[pot].width, gui->pots[pot].height, gui->pots[pot].img);
            gui->pots[pot].texture =
                SDL_CreateTextureFromSurface(gui->renderer, gui->pots[pot].sdl_pot->internal_surface);
            if (gui->pots[pot].texture == NULL)
            {
                sys_print_SDL_error("Failed creating texture");
                return -1;
            }

        }
        if (gui->pots[pot].size == BIG_POT)
        {
            gui->pots[pot].percent = 0;
            gui->pots[pot].img = IMAGE_POT_BIG;
            gui->pots[pot].posX = pots_location_and_size[pot][0];
            gui->pots[pot].posY = pots_location_and_size[pot][1];
            gui->pots[pot].paramMIN = pot_min_max[pot][0];
            gui->pots[pot].paramMAX = pot_min_max[pot][1];
            gui->pots[pot].width = WIDTH_POT_BIG;
            gui->pots[pot].height = HEIGHT_POT_BIG;
            gui->pots[pot].sdl_pot =
                gui_create_button(gui->pots[pot].posX, gui->pots[pot].posY, gui->pots[pot].width, gui->pots[pot].height, gui->pots[pot].img);
            gui->pots[pot].texture =
                SDL_CreateTextureFromSurface(gui->renderer, gui->pots[pot].sdl_pot->internal_surface);
            if (gui->pots[pot].texture == NULL)
            {
                sys_print_SDL_error("Failed creating texture");
                return -1;
            }
        }

    }

    gui->pots[0].param = &sys_param->osc1->amp;
    gui->pots[1].param = &sys_param->osc1->duty;
    gui->pots[2].param = &sys_param->osc1->detune;
    gui->pots[3].param = &sys_param->osc2->amp;
    gui->pots[4].param = &sys_param->osc2->duty;
    gui->pots[5].param = &sys_param->osc2->detune;
    gui->pots[6].param = &sys_param->osc3->amp;
    gui->pots[7].param = &sys_param->osc3->duty;
    gui->pots[8].param = &sys_param->osc3->detune;
    gui->pots[9].param = &sys_param->env->attack;
    gui->pots[10].param = &sys_param->env->decay;
    gui->pots[11].param = &sys_param->env->sustain;
    gui->pots[12].param = &sys_param->env->release;
    gui->pots[13].param = &sys_param->master_volume;
    gui->pots[14].param = &sys_param->dist_param->dist_level;
    gui->pots[15].param = &sys_param->dist_param->wet;
    gui->pots[16].param = &sys_param->delay_param->delay;
    gui->pots[17].param = &sys_param->delay_param->feedback;
    gui->pots[18].param = &sys_param->amp_mod_param->freq;
    gui->pots[19].param = &sys_param->amp_mod_param->duty;
    gui->pots[20].param = &sys_param->amp_mod_param->mod_level;
    gui->pots[21].param = &sys_param->flanger_param->lfo_freq;
    gui->pots[22].param = &sys_param->flanger_param->delay;
    gui->pots[23].param = &sys_param->flanger_param->lfo_range;
    gui->pots[24].param = &sys_param->flanger_param->depth;
    gui->pots[25].param = &sys_param->lfo_filter_param->filter_freq;
    gui->pots[26].param = &sys_param->lfo_filter_param->filter_excursion;
    gui->pots[27].param = &sys_param->lfo_filter_param->lfo_freq;
    gui->pots[28].param = &sys_param->lfo_filter_param->duty;
    gui->pots[29].param = &sys_param->lfo_filter_param->resonance;
    gui->pots[30].param = &sys_param->filter_param->cutoff_freq;
    gui->pots[31].param = &sys_param->filter_param->resonance;

    return 0;
}

int process_switches(Gui *gui, Core *audio_core)
{
    OnOff *onoff_param = NULL;
    Waveform *wave_param = NULL;
    Filter_type *type_param = NULL;
    int param_changed = 0;

    if (gui == NULL || audio_core == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    for (int sw = 0; sw < NUMBER_OF_SWITCHES; ++sw)
    {
        if (SDL_Button_mouse_down(gui->switches[sw].sdl_button, &gui->event))
        {
            if (gui->switches[sw].onoff)    // If ON
            {
                if (gui_set_switch_image(gui->switches[sw].sdl_button, gui->switches[sw].imgoff))return -1;
                gui->switches[sw].onoff = OFF;

                onoff_param = gui->switches[sw].param;
                *onoff_param = OFF;
            }
            else
            {
                if (gui_set_switch_image(gui->switches[sw].sdl_button, gui->switches[sw].imgon))return -1;
                gui->switches[sw].onoff = ON;

                onoff_param = gui->switches[sw].param;
                *onoff_param = ON;
            }
            param_changed = 1;
        }
    }

    if (SDL_Button_mouse_down(gui->ms_switches[0].sdl_button, &gui->event))
    {
        gui->ms_switches[0].curr_state =
            (gui->ms_switches[0].curr_state + 1) % gui->ms_switches[0].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[0].sdl_button, gui->ms_switches[0].img[gui->ms_switches[0].curr_state]))return -1;
        wave_param = gui->ms_switches[0].param;
        *wave_param = gui->ms_switches[0].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[1].sdl_button, &gui->event))
    {
        gui->ms_switches[1].curr_state =
            (gui->ms_switches[1].curr_state + 1) % gui->ms_switches[1].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[1].sdl_button, gui->ms_switches[1].img[gui->ms_switches[1].curr_state]))return -1;
        wave_param = gui->ms_switches[1].param;
        *wave_param = gui->ms_switches[1].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[2].sdl_button, &gui->event))
    {
        gui->ms_switches[2].curr_state =
            (gui->ms_switches[2].curr_state + 1) % gui->ms_switches[2].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[2].sdl_button, gui->ms_switches[2].img[gui->ms_switches[2].curr_state]))return -1;
        wave_param = gui->ms_switches[2].param;
        *wave_param = gui->ms_switches[2].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[3].sdl_button, &gui->event))
    {
        gui->ms_switches[3].curr_state =
            (gui->ms_switches[3].curr_state + 1) % gui->ms_switches[3].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[3].sdl_button, gui->ms_switches[3].img[gui->ms_switches[3].curr_state]))return -1;
        wave_param = gui->ms_switches[3].param;
        *wave_param = gui->ms_switches[3].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[4].sdl_button, &gui->event))
    {
        gui->ms_switches[4].curr_state =
            (gui->ms_switches[4].curr_state + 1) % gui->ms_switches[4].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[4].sdl_button, gui->ms_switches[4].img[gui->ms_switches[4].curr_state]))return -1;
        wave_param = gui->ms_switches[4].param;
        *wave_param = gui->ms_switches[4].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[5].sdl_button, &gui->event))
    {
        gui->ms_switches[5].curr_state =
            (gui->ms_switches[5].curr_state + 1) % gui->ms_switches[5].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[5].sdl_button, gui->ms_switches[5].img[gui->ms_switches[5].curr_state]))return -1;
        type_param = gui->ms_switches[5].param;
        *type_param = gui->ms_switches[5].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[6].sdl_button, &gui->event))
    {
        gui->ms_switches[6].curr_state =
            (gui->ms_switches[6].curr_state + 1) % gui->ms_switches[6].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[6].sdl_button, gui->ms_switches[6].img[gui->ms_switches[6].curr_state]))return -1;
        wave_param = gui->ms_switches[6].param;
        *wave_param = gui->ms_switches[6].curr_state;

        param_changed = 1;
    }
    else if (SDL_Button_mouse_down(gui->ms_switches[7].sdl_button, &gui->event))
    {
        gui->ms_switches[7].curr_state =
            (gui->ms_switches[7].curr_state + 1) % gui->ms_switches[7].number_of_states;
        if (gui_set_switch_image(gui->ms_switches[7].sdl_button, gui->ms_switches[7].img[gui->ms_switches[7].curr_state]))return -1;
        type_param = gui->ms_switches[7].param;
        *type_param = gui->ms_switches[7].curr_state;

        param_changed = 1;
    }

    if (param_changed)
    {
        // Each time oscillator parameters changed, this function needs to be called
        if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

        // Each time a filter parameter is changed, this function needs to be called
        if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

        if (gui_update(gui))return -1;
    }

    return 0;
}

int process_buttons(Gui *gui, Core *audio_core, MIDI_Peripheral_fd *midi_peripheral)
{
    int param_changed = 0;
    int reload_param = 0;
    char const *path;
    char const *RecordPath;
    char const *lFilterPatterns[1] = {"*.prst"};
    char const *WavFilterPatterns[1] = {"*.wav"};
    if (gui == NULL || audio_core == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    // Button LOAD preset
    if (SDL_Button_mouse_down(gui->buttons[0].sdl_button, &gui->event))
    {
        if (gui_set_switch_image(gui->buttons[0].sdl_button, gui->buttons[0].imgon))return -1;
        if (gui_update(gui))return -1;

        path = tinyfd_openFileDialog("Load a preset", "../presets", 1, lFilterPatterns, NULL, 0);
        if (path)
        {
            if (load_preset(path, audio_core->sys_param, ABSOLUTE_PATH_MODE))return -1;
            extract_file_name_from_path(path, preset_name, 4);
            gui->preset_name->text_surface =
                TTF_RenderText_Blended(gui->preset_name->font, preset_name, gui->preset_name->color);
            reload_param = 1;
        }
        if (gui_set_switch_image(gui->buttons[0].sdl_button, gui->buttons[0].imgoff))return -1;
        param_changed = 1;
    }

    // Button SAVE preset
    if (SDL_Button_mouse_down(gui->buttons[1].sdl_button, &gui->event))
    {
        if (gui_set_switch_image(gui->buttons[1].sdl_button, gui->buttons[1].imgon))return -1;
        if (gui_update(gui))return -1;

        path = tinyfd_saveFileDialog("Load a preset", "../presets/.prst", 1, lFilterPatterns, NULL);
        if (path)
        {
            if (save_preset(path, audio_core->sys_param, ABSOLUTE_PATH_MODE))return -1;
            extract_file_name_from_path(path, preset_name, 4);
            gui->preset_name->text_surface =
                TTF_RenderText_Blended(gui->preset_name->font, preset_name, gui->preset_name->color);
        }
        if (gui_set_switch_image(gui->buttons[1].sdl_button, gui->buttons[1].imgoff))return -1;
        param_changed = 1;
    }

    // Button MIDI connect
    if (SDL_Button_mouse_down(gui->buttons[2].sdl_button, &gui->event))
    {
        if (gui->buttons[2].pressed == 0)
        {
            *midi_peripheral = open_midi_peripheral();
            if (*midi_peripheral == -1)
            {
                sys_print_error("Failed opening MIDI device.");
                tinyfd_messageBox("Error", "No MIDI device found.", "ok", "error", 1);
                return 0;
            }

            gui->buttons[2].pressed = 1;
            if (gui_set_switch_image(gui->buttons[2].sdl_button, gui->buttons[2].imgon))return -1;
            if (gui_update(gui))return -1;
        }
    }

    // Button RECORD wav file
    if (SDL_Button_mouse_down(gui->buttons[3].sdl_button, &gui->event))
    {
        if (gui_set_switch_image(gui->buttons[3].sdl_button, gui->buttons[3].imgon))return -1;
        if (gui_update(gui))return -1;

        RecordPath =
            tinyfd_saveFileDialog("Record your musical talent in a wav file", "../.wav", 1, WavFilterPatterns, NULL);
        if (RecordPath)
        {
            //Opening the selected file in order to record
            open_wav_file(RecordPath, audio_core);

            //setting up the flag to record wav file
            audio_core->record_param->RecordOnOff = ON;

        }
        else
        {
            if (gui_set_switch_image(gui->buttons[3].sdl_button, gui->buttons[3].imgoff))return -1;
            if (gui_update(gui))return -1;
        }
    }

    // Button STOP wav file
    if (SDL_Button_mouse_down(gui->buttons[4].sdl_button, &gui->event))
    {
        if (gui_set_switch_image(gui->buttons[4].sdl_button, gui->buttons[4].imgon))return -1;
        if (gui_update(gui))return -1;

        if (audio_core->record_param->RecordOnOff)
        {
            if (tinyfd_messageBox("Recording session", "Looks like you stopped the recording. Were you playing this bad that you want to quit ?\n Feel free to try again ", "yesno", "question", 0))
            {
                //switching off the recording session
                audio_core->record_param->RecordOnOff = OFF;
                close_wav_file(audio_core->record_param->sndFile);
            }

        }
        else
        {
            tinyfd_messageBox("Recording session", "I believe that in order to stop the recording, you should probably start recording first ?\n Feel free to try to record your exploits ", "yes", "ok", 1);
        }

        if (gui_set_switch_image(gui->buttons[3].sdl_button, gui->buttons[3].imgoff))return -1;
        if (gui_set_switch_image(gui->buttons[4].sdl_button, gui->buttons[4].imgoff))return -1;

        if (gui_update(gui))return -1;
    }

    if (param_changed)
    {
        // Each time oscillator parameters changed, this function needs to be called
        if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

        // Each time a filter parameter is changed, this function needs to be called
        if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

        if (reload_param) load_sys_param_to_gui(gui, audio_core->sys_param);

        if (gui_update(gui))return -1;
    }

    return 0;
}

int process_pots(Gui *gui, Core *audio_core, Uint8 mouse_is_down)
{
    double *double_param = NULL;
    Uint8 *uint8_param = NULL;
    Uint16 *uint16_param = NULL;
    Sint8 *sint8_param = NULL;

    int param_changed = 0;
    int mouseX, mouseY;

    if (gui == NULL || audio_core == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    if (gui->event.type == SDL_MOUSEWHEEL || gui->event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&mouseX, &mouseY);

        if (param_is_being_mouse_changed != -1)  // If a parameter is being changed by the mouse
        {
            if (!mouse_is_down)
            {
                param_is_being_mouse_changed = -1;
                return 0;
            }
            change_pot_percent(gui, param_is_being_mouse_changed, mouse_is_down);
            param_changed = 1;
        }
        // OSC1
        if ((mouse_on_button(gui->pots[0].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 0))
        {
            change_pot_percent(gui, 0, mouse_is_down);
            uint16_param = gui->pots[0].param;
            *uint16_param =
                (Uint16) map(gui->pots[0].percent, 0, 100, gui->pots[0].paramMIN, gui->pots[0].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[1].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 1))
        {
            change_pot_percent(gui, 1, mouse_is_down);
            uint8_param = gui->pots[1].param;
            *uint8_param = (Uint8) map(gui->pots[1].percent, 0, 100, gui->pots[1].paramMIN, gui->pots[1].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[2].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 2))
        {
            change_pot_percent(gui, 2, mouse_is_down);
            sint8_param = gui->pots[2].param;
            *sint8_param = (Sint8) map(gui->pots[2].percent, 0, 100, gui->pots[2].paramMIN, gui->pots[2].paramMAX);
            param_changed = 1;
        }
            // OSC 2
        else if ((mouse_on_button(gui->pots[3].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 3))
        {
            change_pot_percent(gui, 3, mouse_is_down);
            uint16_param = gui->pots[3].param;
            *uint16_param =
                (Uint16) map(gui->pots[3].percent, 0, 100, gui->pots[3].paramMIN, gui->pots[3].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[4].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 4))
        {
            change_pot_percent(gui, 4, mouse_is_down);
            uint8_param = gui->pots[4].param;
            *uint8_param = (Uint8) map(gui->pots[4].percent, 0, 100, gui->pots[4].paramMIN, gui->pots[4].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[5].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 5))
        {
            change_pot_percent(gui, 5, mouse_is_down);
            sint8_param = gui->pots[5].param;
            *sint8_param = (Sint8) map(gui->pots[5].percent, 0, 100, gui->pots[5].paramMIN, gui->pots[5].paramMAX);
            param_changed = 1;
        }
            // OSC 3
        else if ((mouse_on_button(gui->pots[6].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 6))
        {
            change_pot_percent(gui, 6, mouse_is_down);
            uint16_param = gui->pots[6].param;
            *uint16_param =
                (Uint16) map(gui->pots[6].percent, 0, 100, gui->pots[6].paramMIN, gui->pots[6].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[7].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 7))
        {
            change_pot_percent(gui, 7, mouse_is_down);
            uint8_param = gui->pots[7].param;
            *uint8_param = (Uint8) map(gui->pots[7].percent, 0, 100, gui->pots[7].paramMIN, gui->pots[7].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[8].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 8))
        {
            change_pot_percent(gui, 8, mouse_is_down);
            sint8_param = gui->pots[8].param;
            *sint8_param = (Sint8) map(gui->pots[8].percent, 0, 100, gui->pots[8].paramMIN, gui->pots[8].paramMAX);
            param_changed = 1;
        }
            // Envelope
        else if ((mouse_on_button(gui->pots[9].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 9))
        {
            change_pot_percent(gui, 9, mouse_is_down);
            double_param = gui->pots[9].param;
            *double_param =
                (double) map(gui->pots[9].percent, 0, 100, gui->pots[9].paramMIN, gui->pots[9].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[10].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 10))
        {
            change_pot_percent(gui, 10, mouse_is_down);
            double_param = gui->pots[10].param;
            *double_param =
                (double) map(gui->pots[10].percent, 0, 100, gui->pots[10].paramMIN, gui->pots[10].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[11].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 11))
        {
            change_pot_percent(gui, 11, mouse_is_down);
            double_param = gui->pots[11].param;
            *double_param =
                (double) map(gui->pots[11].percent, 0, 100, gui->pots[11].paramMIN, gui->pots[11].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[12].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 12))
        {
            change_pot_percent(gui, 12, mouse_is_down);
            double_param = gui->pots[12].param;
            *double_param =
                (double) map(gui->pots[12].percent, 0, 100, gui->pots[12].paramMIN, gui->pots[12].paramMAX);
            param_changed = 1;
        }
            // MASTER VOLUME
        else if ((mouse_on_button(gui->pots[13].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 13))
        {
            change_pot_percent(gui, 13, mouse_is_down);
            uint8_param = gui->pots[13].param;
            *uint8_param =
                (Uint8) map(gui->pots[13].percent, 0, 100, gui->pots[13].paramMIN, gui->pots[13].paramMAX);
            param_changed = 1;
        }
            // Distortion
        else if ((mouse_on_button(gui->pots[14].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 14))
        {
            change_pot_percent(gui, 14, mouse_is_down);
            uint8_param = gui->pots[14].param;
            *uint8_param =
                (Uint8) map(gui->pots[14].percent, 0, 100, gui->pots[14].paramMIN, gui->pots[14].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[15].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 15))
        {
            change_pot_percent(gui, 15, mouse_is_down);
            uint8_param = gui->pots[15].param;
            *uint8_param =
                (Uint8) map(gui->pots[15].percent, 0, 100, gui->pots[15].paramMIN, gui->pots[15].paramMAX);
            param_changed = 1;
        }
            // Delay
        else if ((mouse_on_button(gui->pots[16].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 16))
        {
            change_pot_percent(gui, 16, mouse_is_down);
            double_param = gui->pots[16].param;
            *double_param =
                (double) map(gui->pots[16].percent, 0, 100, gui->pots[16].paramMIN, gui->pots[16].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[17].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 17))
        {
            change_pot_percent(gui, 17, mouse_is_down);
            uint8_param = gui->pots[17].param;
            *uint8_param =
                (Uint8) map(gui->pots[17].percent, 0, 100, gui->pots[17].paramMIN, gui->pots[17].paramMAX);
            param_changed = 1;
        }
            // Amp mod
        else if ((mouse_on_button(gui->pots[18].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 18))
        {
            change_pot_percent(gui, 18, mouse_is_down);
            double_param = gui->pots[18].param;
            *double_param =
                (double) map(gui->pots[18].percent, 0, 100, gui->pots[18].paramMIN, gui->pots[18].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[19].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 19))
        {
            change_pot_percent(gui, 19, mouse_is_down);
            uint8_param = gui->pots[19].param;
            *uint8_param =
                (Uint8) map(gui->pots[19].percent, 0, 100, gui->pots[19].paramMIN, gui->pots[19].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[20].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 20))
        {
            change_pot_percent(gui, 20, mouse_is_down);
            uint8_param = gui->pots[20].param;
            *uint8_param =
                (Uint8) map(gui->pots[20].percent, 0, 100, gui->pots[20].paramMIN, gui->pots[20].paramMAX);
            param_changed = 1;
        }
            // Flanger
        else if ((mouse_on_button(gui->pots[21].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 21))
        {
            change_pot_percent(gui, 21, mouse_is_down);
            double_param = gui->pots[21].param;
            *double_param =
                (double) map(gui->pots[21].percent, 0, 100, gui->pots[21].paramMIN, gui->pots[21].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[22].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 22))
        {
            change_pot_percent(gui, 22, mouse_is_down);
            double_param = gui->pots[22].param;
            *double_param =
                (double) map(gui->pots[22].percent, 0, 100, gui->pots[22].paramMIN, gui->pots[22].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[23].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 23))
        {
            change_pot_percent(gui, 23, mouse_is_down);
            uint8_param = gui->pots[23].param;
            *uint8_param =
                (Uint8) map(gui->pots[23].percent, 0, 100, gui->pots[23].paramMIN, gui->pots[23].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[24].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 24))
        {
            change_pot_percent(gui, 24, mouse_is_down);
            uint8_param = gui->pots[24].param;
            *uint8_param =
                (Uint8) map(gui->pots[24].percent, 0, 100, gui->pots[24].paramMIN, gui->pots[24].paramMAX);
            param_changed = 1;
        }
            // LFO filter
        else if ((mouse_on_button(gui->pots[25].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 25))
        {
            change_pot_percent(gui, 25, mouse_is_down);
            uint16_param = gui->pots[25].param;
            *uint16_param =
                (Uint16) map(gui->pots[25].percent, 0, 100, gui->pots[25].paramMIN, gui->pots[25].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[26].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 26))
        {
            change_pot_percent(gui, 26, mouse_is_down);
            uint16_param = gui->pots[26].param;
            *uint16_param =
                (Uint16) map(gui->pots[26].percent, 0, 100, gui->pots[26].paramMIN, gui->pots[26].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[27].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 27))
        {
            change_pot_percent(gui, 27, mouse_is_down);
            double_param = gui->pots[27].param;
            *double_param =
                (double) map(gui->pots[27].percent, 0, 100, gui->pots[27].paramMIN, gui->pots[27].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[28].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 28))
        {
            change_pot_percent(gui, 28, mouse_is_down);
            uint8_param = gui->pots[28].param;
            *uint8_param =
                (Uint8) map(gui->pots[28].percent, 0, 100, gui->pots[28].paramMIN, gui->pots[28].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[29].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 29))
        {
            change_pot_percent(gui, 29, mouse_is_down);
            double_param = gui->pots[29].param;
            *double_param =
                (double) map(gui->pots[29].percent, 0, 100, gui->pots[29].paramMIN, gui->pots[29].paramMAX);
            param_changed = 1;
        }
            // Filter
        else if ((mouse_on_button(gui->pots[30].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 30))
        {
            change_pot_percent(gui, 30, mouse_is_down);
            uint16_param = gui->pots[30].param;
            *uint16_param =
                (Uint16) map(gui->pots[30].percent, 0, 100, gui->pots[30].paramMIN, gui->pots[30].paramMAX);
            param_changed = 1;
        }
        else if ((mouse_on_button(gui->pots[31].sdl_pot->location_and_size, mouseX, mouseY)
            && (param_is_being_mouse_changed == -1))
            || (param_is_being_mouse_changed == 31))
        {
            change_pot_percent(gui, 31, mouse_is_down);
            double_param = gui->pots[31].param;
            *double_param =
                (double) map(gui->pots[31].percent, 0, 100, gui->pots[31].paramMIN, gui->pots[31].paramMAX);
            param_changed = 1;
        }
    }

    if (param_changed)
    {
        // Each time oscillator parameters changed, this function needs to be called
        if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

        // Each time a filter parameter is changed, this function needs to be called
        if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

        if (gui_update(gui))return -1;
    }

    return 0;
}

int process_touch(Gui *gui, Uint8 id, Uint8 mode)
{
    if (gui == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    short int note_played;
    note_played = id - 60;

    for (int nbtouch = 0; nbtouch < NUMBER_OF_TOUCH; ++nbtouch)
    {

        if (mode == 1)
        {
            gui->touch[note_played].OnOffTouch = ON;

        }
        else
        {
            gui->touch[note_played].OnOffTouch = OFF;

        }
    }
    for (int nbtouch = 0; nbtouch < NUMBER_OF_TOUCH; ++nbtouch)
    {

        if (gui->touch[nbtouch].OnOffTouch == ON)    // If ON
        {
            if (gui_set_switch_image(gui->touch[nbtouch].sdl_Touch, gui->touch[nbtouch].img_touch_on))
            {
                sys_print_error("wrong image to load");
                return -1;
            }
        }
        else
        {
            if (gui_set_switch_image(gui->touch[nbtouch].sdl_Touch, gui->touch[nbtouch].img_touch_off))
            {
                sys_print_error("wrong image to load");
                return -1;

            }
        }
    }
    gui_update(gui);

    return 0;
}

int process_leds(Gui *gui, Core *audio_core)
{

    if (gui == NULL || audio_core == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    short int ledsResults;
    ledsResults = levelVUMeter(audio_core->average_audio_level);

    if (ledsResults == 0)
    {
        gui->Leds[0].OnOffLed = OFF;
        gui->Leds[1].OnOffLed = OFF;
        gui->Leds[2].OnOffLed = OFF;
        gui->Leds[3].OnOffLed = OFF;
        gui->Leds[4].OnOffLed = OFF;
        gui->Leds[5].OnOffLed = OFF;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 1)
    {
        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = OFF;
        gui->Leds[2].OnOffLed = OFF;
        gui->Leds[3].OnOffLed = OFF;
        gui->Leds[4].OnOffLed = OFF;
        gui->Leds[5].OnOffLed = OFF;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 2)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = OFF;
        gui->Leds[3].OnOffLed = OFF;
        gui->Leds[4].OnOffLed = OFF;
        gui->Leds[5].OnOffLed = OFF;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }
    if (ledsResults == 3)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = ON;
        gui->Leds[3].OnOffLed = OFF;
        gui->Leds[4].OnOffLed = OFF;
        gui->Leds[5].OnOffLed = OFF;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 4)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = ON;
        gui->Leds[3].OnOffLed = ON;
        gui->Leds[4].OnOffLed = OFF;
        gui->Leds[5].OnOffLed = OFF;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 5)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = ON;
        gui->Leds[3].OnOffLed = ON;
        gui->Leds[4].OnOffLed = ON;
        gui->Leds[5].OnOffLed = OFF;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 6)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = ON;
        gui->Leds[3].OnOffLed = ON;
        gui->Leds[4].OnOffLed = ON;
        gui->Leds[5].OnOffLed = ON;
        gui->Leds[6].OnOffLed = OFF;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 7)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = ON;
        gui->Leds[3].OnOffLed = ON;
        gui->Leds[4].OnOffLed = ON;
        gui->Leds[5].OnOffLed = ON;
        gui->Leds[6].OnOffLed = ON;
        gui->Leds[7].OnOffLed = OFF;
    }

    if (ledsResults == 8)
    {

        gui->Leds[0].OnOffLed = ON;
        gui->Leds[1].OnOffLed = ON;
        gui->Leds[2].OnOffLed = ON;
        gui->Leds[3].OnOffLed = ON;
        gui->Leds[4].OnOffLed = ON;
        gui->Leds[5].OnOffLed = ON;
        gui->Leds[6].OnOffLed = ON;
        gui->Leds[7].OnOffLed = ON;
    }
    //updating the flag about the buffer being new
    audio_core->buffer_is_new = 0;

    for (int nbLeds = 0; nbLeds < NUMBER_OF_LEDS; ++nbLeds)
    {

        if (gui->Leds[nbLeds].OnOffLed == ON)    // If ON
        {
            if (nbLeds < NUMBER_OF_LEDS - 3)
            {
                if (gui_set_switch_image(gui->Leds[nbLeds].sdl_Led, gui->Leds[nbLeds].img_led_green))
                {
                    sys_print_error("wrong image to load");
                    return -1;
                }
            }
            if (nbLeds < NUMBER_OF_LEDS - 1 && nbLeds >= NUMBER_OF_LEDS - 3)
            {
                if (gui_set_switch_image(gui->Leds[nbLeds].sdl_Led, gui->Leds[nbLeds].img_led_orange))
                {
                    sys_print_error("wrong image to load");
                    return -1;
                }

            }
            if (nbLeds == NUMBER_OF_LEDS - 1)
            {
                if (gui_set_switch_image(gui->Leds[nbLeds].sdl_Led, gui->Leds[nbLeds].img_led_red))
                {
                    sys_print_error("wrong image to load");
                    return -1;
                }

            }

        }
        else
        {
            if (gui_set_switch_image(gui->Leds[nbLeds].sdl_Led, gui->Leds[nbLeds].img_led_off))
            {
                return -1;
                sys_print_error("wrong image to load");
            }
        }

    }
    gui_update(gui);

    return 0;

}

int change_pot_percent(Gui *gui, int potnbr, Uint8 mouse_is_down)
{
    if (gui->event.type == SDL_MOUSEWHEEL)
    {
        if (((double) gui->pots[potnbr].percent + (double) gui->event.wheel.y * (double) POT_INCREMENT) > 100)
        {
            gui->pots[potnbr].percent = 100;
        }
        else if (((double) gui->pots[potnbr].percent + (double) gui->event.wheel.y * (double) POT_INCREMENT) < 0)
        {
            gui->pots[potnbr].percent = 0;
        }
        else
        {
            gui->pots[potnbr].percent += gui->event.wheel.y * POT_INCREMENT;
        }
    }
    else if (gui->event.type == SDL_MOUSEMOTION && mouse_is_down)
    {
        if (param_is_being_mouse_changed == -1) param_is_being_mouse_changed = potnbr;

        if (((double) gui->pots[potnbr].percent - (double) gui->event.motion.yrel) > 100)
        {
            gui->pots[potnbr].percent = 100;
        }
        else if (((double) gui->pots[potnbr].percent - (double) gui->event.motion.yrel) < 0)
        {
            gui->pots[potnbr].percent = 0;
        }
        else
        {
            gui->pots[potnbr].percent -= gui->event.motion.yrel;
        }
    }
}

int load_sys_param_to_gui(Gui *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    OnOff *onoff_param = NULL;
    double *double_param = NULL;
    Uint8 *uint8_param = NULL;
    Uint16 *uint16_param = NULL;
    Sint8 *sint8_param = NULL;
    Waveform *wave_param = NULL;
    Filter_type *type_param = NULL;

    for (int sw = 0; sw < NUMBER_OF_SWITCHES; ++sw)
    {
        onoff_param = gui->switches[sw].param;
        gui->switches[sw].onoff = *onoff_param;
        if (gui->switches[sw].onoff == ON)
        {
            if (gui_set_switch_image(gui->switches[sw].sdl_button, gui->switches[sw].imgon))return -1;
        }
        else
        {
            if (gui_set_switch_image(gui->switches[sw].sdl_button, gui->switches[sw].imgoff))return -1;
        }
    }

    wave_param = gui->ms_switches[0].param;
    gui->ms_switches[0].curr_state = *wave_param;

    wave_param = gui->ms_switches[1].param;
    gui->ms_switches[1].curr_state = *wave_param;

    wave_param = gui->ms_switches[2].param;
    gui->ms_switches[2].curr_state = *wave_param;

    wave_param = gui->ms_switches[3].param;
    gui->ms_switches[3].curr_state = *wave_param;

    wave_param = gui->ms_switches[4].param;
    gui->ms_switches[4].curr_state = *wave_param;

    type_param = gui->ms_switches[5].param;
    gui->ms_switches[5].curr_state = *type_param;

    wave_param = gui->ms_switches[6].param;
    gui->ms_switches[6].curr_state = *wave_param;

    type_param = gui->ms_switches[7].param;
    gui->ms_switches[7].curr_state = *type_param;

    for (int mssw = 0; mssw < NUMBER_OF_MS_SWITCHES; ++mssw)
    {
        if (gui_set_switch_image(gui->ms_switches[mssw].sdl_button, gui->ms_switches[mssw].img[gui->ms_switches[mssw].curr_state]))return -1;
    }

    for (int i = 0; i < 100; ++i)
    {
        // OSC 1
        uint16_param = gui->pots[0].param;
        if ((double) gui->pots[0].percent < map(*uint16_param, gui->pots[0].paramMIN, gui->pots[0].paramMAX, 0, 100))
        { gui->pots[0].percent++; }
        else
        { gui->pots[0].percent--; }

        uint8_param = gui->pots[1].param;
        if ((double) gui->pots[1].percent < map(*uint8_param, gui->pots[1].paramMIN, gui->pots[1].paramMAX, 0, 100))
        { gui->pots[1].percent++; }
        else
        { gui->pots[1].percent--; }

        sint8_param = gui->pots[2].param;
        if ((double) gui->pots[2].percent < map(*sint8_param, gui->pots[2].paramMIN, gui->pots[2].paramMAX, 0, 100))
        { gui->pots[2].percent++; }
        else
        { gui->pots[2].percent--; }

        // OSC 2
        uint16_param = gui->pots[3].param;
        if ((double) gui->pots[3].percent < map(*uint16_param, gui->pots[3].paramMIN, gui->pots[3].paramMAX, 0, 100))
        { gui->pots[3].percent++; }
        else
        { gui->pots[3].percent--; }

        uint8_param = gui->pots[4].param;
        if ((double) gui->pots[4].percent < map(*uint8_param, gui->pots[4].paramMIN, gui->pots[4].paramMAX, 0, 100))
        { gui->pots[4].percent++; }
        else
        { gui->pots[4].percent--; }

        sint8_param = gui->pots[5].param;
        if ((double) gui->pots[5].percent < map(*sint8_param, gui->pots[5].paramMIN, gui->pots[5].paramMAX, 0, 100))
        { gui->pots[5].percent++; }
        else
        { gui->pots[5].percent--; }

        // OSC 3
        uint16_param = gui->pots[6].param;
        if ((double) gui->pots[6].percent < map(*uint16_param, gui->pots[6].paramMIN, gui->pots[6].paramMAX, 0, 100))
        { gui->pots[6].percent++; }
        else
        { gui->pots[6].percent--; }

        uint8_param = gui->pots[1].param;
        if ((double) gui->pots[7].percent < map(*uint8_param, gui->pots[7].paramMIN, gui->pots[7].paramMAX, 0, 100))
        { gui->pots[7].percent++; }
        else
        { gui->pots[7].percent--; }

        sint8_param = gui->pots[8].param;
        if ((double) gui->pots[8].percent < map(*sint8_param, gui->pots[8].paramMIN, gui->pots[8].paramMAX, 0, 100))
        { gui->pots[8].percent++; }
        else
        { gui->pots[8].percent--; }

        // Envelope
        double_param = gui->pots[9].param;
        if ((double) gui->pots[9].percent < map(*double_param, gui->pots[9].paramMIN, gui->pots[9].paramMAX, 0, 100))
        { gui->pots[9].percent++; }
        else
        { gui->pots[9].percent--; }

        double_param = gui->pots[10].param;
        if ((double) gui->pots[10].percent < map(*double_param, gui->pots[10].paramMIN, gui->pots[10].paramMAX, 0, 100))
        { gui->pots[10].percent++; }
        else
        { gui->pots[10].percent--; }

        double_param = gui->pots[11].param;
        if ((double) gui->pots[11].percent < map(*double_param, gui->pots[11].paramMIN, gui->pots[11].paramMAX, 0, 100))
        { gui->pots[11].percent++; }
        else
        { gui->pots[11].percent--; }

        double_param = gui->pots[12].param;
        if ((double) gui->pots[12].percent < map(*double_param, gui->pots[12].paramMIN, gui->pots[12].paramMAX, 0, 100))
        { gui->pots[12].percent++; }
        else
        { gui->pots[12].percent--; }

        // Master volume
        uint8_param = gui->pots[13].param;
        if ((double) gui->pots[13].percent < map(*uint8_param, gui->pots[13].paramMIN, gui->pots[13].paramMAX, 0, 100))
        { gui->pots[13].percent++; }
        else
        { gui->pots[13].percent--; }

        // Distortion
        uint8_param = gui->pots[14].param;
        if ((double) gui->pots[14].percent < map(*uint8_param, gui->pots[14].paramMIN, gui->pots[14].paramMAX, 0, 100))
        { gui->pots[14].percent++; }
        else
        { gui->pots[14].percent--; }

        uint8_param = gui->pots[15].param;
        if ((double) gui->pots[15].percent < map(*uint8_param, gui->pots[15].paramMIN, gui->pots[15].paramMAX, 0, 100))
        { gui->pots[15].percent++; }
        else
        { gui->pots[15].percent--; }

        // Delay
        double_param = gui->pots[16].param;
        if ((double) gui->pots[16].percent < map(*double_param, gui->pots[16].paramMIN, gui->pots[16].paramMAX, 0, 100))
        { gui->pots[16].percent++; }
        else
        { gui->pots[16].percent--; }

        uint8_param = gui->pots[17].param;
        if ((double) gui->pots[17].percent < map(*uint8_param, gui->pots[17].paramMIN, gui->pots[17].paramMAX, 0, 100))
        { gui->pots[17].percent++; }
        else
        { gui->pots[17].percent--; }

        // Amp mod
        double_param = gui->pots[18].param;
        if ((double) gui->pots[18].percent < map(*double_param, gui->pots[18].paramMIN, gui->pots[18].paramMAX, 0, 100))
        { gui->pots[18].percent++; }
        else
        { gui->pots[18].percent--; }

        uint8_param = gui->pots[19].param;
        if ((double) gui->pots[19].percent < map(*uint8_param, gui->pots[19].paramMIN, gui->pots[19].paramMAX, 0, 100))
        { gui->pots[19].percent++; }
        else
        { gui->pots[19].percent--; }

        uint8_param = gui->pots[20].param;
        if ((double) gui->pots[20].percent < map(*uint8_param, gui->pots[20].paramMIN, gui->pots[20].paramMAX, 0, 100))
        { gui->pots[20].percent++; }
        else
        { gui->pots[20].percent--; }

        // Flanger
        double_param = gui->pots[21].param;
        if ((double) gui->pots[21].percent < map(*double_param, gui->pots[21].paramMIN, gui->pots[21].paramMAX, 0, 100))
        { gui->pots[21].percent++; }
        else
        { gui->pots[21].percent--; }

        double_param = gui->pots[22].param;
        if ((double) gui->pots[22].percent < map(*double_param, gui->pots[22].paramMIN, gui->pots[22].paramMAX, 0, 100))
        { gui->pots[22].percent++; }
        else
        { gui->pots[22].percent--; }

        uint8_param = gui->pots[23].param;
        if ((double) gui->pots[23].percent < map(*uint8_param, gui->pots[23].paramMIN, gui->pots[23].paramMAX, 0, 100))
        { gui->pots[23].percent++; }
        else
        { gui->pots[23].percent--; }

        uint8_param = gui->pots[24].param;
        if ((double) gui->pots[24].percent < map(*uint8_param, gui->pots[24].paramMIN, gui->pots[24].paramMAX, 0, 100))
        { gui->pots[24].percent++; }
        else
        { gui->pots[24].percent--; }

        // LFO filter
        uint16_param = gui->pots[25].param;
        if ((double) gui->pots[25].percent < map(*uint16_param, gui->pots[25].paramMIN, gui->pots[25].paramMAX, 0, 100))
        { gui->pots[25].percent++; }
        else
        { gui->pots[25].percent--; }

        uint16_param = gui->pots[26].param;
        if ((double) gui->pots[26].percent < map(*uint16_param, gui->pots[26].paramMIN, gui->pots[26].paramMAX, 0, 100))
        { gui->pots[26].percent++; }
        else
        { gui->pots[26].percent--; }

        double_param = gui->pots[27].param;
        if ((double) gui->pots[27].percent < map(*double_param, gui->pots[27].paramMIN, gui->pots[27].paramMAX, 0, 100))
        { gui->pots[27].percent++; }
        else
        { gui->pots[27].percent--; }

        uint8_param = gui->pots[28].param;
        if ((double) gui->pots[28].percent < map(*uint8_param, gui->pots[28].paramMIN, gui->pots[28].paramMAX, 0, 100))
        { gui->pots[28].percent++; }
        else
        { gui->pots[28].percent--; }

        double_param = gui->pots[29].param;
        if ((double) gui->pots[29].percent < map(*double_param, gui->pots[29].paramMIN, gui->pots[29].paramMAX, 0, 100))
        { gui->pots[29].percent++; }
        else
        { gui->pots[29].percent--; }

        uint16_param = gui->pots[30].param;
        if ((double) gui->pots[30].percent < map(*uint16_param, gui->pots[30].paramMIN, gui->pots[30].paramMAX, 0, 100))
        { gui->pots[30].percent++; }
        else
        { gui->pots[30].percent--; }

        double_param = gui->pots[31].param;
        if ((double) gui->pots[31].percent < map(*double_param, gui->pots[31].paramMIN, gui->pots[31].paramMAX, 0, 100))
        { gui->pots[31].percent++; }
        else
        { gui->pots[31].percent--; }

        if (gui_update(gui))return -1;
        SDL_Delay(2);

        if (gui_update(gui))return -1;

    }

}
Sint8 levelVUMeter(Audio_Buffer average_audio_level)
{
    double LnScaledAudioLevel;
    short int LEDResult = 0;

    //The level is between 0 and 2¹⁶, so between 0 and 1 the Ln value will be set to 1.
    if (average_audio_level[0] == 0) return 0;
    if (average_audio_level[0] <= 1 && average_audio_level[0] != 0)
    {
        return 1;
    }
    else
    {
        LnScaledAudioLevel = log((double) average_audio_level[0]);
    }

    /*It should return a number between 1 and 11.09, but we only have 8 LEDs on our synth. I am therefore
     making the choice to set the thresholds accordingly.
     */
    if (LnScaledAudioLevel < 6) LEDResult = round((double) LnScaledAudioLevel);
    if (LnScaledAudioLevel >= 6 && LnScaledAudioLevel < 8) LEDResult = 6;
    if (LnScaledAudioLevel >= 8 && LnScaledAudioLevel < 9) LEDResult = 7;
    if (LnScaledAudioLevel >= 9) LEDResult = 8;

    return LEDResult;
}

Uint8 prompt_quit()
{
    return tinyfd_messageBox(NULL, "Exit application ?", "yesno", "question", 0);
}



