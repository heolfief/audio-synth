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
#define OSC_NBR 3


// Global test note
Note test_note;

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


    osc_fill_buffer(&test_note.osc1, test_note.osc1.buffer, s_len, SAMPLE_RATE, phase);
    osc_fill_buffer(&test_note.osc2, test_note.osc2.buffer, s_len, SAMPLE_RATE, phase);
    osc_fill_buffer(&test_note.osc3, test_note.osc3.buffer, s_len, SAMPLE_RATE, phase);

    for(Uint16 sample = 0; sample < s_len; ++sample)
    {
        // Add all oscillators into the note buffer [ONLY A TEST, A FUTURE FUNCTION WILL DO THIS]
        test_note.buffer[sample] = (Sint16)(test_note.osc1.buffer[sample]/OSC_NBR + test_note.osc2.buffer[sample]/OSC_NBR + test_note.osc3.buffer[sample]/OSC_NBR);
    }

    for(Uint16 sample = 0; sample < s_len; ++sample)
    {
        s_stream[sample] = test_note.buffer[sample];
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



    test_note.buffer = alloc_note_buffer(AUDIO_BUFF_SIZE);

    test_note.osc1.amp = 32000;
    test_note.osc1.wave = TRI;
    test_note.osc1.detune = 0;
    test_note.osc1.freq = 440;
    test_note.osc1.duty = 50;
    test_note.osc1.onoff = ON;
    test_note.osc1.buffer = alloc_osc_buffer(AUDIO_BUFF_SIZE);

    test_note.osc2.amp = 32000;
    test_note.osc2.wave = SIN;
    test_note.osc2.detune = -24;
    test_note.osc2.freq = 440;
    test_note.osc2.duty = 50;
    test_note.osc2.onoff = ON;
    test_note.osc2.buffer = alloc_osc_buffer(AUDIO_BUFF_SIZE);

    test_note.osc3.amp = 5000;
    test_note.osc3.wave = SQR;
    test_note.osc3.detune = -12;
    test_note.osc3.freq = 440;
    test_note.osc3.duty = 50;
    test_note.osc3.onoff = ON;
    test_note.osc3.buffer = alloc_osc_buffer(AUDIO_BUFF_SIZE);



    SDL_PauseAudio(0);                      // Play audio (pause = off)
    SDL_Delay(5000);                        // 5s sound

    SDL_Quit();

    free_osc_buffer(test_note.osc1.buffer);
    free_osc_buffer(test_note.osc2.buffer);
    free_osc_buffer(test_note.osc3.buffer);

    free_note_buffer(test_note.buffer);

    return 0;
}