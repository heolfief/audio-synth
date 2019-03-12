cmake_minimum_required(VERSION 3.2)

enable_testing()

include_directories ("${PROJECT_SOURCE_DIR}/src")

find_library(CMOCKA_LIBRARY cmocka HINTS /lib)

add_executable(audio_synth_test test.c
        #Sources files
        ../src/note/note.c ../src/note/note.h ../src/note/adsr.h
        ../src/note/polyphony.h ../src/note/polyphony.c
        ../src/oscillator/osc.h ../src/oscillator/osc.c

        #Tests files
        oscillator_test/osc_test.c oscillator_test/osc_test.h
        note_test/note_test.c note_test/note_test.h
        note_test/polyphony_test.c note_test/polyphony_test.h
        )

add_dependencies(audio_synth_test audio_synth_test)

add_test(audio_synth_test audio_synth_test)
add_test(audio_synth_test_valgrind valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ./audio_synth_test)

target_link_libraries(audio_synth_test -fprofile-arcs -ftest-coverage)
target_compile_options(audio_synth_test PRIVATE -O0 -fprofile-arcs -ftest-coverage)

target_link_libraries(audio_synth_test ${CMOCKA_LIBRARY})
target_link_libraries(audio_synth_test m)

install(TARGETS audio_synth_test RUNTIME DESTINATION bin DESTINATION ${INSTALL_BIN_DIR})
