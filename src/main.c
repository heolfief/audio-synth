/**
 * \file main.c
 * \brief Main programm
 *
 */


#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "sys_param/sys_param.h"
#include "oscillator/osc.h"
#include "note/note.h"
#include "note/polyphony.h"
#include "gui/gui.h"

#define SAMPLE_RATE 48000
#define AUDIO_BUFF_SIZE 1024

// Global notes variable
Polyphony *note_array;
Audio_Buffer master_audio;

// Global system parameters changed by the GUI
Sys_param* sys_param = NULL;




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

    polyphony_fill_buffer(master_audio, note_array, s_len, sys_param->env, SAMPLE_RATE, phase);

    for(Uint16 sample = 0; sample < s_len; ++sample)
    {
        s_stream[sample] = master_audio[sample];
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


    // Memory allocation
    note_array = alloc_polyphony(AUDIO_BUFF_SIZE);
    if(note_array == NULL) exit(EXIT_FAILURE);

    master_audio = alloc_audio_buffer(AUDIO_BUFF_SIZE);
    if(master_audio == NULL) exit(EXIT_FAILURE);

    sys_param = alloc_sys_param(AUDIO_BUFF_SIZE);
    if(sys_param == NULL) exit(EXIT_FAILURE);



    // Hard coded system parameters, will be changed by the GUI in the future
    sys_param->env->attack   = 200;
    sys_param->env->decay    = 1000;
    sys_param->env->sustain  = 0.5;
    sys_param->env->release  = 10000;

    sys_param->osc1->amp     = 32000;
    sys_param->osc1->wave    = SQR;
    sys_param->osc1->detune  = 0;
    sys_param->osc1->duty    = 50;
    sys_param->osc1->onoff   = ON;

    sys_param->osc2->amp     = 5000;
    sys_param->osc2->wave    = SIN;
    sys_param->osc2->detune  = 0;
    sys_param->osc2->duty    = 50;
    sys_param->osc2->onoff   = ON;

    sys_param->osc3->amp     = 32000;
    sys_param->osc3->wave    = TRI;
    sys_param->osc3->detune  = -12;
    sys_param->osc3->duty    = 50;
    sys_param->osc3->onoff   = ON;

    // Each time oscillator parameters changed, this function needs to be called
    copy_osc_sys_param_to_notes_osc(sys_param, note_array);


    // Hard coded note data, will be changed by reading MIDI files in the future
    note_array[0]->freq = 440;
    note_array[0]->onoff = OFF;
    note_array[0]->velocity_amp = 1;
    note_array[0]->master_onoff = OFF;


    SDL_PauseAudio(0);                      // Play audio (pause = off)


    for(int i = 0; i < 7; ++i)
    {
        note_array[0]->freq = mario_freq[i];
        note_on(note_array[0]);
        SDL_Delay(100);
        note_off(note_array[0]);
        SDL_Delay(mario_delay[i]);
    }

    SDL_Delay(2000);

    SDL_CloseAudio();
    SDL_Quit();

    // Free all the data
    free_polyphony(note_array);
    free_audio_buffer(master_audio);
    free_sys_param(sys_param);

    return 0;
}