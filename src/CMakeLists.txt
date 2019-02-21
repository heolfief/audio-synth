cmake_minimum_required(VERSION 3.13)
project(audio_synth C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(audio_synth main.c fichier/fichier.h fichier/fichier.c midi/midi.h)

target_link_libraries(audio_synth ${SDL2_LIBRARIES})
target_link_libraries(audio_synth m)
