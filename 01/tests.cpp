#include <iostream>
#include "gtest/gtest.h"
#include "Allocator.hpp"


TEST(test_allocator, alloc)
{
    Allocator al;
    {
	char* res = al.alloc(1);
	ASSERT_EQ(res, nullptr);
    }
    al.makeAllocator(10);
   	 // Add memory
    {
        char *res = al.alloc( 5 );
        ASSERT_TRUE( res != nullptr );
    }
	//Overflow
    {
        char *res = al.alloc(6);
        ASSERT_EQ(res, nullptr);
    }
   	 // Add Memory
    {
        char *res = al.alloc(5);
        ASSERT_TRUE(res != nullptr);
    } 
   	 // Reset
    al.reset();
    al.makeAllocator(10);
    {
        char *res = al.alloc(2);
        ASSERT_TRUE( res != nullptr );
    }
   
    {
	char *res = al.alloc(9);
	ASSERT_EQ(res, nullptr);
    }
    al.reset();

    {
	 char *res = al.alloc(9);
	 ASSERT_TRUE(res != nullptr);
    }
   	 // Chech getter and 0 byte memory
    {
	  char *res = al.alloc(0);
	  ASSERT_EQ(res, nullptr);
    }
    {
	  size_t offset = al.getOffset();
	  ASSERT_EQ(offset,9);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
