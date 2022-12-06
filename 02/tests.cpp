#include "TokenParser.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<uint64_t> digits;
  std::vector<std::string> strings;
  TokenParser parser;
  std::string testing_strings = "24 ya 184467440737095516 test\tdz\nxd 25";
  parser.SetStartCallback([]() {
    std::cout << "Start" << std::endl;
    ;
  });
  parser.SetEndCallback([]() { std::cout << "End!" << std::endl; });
  parser.SetDigitTokenCallback(
      [&digits](uint64_t token) { digits.push_back(token); });
  parser.SetStringTokenCallback(
      [&strings](std::string &line) { strings.push_back(line); });
  parser.Parse(testing_strings);
  for (auto a : digits) {
    std::cout << a << std::endl;
  }
  return 0;
}
