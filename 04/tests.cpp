#include "BigInt.hpp"
#include "vector.hpp"
#include <cstdint>

int main() {
  std::string num = "24";
  std::string num2 = "2";
  BigInt int1 = BigInt(num);
  BigInt int2 = BigInt(num);
  std::cout << int1 + int2 << std::endl;
}
