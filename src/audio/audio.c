/**
 * \file note.c
 * \brief Note data structure and function implementation.
 *
 *
 * Here are implemented the data structure of a note, and the related functions
 */

#include "audio.h"

// Global parameters defined in main.c
extern Audio_Buffer master_audio;
extern Sys_param* sys_param;


void func_callback(void *userdata, Uint8 *stream, int len)
{
    static Uint64 phase;

    memset(stream, 0, (size_t)len);         // Empty buffer
    Sint16 *s_stream = (Sint16*) stream;    // Cast buffer data to signed 16 bits
    Uint16 s_len = (Uint16)len/(Uint16)2;   // data are 16bits=2*8bits, so (len/2) 16 bits data in the buffer

    synthesis_fill_buffer(phase);

    for(Uint16 sample = 0; sample < s_len; ++sample)
    {
        s_stream[sample] = master_audio[sample];
    }

    phase = (phase + s_len)%sys_param->sample_rate;    // Update phase based on play position
}


int set_audio_spec(SDL_AudioSpec *as)
{
    if(as == NULL)
    {
        sys_print_error("AudioSpec parameter is NULL");
        return -1;
    }
    as->freq = sys_param->sample_rate;
    as->format = AUDIO_S16LSB;               // Audio samples are signed 16 bits
    as->samples = sys_param->audio_buffer_length;
    as->callback = func_callback;            // Function that fills the audio buffer, called once it is empty
    as->userdata = NULL;
    as->channels = 1;                        // Mono audio

    return 0;
}