cmake_minimum_required(VERSION 3.2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(SOURCE_FILES main.c
		 oscillator/osc.h oscillator/osc.c
		 note/note.c note/note.h
		 note/adsr.h
		 note/polyphony.c note/polyphony.h
		 gui/gui.c gui/gui.h
		 sys_param/sys_param.c sys_param/sys_param.h
		 audio/audio.c audio/audio.h
		 )

add_executable(audio_synth ${SOURCE_FILES})
add_executable(audio_synth_valgrind ${SOURCE_FILES})

target_compile_definitions(audio_synth_valgrind PRIVATE VALGRIND)

target_link_libraries(audio_synth ${SDL2_LIBRARIES})
target_link_libraries(audio_synth m)

target_link_libraries(audio_synth_valgrind ${SDL2_LIBRARIES})
target_link_libraries(audio_synth_valgrind m)


install(TARGETS audio_synth
	RUNTIME DESTINATION bin	
	DESTINATION ${INSTALL_BIN_DIR})

install(TARGETS audio_synth_valgrind
	RUNTIME DESTINATION bin	
	DESTINATION ${INSTALL_BIN_DIR})
