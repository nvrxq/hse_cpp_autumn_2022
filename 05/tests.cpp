#include "Deserializer.hpp"
#include "Serializer.hpp"
#include "error.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <sys/types.h>
class Tests : public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}
};

struct Data {
  uint64_t a;
  bool b;
  uint64_t c;

  template <class Serializer> Error serialize(Serializer &serializer) {
    return serializer(a, b, c);
  }
};

struct BadData {
  uint64_t a;
  bool b;
  char c;
  template <class Serializer> Error serialize(Serializer &serializer) {
    return serializer(a, b, c);
  }
};

struct BoolData {
  bool a;
  template <class Serializer> Error serialize(Serializer &serializer) {
    return serializer(a);
  }
};
struct UintData {
  uint64_t a;
  template <class Serializer> Error serialize(Serializer &serializer) {
    return serializer(a);
  }
}; // 2) +тест структур с единственным полем каждого типа
struct BadDataS {
  std::string b;
  template <class Serializer> Error serialize(Serializer &serializer) {
    return serializer(b);
  }
};

TEST(std_test, ser) {
  Data x{3, true, 2};
  std::stringstream _stream;
  Serializer serializer(_stream);
  Error _err = serializer.save(x);
  Data y{0, false, 0};
  Deserializer deserializer(_stream);
  Error err = deserializer.load(y);
  // No error
  ASSERT_EQ(err, Error::NoError);
  ASSERT_EQ(_err, Error::NoError);
  ASSERT_EQ(x.a, y.a);
  ASSERT_EQ(x.b, y.b);
  ASSERT_EQ(x.c, y.c);
}
// Невалидные данные
TEST(invalid_test, ser) {
  BadData x{3, true, '2'};
  BadData y{0, true, 'a'};
  std::stringstream _stream;
  Serializer serializer(_stream);
  Error err = serializer.save(x);
  Deserializer deserializer(_stream);
  Error _err = deserializer.load(y);
  ASSERT_EQ(err, Error::CorruptedArchive); // проверки ошибки CorruptedArchive
  ASSERT_EQ(_err, Error::CorruptedArchive);
}

// Только bool
TEST(only_bool, ser) {
  BoolData x{true};
  std::stringstream _stream;
  Serializer serializer(_stream);
  Error err = serializer.save(x);
  ASSERT_EQ(_stream.str(),
            "true "); // тесты save должны проверять что фактически было
                      // записано в поток вывода (добавлено)
  BoolData y{false};
  Deserializer deserializer(_stream);
  Error _err = deserializer.load(y);
  // TESTS
  ASSERT_TRUE(err == Error::NoError); // метод save(добавлено)
  ASSERT_TRUE(_err == Error::NoError);
  ASSERT_EQ(x.a, y.a);
}
// Только int (добавлено)
TEST(only_int, ser) {
  UintData x{24};
  std::stringstream _stream;
  Serializer serializer(_stream);
  Error err = serializer.save(x);
  ASSERT_EQ(_stream.str(), "24 "); // тесты save должны проверять что фактиески
                                   // было записано в поток вывода (добавлено)
  UintData y{0};
  Deserializer deserializer(_stream);
  Error _err = deserializer.load(y);

  ASSERT_EQ(x.a, y.a); // Правильность работы объектов
  ASSERT_EQ(err, Error::NoError);
  ASSERT_EQ(_err, Error::NoError); // Работа с bool
}

// Проверка невалидных данных на  десериализации
TEST(test_des, ser) {
  std::string badstring{"false1"};
  std::stringstream _stream;
  _stream << badstring;
  BoolData x{true};
  Deserializer deserializer(_stream);
  Error err = deserializer.load(x);
  ASSERT_EQ(err, Error::CorruptedArchive);
}

// Проверка валидных данных на десериализации
TEST(test_des_valid, ser) {
  std::string goodstring{"24"};
  std::stringstream _stream;
  _stream << goodstring;
  UintData x{0};
  Deserializer deserializer(_stream);
  Error err = deserializer.load(x);
  ASSERT_EQ(x.a, 24);
  ASSERT_EQ(err, Error::NoError);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
