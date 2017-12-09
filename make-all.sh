#!/bin/bash -e

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

IMAGE_NAME=jellyninjas/terminalfighterdocs 
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
docker build . -t $IMAGE_NAME

# "doxygen -g" will create a default config file named Doxyfile
# "patch < Doxyfile.patch will apply the configuration patch

#docker run --rm -v `pwd`:/documentation $IMAGE_NAME doxygen -g && patch --no-backup-if-mismatch < Doxyfile.patch && doxygen Doxyfile && /bin/bash -c "chown 1000:1000 -R ."
docker run --rm -v `pwd`:/documentation $IMAGE_NAME /bin/bash -c "doxygen -g" && patch --no-backup-if-mismatch < Doxyfile.patch && /bin/bash -c "doxygen Doxyfile && chown 1000:1000 -R ."
#docker run --rm -v `pwd`:/documentation $IMAGE_NAME /bin/bash -c "doxygen -g" && doxygen Doxyfile && /bin/bash -c "chown 1000:1000 -R ."

