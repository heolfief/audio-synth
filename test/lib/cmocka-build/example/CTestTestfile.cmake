# CMake generated Testfile for 
# Source directory: /home/heol/Documents/audio-synth/test/lib/cmocka-1.1.3/example
# Build directory: /home/heol/Documents/audio-synth/test/lib/cmocka-build/example
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simple_test "simple_test")
add_test(allocate_module_test "allocate_module_test")
set_tests_properties(allocate_module_test PROPERTIES  WILL_FAIL "1")
add_test(assert_macro_test "assert_macro_test")
set_tests_properties(assert_macro_test PROPERTIES  WILL_FAIL "1")
add_test(assert_module_test "assert_module_test")
set_tests_properties(assert_module_test PROPERTIES  WILL_FAIL "1")
subdirs("mock")
