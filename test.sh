#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}Building :${NC}"
rm -rf build/test && mkdir -p build/test
cd build/test
cmake ../..
make
pwd
cd ../..
echo -e "${BLUE}\nDone${NC}"
pwd
echo -e "${BLUE}\nExecuting test program :${NC}"
ctest $1
rm Testing -r
echo -e "${BLUE}\nDone${NC}"
