/**
 * \file main.c
 * \brief Main programm
 *
 */


#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "oscillator/osc.h"

#define SAMPLE_RATE 48000
#define AUDIO_BUFF_SIZE 1024
#define OSC_NBR 3

// Global oscillators
Oscillator osc1;
Oscillator osc2;
Oscillator osc3;


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


    osc_fill_buffer(&osc1, osc1.buffer, s_len, SAMPLE_RATE, phase);
    osc_fill_buffer(&osc2, osc2.buffer, s_len, SAMPLE_RATE, phase);
    osc_fill_buffer(&osc3, osc3.buffer, s_len, SAMPLE_RATE, phase);

    for(Uint16 i = 0; i < s_len; ++i)
    {
        // Add all oscillators
        s_stream[i] = (Sint16)(osc1.buffer[i]/OSC_NBR + osc2.buffer[i]/OSC_NBR + osc3.buffer[i]/OSC_NBR);
    }

    phase = (phase + len/2)%SAMPLE_RATE;    // Update phase based on play position
}

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        printf("Error initializing SDL\n");
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
        printf("Unable to open audio..");
        exit(EXIT_FAILURE);
    }



    osc1.amp = 32000;
    osc1.wave = TRI;
    osc1.detune = 0;
    osc1.freq = 440;
    osc1.duty = 50;
    osc1.onoff = ON;
    osc1.buffer = alloc_osc_buffer(AUDIO_BUFF_SIZE);

    osc2.amp = 32000;
    osc2.wave = SIN;
    osc2.detune = -24;
    osc2.freq = 440;
    osc2.duty = 50;
    osc2.onoff = ON;
    osc2.buffer = alloc_osc_buffer(AUDIO_BUFF_SIZE);

    osc3.amp = 5000;
    osc3.wave = SQR;
    osc3.detune = -12;
    osc3.freq = 440;
    osc3.duty = 50;
    osc3.onoff = ON;
    osc3.buffer = alloc_osc_buffer(AUDIO_BUFF_SIZE);

    SDL_PauseAudio(0);                      // Play audio (pause = off)
    SDL_Delay(5000);                        // 5s sound

    SDL_Quit();

    free_osc_buffer(osc1.buffer);
    free_osc_buffer(osc2.buffer);
    free_osc_buffer(osc3.buffer);

    return 0;
}