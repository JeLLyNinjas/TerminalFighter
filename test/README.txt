Testing in Terminal Fighter is done with googletest and googlemock, the header files are included in this project.
You must compile the library that has the definitions yourself. 
Meaning you need a `libgmock.a` archive file in this directory in order to compile the tests. 

To create a `libgmock.a` file follow these instructions in an arbitrary dir.

1. Get the googletest and googlemock source code:
	`git clone https://github.com/google/googletest.git`

2. Go into the cloned directory 
	`cd googletest/`

3. Compile googletest:	
	`g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googletest/src/gtest-all.cc`

4. Compile googlemock:
	`g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googlemock/src/gmock-all.cc`

5. Collect both the resulting .o files into an archive file:
	`ar -rv libgmock.a gtest-all.o gmock-all.o`

Congratulations! You now have a `libgmock.a` archive file, now include it in the `TerminalFighter/test/` directory and you should be good to go, run `make` in the test directory to check if you can compile the tests.