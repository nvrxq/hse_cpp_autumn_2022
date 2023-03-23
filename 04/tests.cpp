#include "BigInt.hpp"

#include <iostream>

int main() {
  std::string num = "99";
  std::string num2 = "-99";
  BigInt int1 = BigInt(num);
  BigInt int2 = BigInt(num2);
  BigInt int3 = -int2;
  std::cout << int1 + int3 << std::endl;

  // std::cout << int3 << std::endl;
  // std::cout << int1 + int3;
  return 0;
}
