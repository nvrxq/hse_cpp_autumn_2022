#include "BigInt.hpp"
#include <cctype>
#include <cmath>
#include <cstring>
#include <endian.h>
#include <ios>
#include <iostream>
#include <stdexcept>

BigInt::BigInt(const BigInt &other) {
  size = other.size;
  digit = new int32_t[size]();
  sign = other.sign;
  for (size_t i = 0; i < size; ++i) {
    digit[i] = other.digit[i];
  }
}

BigInt::BigInt(std::string &num) {
  sign = num[0] == '-';
  size = num.size() - sign;
  digit = new int32_t[size];
  for (size_t i = sign; i < size; ++i) {
    if (std::isdigit(num[i]))
      digit[i] = num[size - i - 1 + sign] - '0';
    else {
      throw std::invalid_argument("Must be digit");
    }
  }
}

std::ostream &operator<<(std::ostream &out, const BigInt &num) {
  if (num.sign)
    out << "-";
  for (int32_t i = num.size - 1; i >= 0; --i)
    out << num.digit[i];

  return out;
}

BigInt::BigInt(BigInt &&other) {
  size = other.size;
  sign = other.sign;
  digit = other.digit;
  other.digit = nullptr;
  other.size = 0;
}

BigInt::BigInt(int32_t *_data, size_t _size, bool _sign)
    : size(_size), sign(_sign) {
  digit = new int32_t[_size]();
  for (size_t i = 0; i < _size; ++i) {
    digit[i] = _data[i];
  }
}

BigInt &BigInt::operator=(const BigInt &other) {
  if (this == &other)
    return *this;
  size = other.size;
  sign = other.sign;
  int32_t *tmp = new int32_t[size]();
  if (digit)
    delete[] digit;
  digit = tmp;
  tmp = nullptr;
  for (size_t i = 0; i < size; ++i) {
    digit[i] = other.digit[i];
  }

  return *this;
}

BigInt &BigInt::operator=(BigInt &&other) {
  if (this == &other)
    return *this;
  size = other.size;
  sign = other.sign;
  delete[] digit;
  digit = other.digit;
  other.digit = nullptr;
  other.size = 0;
  return *this;
}

BigInt BigInt::operator-() const {
  BigInt a(this->digit, this->size, this->sign ^ 1);
  return a;
}

bool operator==(const BigInt &left, const BigInt &right) {
  if ((left.sign != right.sign) || left.size != right.size) {
    return false;
  } else {
    int32_t len = left.size - 1;
    while (left.digit[len] == right.digit[len]) {
      len--;
      if (!len)
        break;
    }
    return !len;
  }
}

bool operator>(const BigInt &left, const BigInt &right) {
  if (left == right)
    return false;
  if ((!left.sign and right.sign) or
      ((left.size > right.size) and !left.sign) or
      ((left.size < right.size) and left.sign)) {
    return true;
  } else if (left.size == right.size) {
    for (size_t i = left.size - 1; i >= 0; --i) {
      if (left.digit[i] != right.digit[i]) {
        if ((left.digit[i] > right.digit[i] and !left.sign) or
            (left.digit[i] < right.digit[i] and left.sign))
          return true;
      }
    }
    return false;
  } else
    return false;
}

bool operator<(const BigInt &left, const BigInt &right) {
  if (left == right)
    return false;
  else
    return !(left > right);
}

BigInt operator+(const BigInt left, const BigInt right) {
  if (left.sign != right.sign) {
    if (left.sign) {
      return right - (-left);
    } else {
      return left - (-right);
    }
  }

  bool dopValue = 0;
  int32_t *a = left.digit, *b = right.digit;
  size_t n = left.size, m = right.size;
  size_t max = n > m ? n : m;
  ++max;
  int32_t *res = new int32_t[max]();
  bool neg = left.sign && right.sign;

  for (size_t i = 0; i < max || dopValue; ++i) {
    res[i] = (i < n ? a[i] : 0) + (i < m ? b[i] : 0) + dopValue;
    dopValue = res[i] >= 10;
    if (dopValue)
      res[i] -= 10;
  }
  if (res[max - 1] == 0)
    --max;
  BigInt ans(res, max, neg);
  delete[] res;
  return ans;
}

BigInt operator-(const BigInt left, const BigInt right) {
  if (left.sign && right.sign)
    return -((-left) - (-right));
  if (left.sign && !right.sign)
    return -((-left) + right);
  if (!left.sign && right.sign)
    return left + (-right);

  bool dopValue = 0;
  size_t n = left.size, m = right.size;
  if (left > right) {
    int32_t *res = new int32_t[n]();
    for (size_t i = 0; i < n; ++i)
      res[i] = left.digit[i];

    for (size_t i = 0; i < m || dopValue; ++i) {
      res[i] -= dopValue + (i < m ? right.digit[i] : 0);
      dopValue = res[i] < 0;
      if (dopValue)
        res[i] += 10;
    }
    while (n > 0 && res[n - 1] == 0)
      --n;
    BigInt ans(res, n, 0);
    delete[] res;
    return ans;
  } else {
    int32_t *res = new int32_t[m]();
    for (size_t i = 0; i < m; ++i)
      res[i] = right.digit[i];

    for (size_t i = 0; i < n || dopValue; ++i) {
      res[i] -= dopValue + (i < n ? left.digit[i] : 0);
      dopValue = res[i] < 0;
      if (dopValue)
        res[i] += 10;
    }
    while (m > 0 && res[m - 1] == 0)
      --m;
    BigInt ans(res, m, 1);
    delete[] res;
    return ans;
  }
}

BigInt operator*(const BigInt left, const BigInt right) {
  int *result = new int[left.size + right.size]();
  for (int i = right.size - 1; i >= 0; i--) {
    int carry = 0;
    for (int j = left.size - 1; j >= 0; j--) {
      int product = (right.digit[i] - '0') * (left.digit[j] - '0') + carry +
                    result[i + j + 1];
      result[i + j + 1] = product % 10;
      carry = product / 10;
    }
    result[i] += carry;
  }
  int startIndex = 0;
  while (startIndex < left.size + right.size && result[startIndex] == 0) {
    startIndex++;
  }
  if (startIndex == left.size + right.size) { // если результат равен нулю
    char *res = new char[2];
    res[0] = '0';
    res[1] = '\0';
    std::string digit;
    digit.assign(res);
    return BigInt(digit);
  } else {
    char *res = new char[left.size + right.size - startIndex + 1];
    int j = 0;
    for (int i = startIndex; i < left.size + right.size; i++) {
      res[j++] = result[i] + '0';
    }
    res[j] = '\0';

    std::string digit;
    digit.assign(res);
    std::cout << "PRODUCT: " << digit << std::endl;
    return BigInt(digit);
  }
}
