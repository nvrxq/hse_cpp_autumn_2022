#include "TokenParser.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

TEST(test_parser, parser) {
  TokenParser Lib;
  const std::string Line =
      "24 2*2=4 test 18446744073709551614 1251215\t25256\nParseLib ";
  //
  // Check StartCallback && EndCallback && empty functions

  {
    std::string start_str;
    std::string end_str;
    Lib.SetStartCallback([&start_str]() { start_str.push_back('S'); });

    Lib.SetEndCallback([&end_str]() { end_str.push_back('E'); });
    Lib.SetDigitTokenCallback();
    Lib.SetStringTokenCallback();
    Lib.Parse(Line);
    // TEST
    ASSERT_EQ(start_str, "S");
    ASSERT_EQ(end_str, "E");
  }

  Lib.SetEndCallback();
  Lib.SetStartCallback();
  // Test StringCallBack func
  {
    std::vector<std::string> string_tokens;
    std::vector<std::string> answer{"2*2=4", "test", "18446744073709551614",
                                    "ParseLib"};
    // INIT
    Lib.SetStringTokenCallback(
        [&string_tokens](std::string &line) { string_tokens.push_back(line); });
    Lib.SetDigitTokenCallback();
    Lib.Parse(Line);
    // TEST
    ASSERT_EQ(string_tokens, answer);
  }
  // Test DigitCallback func
  {
    std::vector<uint64_t> digit_tokens;
    std::vector<uint64_t> answer{24, 1251215, 25256};
    // INIT
    Lib.SetStringTokenCallback();
    Lib.SetDigitTokenCallback(
        [&digit_tokens](uint64_t token) { digit_tokens.push_back(token); });
    Lib.Parse(Line);
    ASSERT_EQ(digit_tokens, answer);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
