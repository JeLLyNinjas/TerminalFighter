#!/bin/bash

readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
readonly IMAGE_NAME="jellyninjas/terminalfighter"

if [ "$1" == "init" ]; then
	docker build -t $IMAGE_NAME $DIR
elif [ "$1" == "build" ]; then
	docker run --rm \
		-v $DIR:/TerminalFighter/ \
		$IMAGE_NAME ./make-all.sh
elif [ "$1" == "clean" ]; then
	rm $DIR/build/CMakeCache.txt
	rm $DIR/build/test/gtest/src/gtest-build/CMakeCache.txt
elif [ "$1" == "shell" ]; then
	docker run --rm -it \
		-v $DIR:/TerminalFighter/ \
		$IMAGE_NAME /bin/bash
else
	echo "usage: docker_build [init | build | shell]"
fi

