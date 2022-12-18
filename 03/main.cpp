#include "Matrix.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(test_matrix, Matrix) {
  // Test INIT and Operators: {"==", "*=", "+", "!="}
  {
    Matrix Mat(5, 5);

    Matrix Mat2(5, 5);
    for (size_t i = 0; i < 5; ++i) {
      for (size_t j = 0; j < 5; ++j) {
        Mat[i][j] = (i + 1) * 2;
        Mat2[i][j] = (i + 1) * 2;
      }
    }
    ASSERT_TRUE(Mat == Mat2);
    ASSERT_EQ(Mat.getColumn(), Mat2.getColumn());
    ASSERT_EQ(Mat.getRow(), Mat2.getRow());

    // Test Operator "*=" and "!="
    Mat *= 2;
    ASSERT_FALSE(Mat == Mat2);

    Matrix Mat3(2, 2);
    Matrix sumMat = Mat + Mat2;
    ASSERT_EQ(sumMat[2][2], Mat[2][2] + Mat2[2][2]);
    ASSERT_TRUE(sumMat != Mat);
    ASSERT_TRUE(sumMat != Mat3);
  }

  // Test throw
  {
    Matrix Mat1(2, 2);
    try {
      Mat1[5][5] = 25;
    } catch (std::out_of_range const &err) {
      EXPECT_EQ(err.what(), std::string("Range Error"));
    }
  }

  // Test Cout
  {
    Matrix Mat(3, 3);
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        Mat[i][j] = i + j;
      }
    }

    std::cout << Mat << std::endl;
  }
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
