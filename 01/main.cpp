#include <iostream>
#include "Allocator.hpp"

int main(){
	Allocator allocator;
	std::cout<<"Test1"<<std::endl;
	allocator.makeAllocator(10);
	allocator.makeAllocator(2);

	char* t = allocator.alloc(5);
	if(t != nullptr){
		std::cout << "est' mesto" << std::endl;
	}
	else{
		std::cout << "net mesta" << std::endl;
	}
	return 0;
}
