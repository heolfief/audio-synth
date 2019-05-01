/**
 * \file gui.c
 * \brief Graphical user interface data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the gui, and the related functions
 */

#include "gui.h"

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

    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP("../src/gui/Figs/bg_fix_3.BMP"); //Loading the image onto the tmp surface
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

    gui->rect.w = APPLICATION_WINDOW_WIDTH;
    gui->rect.h = APPLICATION_WINDOW_HEIGHT;

//    // We get the texture dimensions, copy it on the rendered and update the screen
//    if (SDL_QueryTexture(gui->texture, NULL, NULL, &gui->rect.w, &gui->rect.h))
//    {
//        sys_print_SDL_error("Query texture failed");
//        return -1;
//    }
    if (SDL_RenderCopy(gui->renderer, gui->texture, NULL, &gui->rect))
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

    return gui;
}

int free_gui_sdl_objects(Gui_SDL_objects *gui)
{
    free(gui);
    return 0;
}

int gui_set_button_image(SDL_Button_t *button, SDL_Renderer *renderer, char *path_to_image)
{
    button->internal_surface = SDL_LoadBMP(path_to_image);
    if (button->internal_surface == NULL)
    {
        sys_print_SDL_error("Failed loading image");
        return -1;
    }

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(renderer, button->internal_surface);
    if (pTexture == NULL)
    {
        sys_print_SDL_error("Failed creating texture");
        return -1;
    }
    if (SDL_RenderCopy(renderer, pTexture, NULL, button->location_and_size))return -1;

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(pTexture);

    return 0;
}

SDL_Button_t *gui_create_and_show_button(SDL_Renderer *renderer, int x_location, int y_location, int button_width, int button_height, char *path_to_image)
{
    SDL_Button_t *button = NULL;

    SDL_Surface *tmp = SDL_LoadBMP(path_to_image);
    if (tmp == NULL)
    {
        sys_print_SDL_error("Failed loading image");
        return NULL;
    }

    button = SDL_Button(tmp, x_location, y_location, button_width, button_height);

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(renderer, button->internal_surface);
    if (pTexture == NULL)
    {
        sys_print_SDL_error("Failed creating texture");
        return NULL;
    }
    SDL_RenderCopy(renderer, pTexture, NULL, button->location_and_size);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(pTexture);

    SDL_FreeSurface(tmp); // Libération de la ressource occupée par le sprite

    return button;
}

Button *alloc_button()
{
    Button *bt = (Button*)malloc(sizeof(Button));
    return bt;
}

int free_button(Button *bt)
{

    return 0;
}