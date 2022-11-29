CC=g++
FLAGS =-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread


all: Allocator test_bin

test_bin: 
	${CC} ${FLAGS} Allocator.o tests.cpp -o tests ${TEST_LIB}



Allocator: Allocator.cpp Allocator.hpp
	$(CC) $(FLAGS) Allocator.cpp -c

test: 
	./tests

clean:
	rm -rf *.o tests
