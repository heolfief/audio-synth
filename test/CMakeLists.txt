cmake_minimum_required(VERSION 3.2)

enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/src")

find_library(CMOCKA_LIBRARY cmocka HINTS ../test/lib/cmocka-build/src)

add_executable(audio_synth_test test.c
        #Sources files
        ../src/core/audio_core.c ../src/core/audio_core.h
        ../src/audio_fx/audio_fx.c ../src/audio_fx/audio_fx.h
        ../src/core/note/note.c ../src/core/note/note.h ../src/core/note/adsr.h
        ../src/core/note/polyphony.h ../src/core/note/polyphony.c
        ../src/core/oscillator/osc.h ../src/core/oscillator/osc.c
        ../src/Listmidi/listmidi.c ../src/Listmidi/listmidi.h
        ../src/system/error_handler.h
        ../src/sys_param/sys_param.h ../src/sys_param/sys_param.c
        ../src/audio_fx/ext_effects/snd.c ../src/audio_fx/ext_effects/snd.h
        ../src/audio_fx/ext_effects/biquad.c ../src/audio_fx/ext_effects/biquad.h
        ../src/audio_fx/ext_effects/mem.c ../src/audio_fx/ext_effects/mem.h

        #Tests files
        oscillator_test/osc_test.c oscillator_test/osc_test.h
        note_test/note_test.c note_test/note_test.h
        note_test/polyphony_test.c note_test/polyphony_test.h
        core_test/core_test.c core_test/core_test.h
        sys_param_test/sys_param_test.c sys_param_test/sys_param_test.h list_midi_test/list_midi_test.c list_midi_test/list_midi_test.h midi/midi_list.c midi/midi_list.h)

add_dependencies(audio_synth_test audio_synth_test)

add_test(audio_synth_test audio_synth_test)
add_test(audio_synth_test_valgrind valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ./audio_synth_test)

target_compile_definitions(audio_synth_test PRIVATE TEST)

target_link_libraries(audio_synth_test -fprofile-arcs -ftest-coverage)
target_compile_options(audio_synth_test PRIVATE -O0 -fprofile-arcs -ftest-coverage)

target_link_libraries(audio_synth_test ${CMOCKA_LIBRARY})
target_link_libraries(audio_synth_test m)

install(TARGETS audio_synth_test RUNTIME DESTINATION bin DESTINATION ${INSTALL_BIN_DIR})
