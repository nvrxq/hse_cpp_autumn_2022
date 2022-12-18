CC = g++
FLAGS =-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: MatrixBin mainMat

MatrixBin:
	${CC} ${FLAGS} Matrix.cpp -c

mainMat: 
	${CC} ${FLAGS} Matrix.o main.cpp -g -o main ${TEST_LIB}


test:
	./main

clean:
	rm -rf *.o main
