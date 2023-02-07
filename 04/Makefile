CC = g++
FLAGS =-std=c++20 
TEST_LIB=-lgtest -lgtest_main -lpthread

all: VectorBin BigintBin  MainBin

VectorBin:
	${CC} ${FLAGS} vector.cpp -c

MainBin: 
	${CC} ${FLAGS} vector.o BigInt.o tests.cpp -g -o tests

BigintBin:
	${CC} ${FLAGS} BigInt.cpp -c

run:
	 ./tests

clean:
	rm -rf *.o tests 
