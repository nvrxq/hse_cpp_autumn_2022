#pragma once
#include "vector.hpp"
#include <iostream>
#include <ostream>
#include <sys/types.h>
class BigInt {
private:
  Vector data;
  size_t size;
  bool sign;

public:
  BigInt();
  BigInt(std::string &num);
  BigInt(Vector vec);
  BigInt(BigInt &&bigint); // Перемещение
  size_t getSize() const;
  uint32_t getData(size_t index) const;
  friend std::ostream &operator<<(std::ostream &os, const BigInt &bigint);
  BigInt &operator=(BigInt &&bigint);
  friend BigInt operator+(const BigInt &left, const BigInt &right);
};
