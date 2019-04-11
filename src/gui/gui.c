/**
 * \file gui.c
 * \brief Graphical user interface data structure and function implementation.
 *
 *
 * Here are implemented the data structure of the gui, and the related functions
 */

#include "gui.h"

// Global parameters defined in main.c and audio_core.c
extern Sys_param *sys_param;
extern Polyphony *note_array;



// functions ...

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int testGUI()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    int statut = EXIT_FAILURE;
    SDL_Rect rect = {100, 100, 100, 100}, dst = {0, 0, 0, 0};
    SDL_Color rouge = {255, 0, 0, 255}, bleu = {0, 0, 255, 255};

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    if (0 != SDL_CreateWindowAndRenderer(1280, 800, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, 1280, 800);
    if (NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        goto Quit;
    }

    SDL_Surface *tmp = NULL;
    //SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP("../src/gui/Figs/bg_fix_3.BMP"); //Loading the image onto the tmp surface
    if (NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        goto Quit;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    /* SDL_SetRenderTarget(renderer, texture);
    La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    /*SDL_SetRenderDrawColor(renderer, bleu.r, bleu.g, bleu.b, bleu.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);
    SDL_RenderFillRect(renderer, &rect); /* On dessine un rectangle rouge sur la texture. */

    SDL_SetRenderTarget(renderer, NULL); /* Le renderer est la cible de rendu. */

    /* On récupère les dimensions de la texture, on la copie sur le renderer
       et on met à jour l’écran. */
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_SetWindowTitle(window, "meilleur Synthé du monde");
    SDL_RenderPresent(renderer);
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    while(!quit)
    {
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT)
            quit = SDL_TRUE;
        else if(event.type == SDL_KEYDOWN)
        {
                printf("keysym A\n");
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN){

            printf ("%d %d", event.button.x, event.button.y);
        }
        SDL_Delay(20);
    }

    goto Quit;

        Quit:
            if (NULL != texture)
                SDL_DestroyTexture(texture);
            if (NULL != renderer)
                SDL_DestroyRenderer(renderer);
            if (NULL != window)
                SDL_DestroyWindow(window);
            SDL_Quit();
            return statut;
}

