#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

class TokenParser {
private:
  std::function<void()> StartCallback;
  std::function<void()> EndCallback;
  std::function<void(uint64_t)> DigitTokenCallback;
  std::function<void(std::string &)> StringTokenCallback;

public:
  TokenParser() = default;
  void SetStartCallback(std::function<void()> f);
  void SetEndCallback(std::function<void()> f);

  void SetDigitTokenCallback(std::function<void(uint64_t)> f);
  void SetStringTokenCallback(std::function<void(std::string &)> f);

  void Parse(std::string &line) const;
  bool Delimetr(char *c) const;
  bool IsDigit(char *chr) const;
};
