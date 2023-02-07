#pragma once
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sys/types.h>

class Vector {
private:
  size_t size;
  uint32_t *data;
  size_t capacity;

public:
  Vector();
  Vector(size_t len);
  void operator=(uint32_t x);
  ~Vector();
  uint32_t *begin() const;
  uint32_t *end() const;
  size_t len() const;
  void push_back(uint32_t x);
  uint32_t at(size_t index) const;
  void reserve(size_t _size);
  uint32_t &operator[](size_t index);
};
