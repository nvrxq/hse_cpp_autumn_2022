#include <iostream>
#include "gtest/gtest.h"

#include "Allocator.hpp"



// Тест успешно пройдёт.
TEST(test_allocator, alloc)
{
    Allocator al;
    al.makeAllocator(10);
    {
        char *res = al.alloc( 5 );
        ASSERT_TRUE( res != nullptr );
    }

   
    {
        char *res = al.alloc(6);
        ASSERT_EQ(res, nullptr);
    }

    {
        char *res = al.alloc(5);
        ASSERT_TRUE(res != nullptr);
    }

    al.reset();
    al.makeAllocator(2);
    {
        char *res = al.alloc( 1 );
        ASSERT_TRUE( res != nullptr );
    }

    {
	size_t offset = al.getOffset();
	ASSERT_EQ(offset,1);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
