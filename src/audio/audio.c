/**
 * \file audio.c
 * \brief Audio (SDL related) functions implementation.
 *
 *
 * Here are implemented the SDL related audio functions
 */

#include "audio.h"

void func_callback(void *userdata, Uint8 *stream, int len)
{
    Core *audio_core = (Core *) userdata;
    Sint16 *s_stream = (Sint16 *) stream;    // Cast buffer data to signed 16 bits
    Uint16 s_len = (Uint16) len / (Uint16) 2;   // data are 16bits=2*8bits, so (len/2) 16 bits data in the buffer

    memset(stream, 0, (size_t) len);         // Empty buffer

    if (master_audio_fill_buffer(audio_core) != 0) exit(EXIT_FAILURE);

    for (Uint16 sample = 0; sample < s_len; ++sample) s_stream[sample] = audio_core->master_audio[sample];

    audio_core->phase = (audio_core->phase + s_len);    // Update phase based on play position
}

int set_audio_spec(SDL_AudioSpec *as, const Core *ac)
{
    if (as == NULL)
    {
        sys_print_error("AudioSpec parameter is NULL");
        return -1;
    }
    as->freq = ac->sys_param->sample_rate;
    as->format = AUDIO_S16LSB;               // Audio samples are signed 16 bits
    as->samples = ac->sys_param->audio_buffer_length;
    as->callback = func_callback;            // Function that fills the audio buffer, called once it is empty
    as->userdata = (void *) ac;                // Pass core pointer to the func_callback interrupt function
    as->channels = 1;                        // Mono audio

    return 0;
}