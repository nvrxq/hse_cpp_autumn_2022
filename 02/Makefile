CC=g++
FLAGS =-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread


all: TokenParser test_bin 

test_bin: 
	${CC} ${FLAGS} TokenParser.o tests.cpp -g -o tests  ${TEST_LIB}

TokenParser: TokenParser.hpp TokenParser.cpp
	$(CC) $(FLAGS) TokenParser.cpp -c

test: 
	 ./tests
clean:
	rm -rf *.o tests
