/**
 * \file wav_test.c
 * \brief Wav test functions.
 *
 *
 * Here are implemented the test functions for the Wav
 */
#define TEST_AUDIO_BUFF_SIZE 1024
#define TEST_SAMPLERATE 48000
#define TEST_FILE_PATH "test_file.wav"

#include "wav_test.h"

int setup_wav(void **state)
{
    Core *ac = alloc_core(TEST_AUDIO_BUFF_SIZE);
    if (ac == NULL)
    {
        sys_print_error_test("Memory allocation error on the core during setup_wav");
        return -1;
    }

    // Set file settings, 16bit Mono PCM
    SF_INFO info;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.channels = 1;
    info.samplerate = TEST_SAMPLERATE;

    // Open sound file for writing
    ac->record_param->sndFile = sf_open(TEST_FILE_PATH, SFM_WRITE, &info);
    if (ac->record_param->sndFile == NULL)
    {
        fprintf(stderr, "Error opening sound file '%s': %s\n", TEST_FILE_PATH, sf_strerror(ac->record_param->sndFile));
        return -1;
    }
    *state = ac->record_param->sndFile;

    free_core(ac);

    return 0;

}

int teardown_wav(void **state)
{
    SNDFILE *sndfile = *state;

    // Error handling behaviour test
    assert_int_equal(close_wav_file(NULL), -1);

    if (close_wav_file(sndfile))return -1;

    return 0;
}

void test_write_wav_file(void **state)
{
    SNDFILE *sndfile = *state;
    Audio_Buffer buffer = alloc_audio_buffer(TEST_AUDIO_BUFF_SIZE);
    if (buffer == NULL)fail();

    // Normal behaviour test

    assert_int_equal(write_wav_file(TEST_AUDIO_BUFF_SIZE,buffer,sndfile), 0);

    // Error behaviour test
    assert_int_equal(write_wav_file(TEST_AUDIO_BUFF_SIZE,NULL,sndfile), -1);

    // Error behaviour test
    assert_int_equal(write_wav_file(TEST_AUDIO_BUFF_SIZE,buffer,NULL), -1);

    //checks if the free of the buffer happens correctly
    assert_int_equal(free_audio_buffer(buffer),0);


}
