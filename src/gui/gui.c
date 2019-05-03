/**
 * \file gui.c
 * \brief Graphical user interface data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the gui, and the related functions
 */

#include "gui.h"

static const int switches_location[NUMBER_OF_SWITCHES][2] = {
    {105, 52},        // Switch osc1 OnOff
    {337, 52},        // Switch osc2 OnOff
    {595, 52},        // Switch osc3 OnOff
    {86, 360},        // Switch effect OnOff
    {291, 360},       // Switch effect OnOff
    {497, 360},       // Switch effect OnOff
    {698, 360},       // Switch effect OnOff
    {904, 360},       // Switch effect OnOff
    {1106, 360}       // Switch effect OnOff
};

static double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int init_gui(Gui_SDL_objects *gui)
{
    if (SDL_CreateWindowAndRenderer(APPLICATION_WINDOW_WIDTH, APPLICATION_WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &gui->window, &gui->renderer)
        != 0)
    {
        sys_print_SDL_error("ERROR in creating window and renderer");
        return -1;
    }

    gui->texture =
        SDL_CreateTexture(gui->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, APPLICATION_WINDOW_WIDTH, APPLICATION_WINDOW_HEIGHT);
    if (NULL == gui->texture)
    {
        sys_print_SDL_error("ERROR creating texture");
        return -1;
    }

    SDL_Surface *tmp = IMG_Load(APPLICATION_IMAGE_BACKGROUND); //Loading the image onto the tmp surface
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

    SDL_FreeSurface(tmp); // Free the surface, not needed anymore

    SDL_SetRenderTarget(gui->renderer, NULL);

    gui->background.w = APPLICATION_WINDOW_WIDTH;
    gui->background.h = APPLICATION_WINDOW_HEIGHT;

    if (SDL_RenderCopy(gui->renderer, gui->texture, NULL, &gui->background))
    {
        sys_print_SDL_error("Render Copy failed");
        return -1;
    }
    SDL_SetWindowTitle(gui->window, APPLICATION_NAME);
    SDL_RenderPresent(gui->renderer);

    return 0;
}

void exit_gui(Gui_SDL_objects *gui)
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

