cmake_minimum_required(VERSION 3.2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(audio_synth main.c oscillator/osc.h oscillator/osc.c note/note.c note/note.h gui/gui.c gui/gui.h)

target_link_libraries(audio_synth ${SDL2_LIBRARIES})
target_link_libraries(audio_synth m)


install(TARGETS audio_synth
	RUNTIME DESTINATION bin	
	DESTINATION ${INSTALL_BIN_DIR})
