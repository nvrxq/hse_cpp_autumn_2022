#pragma once
#include "error.hpp"
#include <iostream>
#include <string>
#include <typeinfo>

class Deserializer {

private:
  static constexpr char Separator = ' ';
  std::istream &in_;

  template <class T, class... ArgsT> Error process(T &val, ArgsT &&...args) {
    Error err = process(val);
    if (err != Error::NoError)
      return err;
    return process(std::forward<ArgsT>(args)...);
  }

  template <class T> Error process(T &val) {
    std::string _text;
    in_ >> _text;
    if (_text.empty())
      return Error::CorruptedArchive;
    bool is_number = true;
    for (char c : _text) {
      if (!std::isdigit(c)) {
        is_number = false;
        break;
      }
    }
    if (is_number)
      val = std::stoul(_text);
    else {
      if (_text == "true" or _text == "false") {
        val = _text == "true";
      } else {
        return Error::CorruptedArchive;
      }
    }
    return Error::NoError;
  }

public:
  explicit Deserializer(std::istream &in) : in_(in) {}

  template <class T> Error load(T &obj) { return obj.serialize(*this); }

  template <class... ArgsT> Error operator()(ArgsT &&...args) {
    return process(args...);
  }
};
