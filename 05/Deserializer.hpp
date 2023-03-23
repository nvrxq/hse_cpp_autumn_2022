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
    bool is_bool = typeid(val) == typeid(bool);
    bool is_int = typeid(val) == typeid(uint64_t);
    if (!is_bool and !is_int)
      return Error::CorruptedArchive;
    std::string _text;
    in_ >> _text;
    if (_text.empty())
      return Error::CorruptedArchive;
    if (is_bool)
      val = _text == "true" ? true : false;
    else
      val = std::stoul(_text);

    return Error::NoError;
  }

public:
  explicit Deserializer(std::istream &in) : in_(in) {}

  template <class T> Error load(T &obj) { return obj.serialize(*this); }

  template <class... ArgsT> Error operator()(ArgsT &&...args) {
    return process(args...);
  }
};
