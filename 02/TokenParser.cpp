#include "TokenParser.hpp"


void TokenParser::SetStartCallback(std::function<void()> f) {
  StartCallback = f ? f : []() {};
}

void TokenParser::SetEndCallback(std::function<void()> f) {
  EndCallback = f ? f : []() {};
}

void TokenParser::SetDigitTokenCallback(std::function<void(uint64_t)> f)

{
  DigitTokenCallback = f ? f : [](uint64_t) {};
}

void TokenParser::SetStringTokenCallback(std::function<void(std::string &)> f) {
  StringTokenCallback = f ? f : [](std::string &) {};
}

bool TokenParser::Delimetr(char c) const {
  return c == ' ' || c == '\t' || c == '\n';
}

bool TokenParser::IsDigit(char c) const { return c >= '0' && c <= '9'; }

void TokenParser::Parse(const std::string &line) const {
  size_t DigitToken = 0;
  const size_t n = line.size();
  uint64_t digit;
  bool CheckDelim;
  const uint64_t maximum = 0xFFFFFFFFFFFFFFFF;
  StartCallback();
  std::string token = "";
  for (size_t i = 0; i < n; ++i) {
    CheckDelim = Delimetr(line[i]);
    if (!CheckDelim) {
      token += line[i];
      DigitToken += IsDigit(line[i]);
    }
    if (CheckDelim || (token != "" && i == n - 1)) {
      if (DigitToken == token.size() &&
          ((digit = std::stoull(token)) < maximum / 10))
        DigitTokenCallback(digit);
      else
        StringTokenCallback(token);
      token = "";
      DigitToken = 0;
    }
  }
  EndCallback();
}
