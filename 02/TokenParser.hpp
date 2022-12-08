#pragma once
#include <algorithm>
#include <functional>
#include <cstdint>
#include <string>

class TokenParser {
private:
  std::function<void()> StartCallback;
  std::function<void()> EndCallback;
  std::function<void(uint64_t)> DigitTokenCallback;
  std::function<void(std::string &)> StringTokenCallback;

public:
  TokenParser() = default;
  void SetStartCallback(std::function<void()> f = nullptr);
  void SetEndCallback(std::function<void()> f = nullptr);

  void SetDigitTokenCallback(std::function<void(uint64_t)> f = nullptr);
  void SetStringTokenCallback(std::function<void(std::string &)> f = nullptr);

  void Parse(const std::string &line) const;
  bool Delimetr(char c) const;
  bool IsDigit(char c) const;
};
