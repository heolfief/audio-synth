/**
 * \file wav.c
 * \brief WAV (recording related) functions implementation.
 *
 *
 * Here are implemented the functions of recording of WAV files
 */

#include "wav.h"
#include <sndfile.h>

int open_wav_file(const char *filePath, Core *ac)
{
    if(filePath==NULL)return -1;
    if(ac==NULL)return -1;
    // Set file settings, 16bit Mono PCM
    SF_INFO info;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.channels = 1;
    info.samplerate = ac->sys_param->sample_rate;

    // Open sound file for writing
    ac->record_param->sndFile = sf_open(filePath, SFM_WRITE, &info);
    if (ac->record_param->sndFile == NULL)
    {
        fprintf(stderr, "Error opening sound file '%s': %s\n", filePath, sf_strerror(ac->record_param->sndFile));
        return -1;
    }

    return 0;
}

int write_wav_file(int bufferLength, Audio_Buffer buffer, SNDFILE *sndFile)
{
    if(buffer==NULL)return -1;
    if(sndFile ==NULL)return -1;
    long writtenFrames = sf_writef_short(sndFile, buffer, bufferLength);
    // Check correct number of frames saved
    if (writtenFrames != bufferLength)
    {
        fprintf(stderr, "Did not write enough frames for source, wrote : %ld \n", writtenFrames);
        sf_close(sndFile);
        return -1;
    }

    return 0;

}
int close_wav_file(SNDFILE *sndFile)
{
    if(sndFile == NULL)return -1;
    sf_write_sync(sndFile);
    sf_close(sndFile);
    return 0;
}

