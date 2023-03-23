#pragma once
#include "error.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include <typeinfo>

class Serializer {
  static constexpr char Separator = ' ';
  std::ostream &out_;

public:
  explicit Serializer(std::ostream &out) : out_(out) {}

  template <class T> Error save(T &object) { return object.serialize(*this); }

  template <class... ArgsT> Error operator()(ArgsT... args) {
    return process(args...);
  }

  template <class T, class... ArgsT> Error process(T val, ArgsT &&...args) {
    Error err = process(val);
    if (err != Error::NoError) {
      return err;
    }
    return process(std::forward<ArgsT>(args)...);
  }

  template <class T> Error process(T val) {
    bool is_bool = typeid(val) == typeid(bool);
    bool is_int = typeid(val) == typeid(uint64_t);
    if (!is_bool and !is_int)
      return Error::CorruptedArchive;
    if (is_bool) {
      std::string _val = val == 1 ? "true" : "false";
      out_ << _val << Separator;
    } else
      out_ << val << Separator;
    return Error::NoError;
  }

private:
  // process использует variadic templates
};
