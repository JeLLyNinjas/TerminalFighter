#!/bin/bash -e

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     MACHINE=Linux;;
    Darwin*)    MACHINE=Mac;;
    CYGWIN*)    MACHINE=Cygwin;;
    MINGW*)     MACHINE=MinGw;;
    *)          MACHINE="UNKNOWN:${unameOut}"
esac
echo Machine identified as $MACHINE

if [ $MACHINE = Linux ]; then
    USER=`whoami`
    if [ $USER = "root" ]
        then
        echo "Running as ROOT"
    else
        echo "***********YOU ARE NOT ROOT************"
        exit 1
    fi
fi

DIR=`pwd`

function finish {
    echo "Cleaning up..."
    rm $DIR/pkgconfig.tgz || true
    rm $DIR/SDL2-2.0.7.tar.gz || true
    rm $DIR/freetype-2.8.tar.gz || true
    rm $DIR/SDL2_ttf-2.0.14.tar.gz || true
    rm $DIR/SDL2_image-2.0.2.tar.gz || true
    rm $DIR/SDL2_mixer-2.0.2.tar.gz || true
    rm -rf $DIR/pkg-config-0.28 || true
    rm -rf $DIR/SDL2_image-2.0.2  || true
    rm -rf $DIR/freetype-2.8 || true
    rm -rf $DIR/SDL2_ttf-2.0.14  || true
    rm -rf $DIR/SDL2-2.0.7 || true
    rm -rf $DIR/SDL2_mixer-2.0.2 || true
    rm -rf $DIR/glog || true
    rm -rf $DIR/yaml-cpp || true
}

trap finish EXIT

#pkg-config
if [ $MACHINE = Mac ]; then
    curl https://pkg-config.freedesktop.org/releases/pkg-config-0.28.tar.gz -o pkgconfig.tgz
    tar -zxf pkgconfig.tgz && cd pkg-config-0.28
    ./configure --with-internal-glib && make install
fi

#SDL2.0
wget https://www.libsdl.org/release/SDL2-2.0.7.tar.gz
tar xzf SDL2-2.0.7.tar.gz
cd SDL2-2.0.7
./configure
make -j4
make install -j4
cd $DIR

#SDL2_ttf
wget -O freetype-2.8.tar.gz https://sourceforge.net/projects/freetype/files/freetype2/2.8/freetype-2.8.tar.gz/download
tar xzf freetype-2.8.tar.gz
cd freetype-2.8
./configure
make -j4
make install -j4
cd $DIR

wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
tar xzf SDL2_ttf-2.0.14.tar.gz
cd SDL2_ttf-2.0.14
./configure
make -j4
make install -j4
cd $DIR

#SDL2_image
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.2.tar.gz
tar xzf SDL2_image-2.0.2.tar.gz
cd SDL2_image-2.0.2
./configure
make -j4
make install -j4
cd $DIR

#SDL2_mixer
wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.2.tar.gz
tar xzf SDL2_mixer-2.0.2.tar.gz
cd SDL2_mixer-2.0.2

#SMPEG
cd external/smpeg2-2.0.0
./configure
make -j4
make install -j4
cd ../../
./configure
make -j4
make install -j4
cd $DIR

# glog
git clone https://github.com/google/glog.git
cd glog
mkdir build
cd build
cmake ..
make -j4
make install -j4
cd $DIR

# yaml-cpp
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build
cd build
cmake ..
make -j4
make install -j4
cd $DIR
