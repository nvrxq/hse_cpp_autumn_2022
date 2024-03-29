#include "format.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

class Tests : public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}
};

TEST(tests_format, test1) {
  std::string testString1 = "{1}+{1} = {0}";
  auto test1 = format(testString1, 2, "one");
  ASSERT_EQ(test1, "one+one = 2");

  std::string testStrin2 = "dwa plus {0} ravno {1}";
  auto test2 = format(testStrin2, 10, 12);
  ASSERT_EQ(test2, "dwa plus 10 ravno 12");
}

TEST(Except, test2) {
  std::string testStringOutRange = "test out for {25}";
  std::string testStringBadBrace = "testing }{24}";
  ASSERT_THROW(format(testStringOutRange, "range"), RangeErrorException);
  ASSERT_THROW(format(testStringBadBrace, "425"), BadBraceException);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
