#include "avl.hpp"
#include <gtest/gtest.h>
#include <iostream>

class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(size_test, avl){
    avl_tree<int, int> tree;
    tree.insert(std::make_pair(0, 24));
    ASSERT_EQ(tree.size(), 1);
    tree.insert(std::make_pair(1, 25));
    ASSERT_EQ(tree.size(), 2);
    tree.insert(std::make_pair(2, 26));
    ASSERT_EQ(tree.size(), 3);
    tree.insert(std::make_pair(3, 27));
    ASSERT_EQ(tree.size(), 4);
    tree.insert(std::make_pair(4, 28));
    ASSERT_EQ(tree.size(), 5);
    tree.insert(std::make_pair(5, 29));
    ASSERT_EQ(tree.size(), 6);
    tree.insert(std::make_pair(6, 30));
    ASSERT_EQ(tree.size(), 7);
    bool empty = tree.empty();
    ASSERT_FALSE(empty);
}
TEST(valid_data, avl){
    avl_tree<int, std::string> tree;
    tree.insert(std::make_pair(0, "test1"));
    tree.insert(std::make_pair(1, "test2"));
    tree.insert(std::make_pair(2, "test3"));
    tree.insert(std::make_pair(3, "test4"));
    tree.insert(std::make_pair(4, "test5"));
    ASSERT_EQ(tree[0], "test1");
    ASSERT_EQ(tree[1], "test2");
    ASSERT_EQ(tree[2], "test3");
    ASSERT_EQ(tree[3], "test4");
    ASSERT_EQ(tree[4], "test5");
    bool empty = tree.empty();
    ASSERT_FALSE(empty);
    
}
TEST(erase_test, avl){
    avl_tree<int, int> tree;
    for(size_t i = 0; i < 10; ++i)
    tree.insert(std::make_pair(i, i+1));
    tree.erase(2);
    tree.erase(5);
    ASSERT_EQ(tree.size(), 8);
}




int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}