#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "oscillator/osc.h"

#define SAMPLE_RATE 48000
#define AUDIO_BUFF_SIZE 1024
#define VOLUME 32767


Uint64 cursor=0;            // Variable qui retient l'emplacement de lecture entre chaque buffer

void func_callback(void *unused, Uint8 *stream, int len)
{

    int note = 440; // 440Hz

    memset(stream, 0, len);         // on vide le buffer
    Sint16 *s_stream = (Sint16*) stream;    // On cast les données du buffer en 16 bits signés

    for (int i=0;i<len/2;i++)              // données 16bits=2*8bits, donc (len/2) données 16 bits dans le buffer
    {
        s_stream[i] = (Sint16)(VOLUME*(sin((i+cursor)*note*2*M_PI/SAMPLE_RATE)));
    }
    cursor = (cursor + len/2)%SAMPLE_RATE;  // mise à jour de l'emplacement de lecture
}

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        printf("Error initializing SDL\n");
        return 1;
    }

    SDL_AudioSpec as;

    as.freq = SAMPLE_RATE;
    as.format = AUDIO_S16LSB;               // Echantillons audio sur 16bits signés
    as.samples = AUDIO_BUFF_SIZE;
    as.callback = func_callback;            // fonction qui remplit le buffer audio, appelée dès qu'il est vide
    as.userdata = NULL;
    as.channels = 1;                        // mono


    if (SDL_OpenAudio(&as, NULL)<0)
    {
        printf("Unable to open audio..");
        return 1;
    }
    SDL_PauseAudio(0);                      // Play audio (pause = off)
    SDL_Delay(5000);                        // Son de 5s

    SDL_Quit();
    return 0;
}