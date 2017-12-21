#!/bin/bash

readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

function src {
	mkdir -p "$DIR"/build
	(cd $DIR/build && cmake ..)
	(cd "$DIR"/build && make -j8)

	if [ $? -eq 0 ]; then
    	printf "\n${GREEN}|*******| SOURCE COMPILATION SUCCESSFUL |*******|${NC}\n\n"
	else
    	printf "\n${RED}|*******| SOURCE COMPILATION FAILED |*******|${NC}\n\n"
    	exit 1
	fi

	cp "$DIR"/build/src/TerminalFighter/TerminalFighter "$DIR"/TerminalFighter
}

function format {
	(cd "$DIR" && astyle *.h *.cpp -r --options=astylerc)
	find "$DIR" -name "*.orig" -delete
}

function docs {
	(cd "$DIR"/documentation && doxygen -g)
	(cd "$DIR"/documentation && patch --no-backup-if-mismatch < $DIR/documentation/Doxyfile.patch)
	doxygen "$DIR"/documentation/Doxyfile
	rm $DIR/documentation/Doxyfile
}

function clean {
	rm -r $DIR/build
}

if [ "$1" == "all" ]; then
	src
	format
	docs
elif [ "$1" == "src" ]; then
	src
elif [ "$1" == "format" ]; then
	format
elif [ "$1" == "docs" ]; then
	docs
elif [ "$1" == "clean" ]; then
	clean
else
	echo "usage: $0 [all | src | format | docs | clean]"
fi
