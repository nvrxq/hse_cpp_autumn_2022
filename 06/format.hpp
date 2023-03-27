#include "exception.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

template <typename Arg> std::string getArg(Arg &&rightArg) {
  std::ostringstream os;
  os << rightArg;
  return os.str();
}

template <typename... Args>
std::string format(std::string format_string, Args &&...args) {
  std::vector<int> idx;
  std::string digit;
  std::string resultString;
  bool stackStatus = false;
  size_t len = format_string.length();
  std::vector<std::string> formatArgs = {getArg(std::forward<Args>(args))...};

  for (size_t i = 0; i < len; ++i) {
    if ((stackStatus && format_string[i] == '{') ||
        (!stackStatus && format_string[i] == '}'))
      throw BadBraceException("Unexpected brace!");
    if (stackStatus && format_string[i] == '}') {
      size_t idx = std::stoi(digit);
      if (idx > formatArgs.size()) {
        throw RangeErrorException("Range Error!");
      } else {
        resultString += formatArgs[idx];
      }
      stackStatus = false;
      digit = "";
    }
    if (stackStatus)
      digit += format_string[i];

    if (!stackStatus && format_string[i] == '{') {
      stackStatus = true;
    }
    if (!stackStatus && format_string[i] != '}') {
      resultString += format_string[i];
    }
  }
  // std::cout << resultString << std::endl;
  return resultString;
}
