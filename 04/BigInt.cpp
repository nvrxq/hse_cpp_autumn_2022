#include "BigInt.hpp"
#include "vector.hpp"
#include <cstdint>
#include <string>

BigInt::BigInt() : size(0), sign(true) {}

BigInt::BigInt(std::string &num) {
  sign = num[0] == '-';
  size_t lenStr = num.size();
  size = lenStr - sign;
  for (size_t i = sign; i < lenStr; ++i) {
    data.push_back(num[i] - '0');
  }
}

BigInt::BigInt(Vector num) {
  size = num.len();
  data = num;
}

/*
BigInt::BigInt(Vector vec){
  data = vec;
}

BigInt &BigInt::operator=(const BigInt &bigint) {
  delete data;
  data = new Vector;
  for (size_t i = 0; i < bigint.size; ++i) {
    data->push_back(bigint.data->at(i));
  }
  return *this;
}
*/

size_t BigInt::getSize() const { return size; }

uint32_t BigInt::getData(size_t index) const { return data.at(index); }

std::ostream &operator<<(std::ostream &os, const BigInt &num) {
  for (size_t i = 0; i < num.size; ++i) {
    os << num.data.at(i);
  }
  return os;
}

/*
BigInt operator+(const BigInt &left, uint32_t value){
  std::string num = std::to_string(value);
  BigInt* obj = new BigInt(num);
  for(size_t i = left ->;)
}
*/

BigInt operator+(const BigInt &left, const BigInt &right) {
  size_t leftLen = left.size;
  size_t rightLen = right.size;
  size_t max = leftLen >= rightLen ? leftLen : rightLen;
  std::cout << max << std::endl;
  Vector res(max);
  for (size_t i = 0; i < max; ++i) {
    res[max - i - 1] =
        (leftLen - i - 1 >= 0 ? left.data.at(leftLen - i - 1) : 0) +
        (rightLen - i - 1 >= 0 ? right.data.at(rightLen - i - 1) : 0);
  }

  return BigInt(res);
}
