# CMake generated Testfile for 
# Source directory: /home/heol/Documents/audio-synth/test
# Build directory: /home/heol/Documents/audio-synth/build/debug/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(audio_synth_test "./audio_synth_test")
add_test(audio_synth_test_valgrind "valgrind" "--error-exitcode=1" "--read-var-info=yes" "--leak-check=full" "--show-leak-kinds=all" "./audio_synth_test")
add_test(audio_synth_valgrind "valgrind" "--error-exitcode=1" "--read-var-info=yes" "--leak-check=full" "--show-leak-kinds=all" "./audio_synth_valgrind")
