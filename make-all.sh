#!/bin/bash -e

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# ./format-all.sh

# if astyle *.h *.cpp -r --dry-run --options=astylerc | grep Formatted; then
#     printf "\n${RED}|*******| STYLE CHECK FAILED |*******|${NC}\n\n"
#     exit 1
# else
#     printf "\n${GREEN}|*******| STYLE CHECK SUCCESSFUL |*******|${NC}\n\n"
# fi

mkdir -p build
cd build
cmake ..
make -j8
# make -j8 VERBOSE=1
if [ $? -eq 0 ]; then
    printf "\n${GREEN}|*******| SOURCE COMPILATION SUCCESSFUL |*******|${NC}\n\n"
else
    printf "\n${RED}|*******| SOURCE COMPILATION FAILED |*******|${NC}\n\n"
    exit 1
fi
cp src/TerminalFighter/TerminalFighter ../
./test/runTests
cd ..

# Update docker if there are any new files
docker build . -t terminal_documentation

# "doxygen -g" will create a default config file named Doxyfile
# "patch < Doxyfile.patch will apply the configuration patch
#sudo docker run --rm -v `pwd`:/documentation test1 /bin/bash -c "doxygen -g && \
    #patch < Doxyfile.patch && doxygen Doxyfile
docker run --rm -v `pwd`:/documentation terminal_documentation /bin/bash -c "doxygen Doxyfile"
