#pragma once
#include <iostream>

class Allocator
{
	public:
		Allocator();
		void makeAllocator(size_t maxSize);
		char* alloc(size_t size);
		void reset();

		~Allocator();
	private:
		size_t offset;
		size_t realSize;
		char* ptr;
};
