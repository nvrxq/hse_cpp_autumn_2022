#include "TokenParser.hpp"
#include <cstdint>
#include <iostream>
#include <string>

void TokenParser::SetStartCallback(std::function<void()> f = nullptr) {
  StartCallback = f ? f : []() {};
}

void TokenParser::SetEndCallback(std::function<void()> f = nullptr) {
  EndCallback = f ? f : []() {};
}

void TokenParser::SetDigitTokenCallback(
    std::function<void(uint64_t)> f = nullptr)

{
  DigitTokenCallback = f ? f : [](uint64_t) {};
}

void TokenParser::SetStringTokenCallback(
    std::function<void(std::string &)> f = nullptr) {
  StringTokenCallback = f ? f : [](std::string &) {};
}

bool TokenParser::Delimetr(char *chr) const {
  return *chr == ' ' || *chr == '\t' || *chr == '\n';
}

bool TokenParser::IsDigit(char *chr) const {
  return *chr >= '0' && *chr <= '9';
}

void TokenParser::Parse(std::string &line) const {
  bool DigitToken = true;
  StartCallback();
  std::string token = "";
  for (size_t i = 0; i < line.size(); ++i) {
    if (!Delimetr(&line[i])) {
      token += line[i];
      std::cout << token << " " << DigitToken << std::endl;
      DigitToken = IsDigit(&line[i]);
    } else {
      if (DigitToken)
        DigitTokenCallback(std::stoull(token));
      else
        StringTokenCallback(token);
      token = "";
    }
  }
  EndCallback();
}
