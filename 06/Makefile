CC = g++
FLAGS =-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread


all: main_bin test_bin 

main_bin: 
	${CC} ${FLAGS} tests.cpp -c

test_bin:
	${CC} tests.o -g -o tests ${TEST_LIB}

test:
	./tests


clean:
	rm -rf *.o
	rm tests
