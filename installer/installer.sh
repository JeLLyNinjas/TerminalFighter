#!/bin/bash -e

USER=`whoami`
if [ $USER = "root" ]
    then
    echo "Running as ROOT"
else
    echo "***********YOU ARE NOT ROOT************"
    exit 0
fi


DIR=`pwd`

function finish {
	echo "Cleaning up..."
	rm $DIR/SDL2-2.0.3.tar.gz || true
	rm $DIR/SDL2_ttf-2.0.12.tar.gz || true
	rm $DIR/SDL2_image-2.0.0.tar.gz || true
	rm $DIR/SDL2_mixer-2.0.0.tar.gz || true
	rm -rf $DIR/SDL2_image-2.0.0  || true
	rm -rf $DIR/SDL2_ttf-2.0.12  || true
	rm -rf $DIR/SDL2-2.0.3 || true
	rm -rf $DIR/SDL2_mixer-2.0.0 || true
}

trap finish EXIT

#SDL2.0
wget https://www.libsdl.org/release/SDL2-2.0.3.tar.gz
tar -xzvf SDL2-2.0.3.tar.gz
cd SDL2-2.0.3
./configure 


make -j4
make install -j4
cd ..


#SDL2_ttf
apt-get install libfreetype6-dev
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
tar -xzvf SDL2_ttf-2.0.12.tar.gz
cd SDL2_ttf-2.0.12
./configure
make -j4
make install -j4
cd ..

#SDL2_image
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz
tar -xzvf SDL2_image-2.0.0.tar.gz
cd SDL2_image-2.0.0
./configure
make -j4
make install -j4
cd ..
#SDL2_mixer
wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.0.tar.gz
tar -xzvf SDL2_mixer-2.0.0.tar.gz
cd SDL2_mixer-2.0.0
#SMPEG
cd external/smpeg2-2.0.0
./configure
make -j4
make install -j4
cd ../..
./configure
make -j4
make install -j4
cd ..
