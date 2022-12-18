#include "Matrix.hpp"
#include <cstddef>
#include <stdexcept>

Matrix::ProxyRow::ProxyRow(size_t _columns) {
  data_ = new int32_t[_columns];
  sizeColumns = _columns;
}

Matrix::Matrix(size_t _row, size_t _columns)
    : RowSize(_row), ColumnSize(_columns) {
  rows = new ProxyRow[_row];
  for (size_t i = 0; i < _row; ++i)
    rows[i].SetData(_columns);
}

int32_t &Matrix::ProxyRow::operator[](size_t _columns) {
  if (_columns >= sizeColumns)
    throw std::out_of_range("Range Error");
  return data_[_columns];
}

Matrix::ProxyRow &Matrix::operator[](size_t _row) {
  if (_row >= RowSize)
    throw std::out_of_range("Range Error");
  return rows[_row];
}

Matrix::ProxyRow::~ProxyRow() { delete[] data_; }

std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
  for (size_t i = 0; i < mat.getRow(); ++i) {
    os << "\n";
    for (size_t j = 0; j < mat.getColumn(); ++j) {
      os << mat.rows[i][j] << " ";
    }
  }
  return os;
}

void Matrix::operator*=(int32_t scalar) {
  for (size_t i = 0; i < RowSize; ++i) {
    for (size_t j = 0; j < ColumnSize; ++j)
      rows[i][j] *= scalar;
  }
}

bool Matrix::operator==(Matrix &mat) const {
  bool flag = true;
  if (RowSize != mat.RowSize || ColumnSize != mat.ColumnSize)
    return false;
  for (size_t i = 0; i < RowSize; ++i) {
    for (size_t j = 0; j < ColumnSize; ++j) {
      flag = (rows[i][j] == mat[i][j]);
      if (!flag)
        return flag;
    }
  }
  return flag;
}

bool Matrix::operator!=(Matrix &mat) const { return !(*this == mat); }

Matrix Matrix::operator+(Matrix &mat) {
  if (RowSize != mat.RowSize || ColumnSize != mat.ColumnSize)
    throw std::out_of_range("Not same shape");
  Matrix SumMat(RowSize, ColumnSize);
  for (size_t i = 0; i < RowSize; ++i) {
    for (size_t j = 0; j < ColumnSize; ++j)
      SumMat[i][j] = rows[i][j] + mat[i][j];
  }
  return SumMat;
}

void Matrix::ProxyRow::SetData(size_t _columns) {
  data_ = new int32_t[_columns];
  sizeColumns = _columns;
};

size_t Matrix::getColumn() const { return RowSize; }

size_t Matrix::getRow() const { return ColumnSize; }
