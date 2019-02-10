#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "oscillator/osc.h"

#define SAMPLE_RATE 48000
#define AUDIO_BUFF_SIZE 1024
#define OSC_NBR 3

Uint64 phase=0;

Oscillator osc1;
Oscillator osc2;
Oscillator osc3;

void func_callback(void *unused, Uint8 *stream, int len)
{
    memset(stream, 0, len);                 // Empty buffer
    Sint16 *s_stream = (Sint16*) stream;    // Cast buffer data to signed 16 bits
    Uint16 s_len = (Uint16)len/2;           // data are 16bits=2*8bits, so (len/2) 16 bits data in the buffer

    Sint16 *osc1_buff = NULL;
    Sint16 *osc2_buff = NULL;
    Sint16 *osc3_buff = NULL;

    osc1_buff = calloc(s_len, sizeof(osc1_buff));
    osc2_buff = calloc(s_len, sizeof(osc2_buff));
    osc3_buff = calloc(s_len, sizeof(osc3_buff));

    osc_fill_buffer(&osc1, osc1_buff, s_len, SAMPLE_RATE, phase);
    osc_fill_buffer(&osc2, osc2_buff, s_len, SAMPLE_RATE, phase);
    osc_fill_buffer(&osc3, osc3_buff, s_len, SAMPLE_RATE, phase);

    for(Uint16 i = 0; i < s_len; ++i)
    {
        s_stream[i] = (Sint16)(osc1_buff[i]/OSC_NBR + osc2_buff[i]/OSC_NBR + osc3_buff[i]/OSC_NBR);
    }

    phase = (phase + len/2)%SAMPLE_RATE;    // Update phase based on play position
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
    as.format = AUDIO_S16LSB;               // Audio samples are signed 16 bits
    as.samples = AUDIO_BUFF_SIZE;
    as.callback = func_callback;            // Function that fills the audio buffer, called once it is empty
    as.userdata = NULL;
    as.channels = 1;                        // Mono audio


    if (SDL_OpenAudio(&as, NULL)<0)
    {
        printf("Unable to open audio..");
        return 1;
    }

    osc1.amp = 20000;
    osc1.wave = SIN;
    osc1.detune = 0;
    osc1.freq = 440;
    osc1.duty = 50;

    osc2.amp = 5000;
    osc2.wave = SQR;
    osc2.detune = 0;
    osc2.freq = 440;
    osc2.duty = 50;

    osc3.amp = 32767;
    osc3.wave = SIN;
    osc3.detune = -12;
    osc3.freq = 440;
    osc3.duty = 50;

    SDL_PauseAudio(0);                      // Play audio (pause = off)
    SDL_Delay(5000);                        // 5s sound

    SDL_Quit();
    return 0;
}