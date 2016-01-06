OBJS = $(wildcard src/*.cpp) $(filter-out ../src/main.cpp, $(wildcard ../src/*.cpp))

COMPILE_FLAGS = -w -g -std=c++0x

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -pthread 

OUTPUT_NAME = run-tests

INCLUDE_FLAGS = -I../src -Ilib

all :
	 $(CXX) -isystem gtest_include -isystem gmock_include $(INCLUDE_FLAGS) $(OBJS) $(LINK_FLAGS) $(COMPILE_FLAGS) libgmock.a -o $(OUTPUT_NAME)

clean :
	rm run-tests

