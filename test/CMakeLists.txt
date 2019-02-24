cmake_minimum_required(VERSION 3.2)

add_executable(audio_synth_test test.h)

install(TARGETS audio_synth_test DESTINATION bin)
