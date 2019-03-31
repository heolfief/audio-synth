#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}\nExecuting test program :${NC}"
cp CTestTestfile.cmake bin
cd bin
ctest --output-on-failure $1
e=$?
echo -e "${BLUE}\nDone${NC}"
rm -rf Testing CTestTestfile.cmake
exit $e
