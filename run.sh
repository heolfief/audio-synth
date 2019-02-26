#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}\nExecuting program :${NC}"
bin/audio_synth
echo -e "${BLUE}\nDone${NC}"
