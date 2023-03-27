#include <exception>
#include <iostream>
#include <string>

class BadBraceException : public std::exception {
  std::string _err;

public:
  BadBraceException(const std::string &err) : _err(err){};
  const char *what() const noexcept override { return _err.c_str(); }
};

class RangeErrorException : public std::exception {
  std::string _err;

public:
  RangeErrorException(const std::string &err) : _err(err){};
  const char *what() const noexcept override { return _err.c_str(); }
};
