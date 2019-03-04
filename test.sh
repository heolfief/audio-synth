#!/bin/bash

BLUE='\033[1;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}\nExecuting test program :${NC}"
ctest --output-on-failure $1
rm Testing -r
exit $exit_status
echo -e "${BLUE}\nDone${NC}"
