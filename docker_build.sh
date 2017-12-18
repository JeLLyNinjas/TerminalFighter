#!/bin/bash

readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
readonly IMAGE_NAME="jellyninjas/terminalfighter"

if [[ $# -eq 0 ]]; then
	echo "usage: docker_build [init | shell | <build.sh args>]"
	exit 1
fi

if [[ "$1" == "init" ]]; then
	docker build -t $IMAGE_NAME $DIR
elif [ "$1" == "shell" ]; then
	docker run --rm -it \
		-v $DIR:/TerminalFighter/ \
		$IMAGE_NAME /bin/bash
else
	docker run --rm \
		-v $DIR:/TerminalFighter/ \
		$IMAGE_NAME ./build.sh "$1"
	docker run --rm \
		-v $DIR:/TerminalFighter/ \
		$IMAGE_NAME chown -R 1000:1000 .
fi

