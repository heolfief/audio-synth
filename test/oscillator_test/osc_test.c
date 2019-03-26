/**
 * \file osc_test.c
 * \brief Oscillator test functions.
 *
 *
 * Here are implemented the test functions for the oscillator
 */
#include "osc_test.h"

#define TEST_SAMPLE_RATE 48000
#define TEST_AUDIO_BUFF_SIZE 1024


int setup_osc(void **state)
{
    Oscillator *osc = NULL;
    osc = alloc_osc(TEST_AUDIO_BUFF_SIZE);
    if(osc == NULL)
    {
        return -1;
    }

    *state = osc;
    return 0;
}

int teardown_osc(void **state)
{
    free_osc(*state);
    return 0;
}

void test_fill_osc_buffer_unknown(void **state)
{
    Oscillator *osc = *state;

    int return_value = 0;

    osc->amp = 32000;  // Set amplitude to something not zero
    osc->wave = 100;   // Set wave to unknown
    osc->detune = 0;   // Set detune to zero
    osc->freq = 1000;  // Set frequency to something
    osc->duty = 50;    // Set dutycycle to something
    osc->onoff = ON;   // Set oscillator to ON

    return_value = osc_fill_buffer(osc, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);

    assert_int_equal(return_value, -1);
}

void test_fill_osc_buffer_zeros(void **state)
{
    Oscillator *osc = *state;

    osc->amp = 32000;  // Set amplitude to something not zero
    osc->wave = TRI;   // Set wave to anything
    osc->detune = 0;   // Set detune to zero
    osc->freq = 1000;  // Set frequency to something
    osc->duty = 50;    // Set dutycycle to something
    osc->onoff = OFF;  // Most important : set oscillator to OFF, therefore buffer should be filled with zeros by osc_fill_buffer

    osc_fill_buffer(osc, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);

    for(Uint16 sample = 0; sample < TEST_AUDIO_BUFF_SIZE; ++sample)
    {
        assert_int_equal(osc->buffer[sample], 0);
    }
}

void test_fill_osc_buffer_sine(void **state)
{
    Oscillator *osc = *state;

    // Known values for 10000*sin(2*pi*t) with t=0:0.1:10
    int res[10] = {0, 5877, 9510, 9510, 5877, 0, -5877, -9510, -9510, -5877};

    osc->amp = 10000;  // Set amplitude
    osc->wave = SIN;   // Set wave to sine
    osc->detune = 0;   // Set detune to zero
    osc->freq = 1;     // Set frequency to 1Hz
    osc->onoff = ON;   // Set oscillator to ON
    osc->duty = 50;    // Set dutycycle 50%

    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)

    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res[i]);
    }

    osc_fill_buffer(osc, 10, 10, 5);   // test phase, phase = half period

    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res[(i+5)%10]);    // test if sine is translated by half a period
    }
}

void test_fill_osc_buffer_square(void **state)
{
    Oscillator *osc = *state;

    // Known values for dutycycle = 0%
    static const int res_0[10] = {-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000, -10000};

    // Known values for dutycycle = 25%
    static const int res_25[10] = {10000, 10000, 10000,-10000,-10000,-10000,-10000,-10000,-10000, -10000};

    // Known values for dutycycle = 50%
    static const int res_50[10] = {10000, 10000, 10000, 10000, 10000,-10000,-10000,-10000,-10000, -10000};

    // Known values for dutycycle = 75%
    static const int res_75[10] = {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,-10000, -10000};

    // Known values for dutycycle = 100%
    static const int res_100[10] = {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000};

    osc->amp = 10000;  // Set amplitude to something not zero
    osc->wave = SQR;   // Set wave to square
    osc->detune = 0;   // Set detune to zero
    osc->freq = 1;  // Set frequency to something
    osc->onoff = ON;   // Set oscillator to ON

    osc->duty = 0;    // Set dutycycle 0%
    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)
    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_0[i]);
    }

    osc->duty = 25;    // Set dutycycle 25%
    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)
    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_25[i]);
    }

    osc->duty = 50;    // Set dutycycle 50%
    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)
    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_50[i]);
    }

    osc->duty = 75;    // Set dutycycle 75%
    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)
    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_75[i]);
    }

    osc->duty = 100;    // Set dutycycle 100%
    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)
    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_100[i]);
    }
}

void test_fill_osc_buffer_tri(void **state)
{
    Oscillator *osc = *state;

    // Known values for dutycycle = 50%
    static const int res_50[10] = {0, 2000, 4000, 6000, 8000, 10000, 8000, 6000, 4000, 2000};

    // Known values for dutycycle = 100%
    static const int res_100[10] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};

    int avg = 5000;

    osc->amp = 10000;  // Set amplitude
    osc->wave = TRI;   // Set wave to sine
    osc->detune = 0;   // Set detune to zero
    osc->freq = 1;     // Set frequency to 1Hz
    osc->onoff = ON;   // Set oscillator to ON

    osc->duty = 50;    // Set dutycycle 50%

    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)

    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_50[i]-avg);
    }

    osc->duty = 100;    // Set dutycycle 100%

    osc_fill_buffer(osc, 10, 10, 0);   // samplerate = buffsize = 10 (10 sample/s : 1Hz so 10 samples for a wave period)

    for(int i = 0; i<10; ++i)
    {
        assert_int_equal(osc->buffer[i], res_100[i]-avg);
    }
}

void test_osc_fill_buffer_null(void **state)
{
    Oscillator *osc = *state;

    int return_value = osc_fill_buffer(NULL, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, -1);
}

void test_osc_fill_buffer_incorect_amp(void **state)
{
    Oscillator *osc = *state;
    int return_value = 0;


    osc_init_default_values(osc, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);

    osc->amp = OSC_AMP_MAX + 1;

    return_value = osc_fill_buffer(osc, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);
    assert_int_equal(return_value, -1);
}

void test_osc_init_default_values(void **state)
{
    Oscillator *osc = *state;

    osc_init_default_values(osc, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE);

    assert_int_equal(osc->amp, DEFAULT_OSC_AMP);
    assert_int_equal(osc->wave, DEFAULT_OSC_WAVE);
    assert_int_equal(osc->detune, DEFAULT_OSC_DETUNE);
    assert_int_equal(osc->onoff, DEFAULT_OSC_ONOFF);
    assert_int_equal(osc->duty, DEFAULT_OSC_DUTY);
    assert_int_equal(osc->freq, DEFAULT_OSC_FREQ);
}