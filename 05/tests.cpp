#include "Deserializer.hpp"
#include "Serializer.hpp"
#include "error.hpp"
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
  bool b;
  template <class Serializer> Error serialize(Serializer &serializer) {
    return serializer(a, b);
  }
};

TEST(std_test, ser) {
  Data x{3, true, 2};
  std::stringstream _stream;
  Serializer serializer(_stream);
  serializer.save(x);
  Data y{0, false, 0};
  Deserializer deserializer(_stream);
  Error err = deserializer.load(y);
  // No error
  ASSERT_EQ(err, Error::NoError);
  ASSERT_EQ(x.a, y.a);
  ASSERT_EQ(x.b, y.b);
  ASSERT_EQ(x.c, y.c);
}

TEST(invalid_test, ser) {
  BadData x{3, true, '2'};
  std::stringstream _stream;
  Serializer serializer(_stream);
  Error err = serializer.save(x);
  ASSERT_EQ(err, Error::CorruptedArchive);
}

TEST(only_bool, ser) {
  BoolData x{true, true};
  std::stringstream _stream;
  Serializer serializer(_stream);
  Error err = serializer.save(x);
  ASSERT_TRUE(err == Error::NoError);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
