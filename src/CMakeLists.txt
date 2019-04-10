cmake_minimum_required(VERSION 3.2)

find_package(SDL2 REQUIRED)
find_package(LibXml2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIR})

set(SOURCE_FILES main.c
        core/audio_core.c core/audio_core.h
        core/oscillator/osc.h core/oscillator/osc.c
        core/note/note.c core/note/note.h
        core/note/adsr.h
        core/note/polyphony.c core/note/polyphony.h
        gui/gui.c gui/gui.h
        sys_param/sys_param.c sys_param/sys_param.h
        audio/audio.c audio/audio.h
        system/error_handler.h
        audio_fx/audio_fx.c audio_fx/audio_fx.h
        sys_param/xml/preset_xml.c sys_param/xml/preset_xml.h
        audio_fx/ext_effects/snd.c audio_fx/ext_effects/snd.h
        audio_fx/ext_effects/mem.c audio_fx/ext_effects/mem.h
        audio_fx/ext_effects/biquad.c audio_fx/ext_effects/biquad.h
        audio_fx/ext_effects/mem.c audio_fx/ext_effects/mem.h
        )

add_executable(audio_synth ${SOURCE_FILES})
add_executable(audio_synth_valgrind ${SOURCE_FILES})

target_compile_definitions(audio_synth_valgrind PRIVATE VALGRIND)

target_link_libraries(audio_synth ${SDL2_LIBRARIES} ${LIBXML2_LIBRARIES})
target_link_libraries(audio_synth m)

target_link_libraries(audio_synth_valgrind ${SDL2_LIBRARIES} ${LIBXML2_LIBRARIES})
target_link_libraries(audio_synth_valgrind m)


install(TARGETS audio_synth
        RUNTIME DESTINATION bin
        DESTINATION ${INSTALL_BIN_DIR})

install(TARGETS audio_synth_valgrind
        RUNTIME DESTINATION bin
        DESTINATION ${INSTALL_BIN_DIR})
