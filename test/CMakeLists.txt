cmake_minimum_required(VERSION 3.2)

enable_testing()

include_directories ("${PROJECT_SOURCE_DIR}/src")

find_library(CMOCKA_LIBRARY cmocka HINTS /lib)

add_executable(audio_synth_test test.c ../src/oscillator/osc.h ../src/oscillator/osc.c oscillator/osc_test.c oscillator/osc_test.h)
add_dependencies(audio_synth_test audio_synth_test)

add_test(audio_synth_test audio_synth_test)
add_test(audio_synth_test_valgrind valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ./audio_synth_test)

target_link_libraries(audio_synth_test -fprofile-arcs -ftest-coverage)
target_compile_options(audio_synth_test PRIVATE -O0 -fprofile-arcs -ftest-coverage)

target_link_libraries(audio_synth_test ${CMOCKA_LIBRARY})
target_link_libraries(audio_synth_test m)

install(TARGETS audio_synth_test RUNTIME DESTINATION bin DESTINATION ${INSTALL_BIN_DIR})
