#include "vector.hpp"
#include <algorithm>
#include <cstdint>
#include <sys/types.h>

Vector::Vector() : size(), data(nullptr), capacity() {}

Vector::Vector(size_t _n) {
  size = _n;
  capacity = _n;
  data = new uint32_t[capacity]();
}

Vector::~Vector() { delete[] data; }
uint32_t *Vector::begin() const { return data; }

uint32_t *Vector::end() const { return data + size; }

size_t Vector::len() const { return size; }

void Vector::push_back(uint32_t x) {
  if (size == capacity) {
    capacity = capacity ? capacity * 2 : 1;
    uint32_t *temp = new uint32_t[capacity]();
    std::copy(data, data + size, temp);
    delete[] data;
    data = temp;
  }
  data[size++] = x;
}

uint32_t &Vector::operator[](size_t index) { return data[index]; }

uint32_t Vector::at(size_t index) const { return data[index]; }
