#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "oscillator/osc_test.h"

int main(void)
{
  const struct CMUnitTest tests_oscillator[] =
  {
      cmocka_unit_test_setup_teardown(test_fill_osc_buffer_zeros, setup_osc_buffer, teardown_osc_buffer),
      cmocka_unit_test_setup_teardown(test_fill_osc_buffer_square, setup_osc_buffer, teardown_osc_buffer)
  };
  return cmocka_run_group_tests(tests_oscillator,NULL,NULL);
}