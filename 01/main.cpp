#include <iostream>
#include "Allocator.hpp"

int main(){
	Allocator allocOBJ;
	std::cout<<"Test1"<<std::endl;
	allocOBJ.makeAllocator(10);
	char* t = allocOBJ.alloc(5);
	if(t != nullptr){
		std::cout << "est' mesto" << std::endl;
	}
	else{
		std::cout << "net mesta" << std::endl;
	}
	return 0;
}
