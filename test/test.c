#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "oscillator_test/osc_test.h"
#include "note_test/note_test.h"

int main(void) {
    const struct CMUnitTest tests[] =
    {
        // Oscillator tests
        cmocka_unit_test_setup_teardown(test_fill_osc_buffer_unknown, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_fill_osc_buffer_zeros, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_fill_osc_buffer_sine, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_fill_osc_buffer_square, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_fill_osc_buffer_tri, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_osc_init_default_values, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_osc_fill_buffer_null, setup_osc, teardown_osc),
        cmocka_unit_test_setup_teardown(test_osc_fill_buffer_incorect_amp, setup_osc, teardown_osc),


        // Note tests
        cmocka_unit_test_setup_teardown(test_note_on, setup_note, teardown_note),
        cmocka_unit_test_setup_teardown(test_note_off, setup_note, teardown_note),
        cmocka_unit_test_setup_teardown(test_update_envelope, setup_note, teardown_note),
        cmocka_unit_test_setup_teardown(test_note_fill_buffer, setup_note, teardown_note),
        cmocka_unit_test(test_get_freq_from_note_nbr)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}