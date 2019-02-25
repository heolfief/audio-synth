#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "oscillator/osc.h"

#define TEST_SAMPLE_RATE 48000
#define TEST_AUDIO_BUFF_SIZE 1024

static int setup_osc_buffer(void **state)
{
  Oscillator osc;
  osc.buffer = alloc_osc_buffer(TEST_AUDIO_BUFF_SIZE);

  assert_non_null(osc.buffer);

  *state = osc.buffer;
  return 0;
}

static int teardown_osc_buffer(void **state)
{
  free_osc_buffer(*state);
  return 0;
}

static void test_fill_osc_buffer_zeros(void **state)
{
  Oscillator osc;
  osc.buffer = *state;

  osc.amp = 32000;  // Set amplitude to something not zero
  osc.wave = TRI;   // Set wave to anything
  osc.detune = 0;   // Set detune to zero
  osc.freq = 1000;  // Set frequency to something
  osc.duty = 50;    // Set dutycycle to something
  osc.onoff = OFF;  // Most important : set oscillator to OFF, therefore buffer should be filled with zeros by osc_fill_buffer

  osc_fill_buffer(&osc, osc.buffer, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);
  assert_int_equal(*osc.buffer, 0);
}

static void test_fill_osc_buffer_square(void **state)
{
  Oscillator osc;
  osc.buffer = *state;

  osc.amp = 32000;  // Set amplitude to something not zero
  osc.wave = SQR;   // Set wave to square
  osc.detune = 0;   // Set detune to zero
  osc.freq = 1000;  // Set frequency to something
  osc.onoff = ON;   // Set oscillator to ON

  osc.duty = 100;   // Most important : set dutycycle 100%, therefore, osc.buffer should be filled with osc.amp
  osc_fill_buffer(&osc, osc.buffer, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);
  assert_int_equal(*osc.buffer, osc.amp);

  osc.duty = 0;   // Most important : set dutycycle 0%, therefore, osc.buffer should be filled with -osc.amp
  osc_fill_buffer(&osc, osc.buffer, TEST_AUDIO_BUFF_SIZE, TEST_SAMPLE_RATE, 0);
  assert_int_equal(*osc.buffer, -osc.amp);
}

int main(void)
{
  const struct CMUnitTest tests_oscillator[] =
  {
      cmocka_unit_test_setup_teardown(test_fill_osc_buffer_zeros, setup_osc_buffer, teardown_osc_buffer),
      cmocka_unit_test_setup_teardown(test_fill_osc_buffer_square, setup_osc_buffer, teardown_osc_buffer)
  };
  return cmocka_run_group_tests(tests_oscillator,NULL,NULL);
}