Gui_SDL_objects *alloc_gui_sdl_objects()
{
    Gui_SDL_objects *gui = (Gui_SDL_objects *) malloc(sizeof(Gui_SDL_objects));
    if (gui == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    Mouse_position *mp = (Mouse_position *) malloc(sizeof(Mouse_position));
    if (mp == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->mouse_position = mp;

    Switch *bt = (Switch *) calloc(NUMBER_OF_SWITCHES, sizeof(Switch));
    if (bt == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->switches = bt;

    Potentiometer *pot = (Potentiometer *) calloc(NUMBER_OF_POTS, sizeof(Potentiometer));
    if (pot == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }
    gui->pots = pot;

    return gui;
}

int free_gui_sdl_objects(Gui_SDL_objects *gui)
{
    free(gui->mouse_position);
    free(gui->switches);
    free(gui->pots);
    free(gui);
    return 0;
}

int gui_update(Gui_SDL_objects *gui)
{
    // Render background
    if (SDL_RenderCopy(gui->renderer, gui->texture, NULL, &gui->background))
    {
        sys_print_SDL_error("Render Copy failed");
        return -1;
    }

    // For each button
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

    // For each pot
    for (int i = 0; i < NUMBER_OF_POTS; ++i)
    {
        SDL_Texture
            *tmp = SDL_CreateTextureFromSurface(gui->renderer, gui->pots[i].sdl_pot->internal_surface);
        if (tmp == NULL)
        {
            sys_print_SDL_error("Failed creating texture");
            return -1;
        }
        if (SDL_RenderCopyEx(gui->renderer, tmp, NULL, gui->pots[i].sdl_pot->location_and_size,
                             map(gui->pots[i].percent, 0, 100, 0, 290), NULL, SDL_FLIP_NONE))
        {
            sys_print_SDL_error("Failed RenderCopy");
            return -1;
        }
        SDL_DestroyTexture(tmp);
    }

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

int create_switches_map(Gui_SDL_objects *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    for (int bt = 0; bt < NUMBER_OF_SWITCHES; ++bt)
    {
        gui->switches[bt].onoff = OFF;
        gui->switches[bt].imgoff = APPLICATION_IMAGE_SWITCH_OFF;
        gui->switches[bt].imgon = APPLICATION_IMAGE_SWITCH_ON;
        gui->switches[bt].posX = switches_location[bt][0];
        gui->switches[bt].posY = switches_location[bt][1];
        gui->switches[bt].width = APPLICATION_IMAGE_SWITCH_WIDTH;
        gui->switches[bt].height = APPLICATION_IMAGE_SWITCH_HEIGHT;
        gui->switches[bt].sdl_button =
            gui_create_button(gui->switches[bt].posX, gui->switches[bt].posY, gui->switches[bt].width, gui->switches[bt].height, gui->switches[bt].imgoff);
    }

    gui->switches[0].param = &sys_param->osc1->onoff;
    gui->switches[1].param = &sys_param->osc2->onoff;
    gui->switches[2].param = &sys_param->osc3->onoff;
    gui->switches[3].param = &sys_param->dist_param->onoff;
    gui->switches[4].param = &sys_param->delay_param->onoff;
    gui->switches[5].param = &sys_param->amp_mod_param->onoff;
    gui->switches[6].param = &sys_param->flanger_param->onoff;
    gui->switches[7].param = &sys_param->lfo_filter_param->onoff;
    gui->switches[8].param = &sys_param->filter_param->onoff;

    return 0;
}

int create_pots_map(Gui_SDL_objects *gui, Sys_param *sys_param)
{
    if (gui == NULL || sys_param == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }
    for (int bt = 0; bt < NUMBER_OF_POTS; ++bt)
    {
        gui->pots[bt].percent = 0;
        gui->pots[bt].img = APPLICATION_IMAGE_POT;
        gui->pots[bt].posX = 898;
        gui->pots[bt].posY = 428;
        gui->pots[bt].width = APPLICATION_IMAGE_POT_WIDTH;
        gui->pots[bt].height = APPLICATION_IMAGE_POT_HEIGHT;
        gui->pots[bt].sdl_pot =
            gui_create_button(gui->pots[bt].posX, gui->pots[bt].posY, gui->pots[bt].width, gui->pots[bt].height, gui->pots[bt].img);
    }

    gui->pots[0].param = &sys_param->lfo_filter_param->lfo_freq;
    gui->pots[0].paramMIN = 0;
    gui->pots[0].paramMAX = 20;

    return 0;
}

int process_switches(Gui_SDL_objects *gui, Core *audio_core)
{
    OnOff *param = NULL;

    if (gui == NULL || audio_core == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    for (int bt = 0; bt < NUMBER_OF_SWITCHES; ++bt)
    {
        if (SDL_Button_mouse_down(gui->switches[bt].sdl_button, &gui->event))
        {
            if (gui->switches[bt].onoff)    // If ON
            {
                if (gui_set_switch_image(gui->switches[bt].sdl_button, gui->switches[bt].imgoff))return -1;
                gui->switches[bt].onoff = OFF;

                param = gui->switches[bt].param;
                *param = OFF;
            }
            else
            {
                if (gui_set_switch_image(gui->switches[bt].sdl_button, gui->switches[bt].imgon))return -1;
                gui->switches[bt].onoff = ON;

                param = gui->switches[bt].param;
                *param = ON;
            }
        }
    }

    // Each time oscillator parameters changed, this function needs to be called
    if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

    // Each time a filter parameter is changed, this function needs to be called
    if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

    if (gui_update(gui))return -1;

    return 0;
}

int process_pots(Gui_SDL_objects *gui, Core *audio_core)
{
    double *double_param = NULL;

    if (gui == NULL || audio_core == NULL)
    {
        sys_print_error("Parameter is NULL");
        return -1;
    }

    if (gui->event.type == SDL_MOUSEWHEEL)
    {
        if (SDL_Button_mouse_over(gui->pots[0].sdl_pot, &gui->event))
        {
            if (((double) gui->pots[0].percent - (double) gui->event.wheel.y * (double) POT_INCREMENT) > 100)
            {
                gui->pots[0].percent = 100;
            }
            else if (((double) gui->pots[0].percent - (double) gui->event.wheel.y * (double) POT_INCREMENT) < 0)
            {
                gui->pots[0].percent = 0;
            }
            else
            {
                gui->pots[0].percent -= gui->event.wheel.y * POT_INCREMENT;
            }

            double_param = gui->pots[0].param;
            *double_param = (double) map(gui->pots[0].percent, 0, 100, gui->pots[0].paramMIN, gui->pots[0].paramMAX);
        }
    }

    // Each time oscillator parameters changed, this function needs to be called
    if (copy_osc_sys_param_to_notes_osc(audio_core->sys_param, audio_core->note_array))return -1;

    // Each time a filter parameter is changed, this function needs to be called
    if (compute_filter_coeffs(audio_core->sys_param->filter_param, audio_core->sys_param->sample_rate, audio_core->effect_core->filter_state))return -1;

    if (gui_update(gui))return -1;

    return 0;
}