CC = g++
FLAGS =-std=c++20 
TEST_LIB=-lgtest -lgtest_main -lpthread

all:    MainBin


MainBin: 
	${CC} ${FLAGS} BigInt.cpp tests.cpp -g -o tests ${TEST_LIB}

test:
	 ./tests

clean:
	rm -rf *.o tests 
