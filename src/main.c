/**
 * \file main.c
 * \brief Main programm
 *
 */


#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "oscillator/osc.h"
#include "note/note.h"
#include "gui/gui.h"

#define SAMPLE_RATE 48000
#define AUDIO_BUFF_SIZE 1024

// Global note variable
Note *test_note;

Envelope test_env = {.attack = 200, .decay =1000, .sustain =0.5, .release =10000};

Uint16 mario_freq[7]={660, 660, 660, 510, 660, 770, 380};
Uint16 mario_delay[7]={80, 200, 250, 80, 250, 450, 450};

/**
 *  \fn void func_callback(void *unused, Uint8 *stream, int len)
 *  \brief This function is called when the audio device needs more data.
 *
 *  \param userdata An application-specific parameter saved in
 *                  the SDL_AudioSpec structure
 *  \param stream A pointer to the audio data buffer.
 *  \param len    The length of that buffer in bytes.
 *
 *  Once the callback returns, the buffer will no longer be valid.
 *  Stereo samples are stored in a LRLRLR ordering.
 *
 *  You can choose to avoid callbacks and use SDL_QueueAudio() instead, if
 *  you like. Just open your audio device with a NULL callback.
 */
void func_callback(void *unused, Uint8 *stream, int len)
{
    static Uint64 phase;

    memset(stream, 0, (size_t)len);         // Empty buffer
    Sint16 *s_stream = (Sint16*) stream;    // Cast buffer data to signed 16 bits
    Uint16 s_len = (Uint16)len/(Uint16)2;   // data are 16bits=2*8bits, so (len/2) 16 bits data in the buffer

    note_fill_buffer(test_note, test_note->buffer, s_len, &test_env, SAMPLE_RATE, phase);

    for(Uint16 sample = 0; sample < s_len; ++sample)
    {
        s_stream[sample] = test_note->buffer[sample];
    }


    phase = (phase + len/2)%SAMPLE_RATE;    // Update phase based on play position
}

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        fprintf(stderr, "Error initializing SDL\n");
        exit(EXIT_FAILURE);
    }

    SDL_AudioSpec as;

    as.freq = SAMPLE_RATE;
    as.format = AUDIO_S16LSB;               // Audio samples are signed 16 bits
    as.samples = AUDIO_BUFF_SIZE;
    as.callback = func_callback;            // Function that fills the audio buffer, called once it is empty
    as.userdata = NULL;
    as.channels = 1;                        // Mono audio


    if (SDL_OpenAudio(&as, NULL)<0)
    {
        fprintf(stderr, "Unable to open audio..");
        exit(EXIT_FAILURE);
    }

    test_note = alloc_note(AUDIO_BUFF_SIZE);

    test_note->osc1->amp = 32000;
    test_note->osc1->wave = SQR;
    test_note->osc1->detune = 0;
    test_note->osc1->duty = 50;
    test_note->osc1->onoff = ON;

    test_note->osc2->amp = 5000;
    test_note->osc2->wave = SIN;
    test_note->osc2->detune = 0;
    test_note->osc2->duty = 50;
    test_note->osc2->onoff = ON;

    test_note->osc3->amp = 32000;
    test_note->osc3->wave = TRI;
    test_note->osc3->detune = -12;
    test_note->osc3->duty = 50;
    test_note->osc3->onoff = ON;


    test_note->freq = 440;
    test_note->onoff = OFF;
    test_note->velocity_amp = 1;
    test_note->master_onoff = OFF;

    SDL_PauseAudio(0);                      // Play audio (pause = off)


    for(int i = 0; i < 7; ++i)
    {
        test_note->freq = mario_freq[i];
        note_on(test_note);
        SDL_Delay(100);
        note_off(test_note);
        SDL_Delay(mario_delay[i]);
    }

    SDL_Delay(2000);

    SDL_CloseAudio();
    SDL_Quit();

    free_note(test_note);

    return 0;
}