#include "BigInt.hpp"
#include <gtest/gtest.h>
#include <iostream>



class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};


TEST(standart_test, bigint){
  // Арифметические тесты
  BigInt a = 1;
  BigInt b("123456789");
  BigInt d;
  d = a + b;                    // operator +
  ASSERT_EQ(d,123456790);
  d = a - b;                    // operator -
  ASSERT_EQ(d, -123456788);
  d = a * 1234;                 // operator *
  ASSERT_EQ(d, 1234);
}


TEST(move_test, bigint){
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);  //rvalue 
    a = d + b;
    BigInt result("246913578024691357802469135782");
    bool equals = a == result;
    ASSERT_TRUE(equals);
}


TEST(bool_test, bigint){
  BigInt a = 24;
  BigInt b = 25;
  bool gr = a > b;
  bool _gr = a < b;
  ASSERT_FALSE(gr);
  ASSERT_TRUE(_gr);
  b = -25;
  gr = a > b;
  _gr = a < b;
  ASSERT_TRUE(gr);
  ASSERT_FALSE(_gr);
}

TEST(unusual_situations, bigint){
   BigInt a = -141;
   BigInt b("-225");
   BigInt c = a*b;
   ASSERT_EQ(c, 31725);
}


TEST(invalid_data, bigint){
  ASSERT_THROW(BigInt b("dva"), std::invalid_argument);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}