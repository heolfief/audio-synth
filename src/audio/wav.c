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
    // Set file settings, 16bit Mono PCM
    SF_INFO info;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.channels = 1;
    info.samplerate = ac->sys_param->sample_rate;
    printf("file %s info created \n", filePath);

    // Open sound file for writing
    ac->record_param->sndFile = sf_open(filePath, SFM_WRITE, &info);
    if (ac->record_param->sndFile == NULL)
    {
        fprintf(stderr, "Error opening sound file '%s': %s\n", filePath, sf_strerror(ac->record_param->sndFile));
        return -1;
    }
    printf("file %s opened for writing \n", filePath);

    return 0;
}

int write_wav_file(int bufferLength, Audio_Buffer buffer, SNDFILE *sndFile)
{

    printf("trying to write frames into file   \n");

    long writtenFrames = sf_writef_short(sndFile, buffer, bufferLength);
    // Check correct number of frames saved
    printf("written frames : %d\n", writtenFrames);
    if (writtenFrames != bufferLength)
    {
        fprintf(stderr, "Did not write enough frames for source, wrote : %d \n", writtenFrames);
        sf_close(sndFile);
        return -1;
    }

    return 0;

}
int close_wav_file(SNDFILE *sndFile)
{
    sf_write_sync(sndFile);
    sf_close(sndFile);
    printf("file closed\n");
    return 0;
}

