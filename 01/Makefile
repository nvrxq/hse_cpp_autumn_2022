CC=g++
FLAGS =-std=c++17 -Wall -pedantic -Werror -Wextra

all: alloc

alloc : main.o Allocator.o
	$(CC) $(FLAGS) main.o Allocator.o -o main
	./main

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

Allocator.o: Allocator.cpp
	$(CC) $(FLAGS) Allocator.cpp -c

clean:
	rm -rf *.o main
