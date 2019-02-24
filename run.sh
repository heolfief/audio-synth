#!/bin/bash
echo "Building"
rm -rf build/run && mkdir build/run
cd build/run
cmake ../..
make && make install
cd ../..
echo "Done"

echo "Executing program"
bin/audio_synth
