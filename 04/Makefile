CC = g++
FLAGS =-std=c++20 
TEST_LIB=-lgtest -lgtest_main -lpthread

all:  BigintBin  MainBin


MainBin: 
	${CC} ${FLAGS}  BigInt.o tests.cpp -g -o tests

BigintBin:
	${CC} ${FLAGS} BigInt.cpp -c

run:
	 ./tests

clean:
	rm -rf *.o tests 
