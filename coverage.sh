#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}\nExecuting code coverage :${NC}"
bin/audio_synth_test > /dev/null 2>&1 #mute output
lcov --capture --directory build/run --output-file build/run/coverage.info
lcov --remove build/run/coverage.info $PWD'/test/*' -o build/run/coverage_clean.info
genhtml build/run/coverage_clean.info --output-directory doc/coverage
echo -e "${BLUE}\nDone${NC}"
echo -e "Please open doc/coverage/index.html to see result\n"
if [ $# -eq 0 ]; then
    echo -e "Opening doc/coverage/index.html with default browser\n"
    xdg-open doc/coverage/index.html
    exit 1
fi
