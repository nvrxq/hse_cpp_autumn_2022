#pragma once

#include <ostream>
#include <string>

class BigInt {
private:
  int32_t *digit;
  size_t size;
  bool sign;

public:
  BigInt() = default;

  BigInt(std::string &num);
  BigInt(const BigInt &other);
  BigInt(BigInt &&other);
  BigInt(int32_t *_data, size_t _len, bool _sign);
  BigInt &operator=(const BigInt &other);
  BigInt &operator=(BigInt &&other);
  BigInt operator-() const;

  friend bool operator>(const BigInt &left, const BigInt &right);
  friend bool operator<(const BigInt &left, const BigInt &right);

  friend bool operator==(const BigInt &left, const BigInt &right);
  friend bool operator!=(const BigInt &left, const BigInt &right);
  friend bool operator>=(const BigInt &left, const BigInt &right);
  friend bool operator<=(const BigInt &left, const BigInt &right);

  friend BigInt operator+(const BigInt left, const BigInt right);
  friend BigInt operator-(const BigInt left, const BigInt right);
  friend BigInt operator*(const BigInt left, const BigInt right);
  /*
  BigInt operator*(const BigInt &other) const;
  */
  ~BigInt() = default;

  friend std::ostream &operator<<(std::ostream &out, const BigInt &num);
};
