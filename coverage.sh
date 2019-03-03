#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}\nExecuting code coverage :${NC}"
bin/audio_synth_test > /dev/null 2>&1
lcov --capture --directory build/run --output-file build/run/coverage.info
genhtml build/run/coverage.info --output-directory doc/coverage
echo -e "${BLUE}\nDone${NC}"
echo -e "Please open doc/coverage/index.html to see result\n"
