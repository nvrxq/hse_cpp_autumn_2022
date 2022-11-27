#include <iostream>
#include "Allocator.hpp"


Allocator::Allocator(){
	ptr = nullptr;
	offset = 0;
	realSize = 0;
}

Allocator::~Allocator(){
	delete [] ptr;
}

void Allocator::makeAllocator(size_t maxSize){
	delete [] ptr;
	realSize = maxSize;
	ptr = new char[maxSize];
}

char* Allocator::alloc(size_t size){
	if(size + offset < realSize)
	{
		offset += size;
		char *ret = ptr + size;
		return ret;
	}
	return nullptr;
}

void Allocator::reset(){
	offset = 0;
}

int Allocator::getOffset() const{
	return offset;
}

int Allocator::getRealSize() const{
	return realSize;
}
