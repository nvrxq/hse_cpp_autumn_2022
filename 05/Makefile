CC = g++
FLAGS =-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread


all: Serializer.hpp Deserializer.hpp tests.cpp
	${CC} ${FLAGS} tests.cpp -o tests ${TEST_LIB}

test:
	./tests


clean:
	rm -rf *.o
	rm tests
