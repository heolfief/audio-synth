#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}Building :${NC}"
rm -rf build/run && mkdir -p build/run
cd build/run
cmake ../..
make
cd ../..
echo -e "${BLUE}\nDone${NC}"

echo -e "${BLUE}\nExecuting program :${NC}"
bin/audio_synth
echo -e "${BLUE}\nDone${NC}"
