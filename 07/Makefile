CC = g++
FLAGS =-std=c++20 -Wall -pedantic  -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread


all: avl

avl: 
	${CC} ${FLAGS} tests.cpp -o tests ${TEST_LIB}

test:
	./tests


clean:
	rm -rf *.o
	rm tests
