#OBJS = files to compile
OBJS = $(wildcard src/*.cpp) 

#COMPLIE_FLAGS = additional flags
COMPILE_FLAGS = -Werror -g -std=c++0x

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -pthread
	

#OUTPUT_NAME = final name
OUTPUT_NAME = TerminalFighter

#INCLUDE FLAGS
INCLUDE_FLAGS = -Ilib -Iinclude

all :
	 $(CXX) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS) -o $(OUTPUT_NAME)

clean :
	rm $(OUTPUT_NAME)

