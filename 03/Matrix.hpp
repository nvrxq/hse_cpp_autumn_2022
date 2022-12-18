#pragma once
#include <iostream>
#include <ostream>

class Matrix {

  class ProxyRow {
  public:
    ProxyRow() = default;
    ~ProxyRow();
    void SetData(size_t columns);
    int32_t &operator[](size_t _columns);
    void SetRow(size_t _columns);
    size_t GetRow() const;

  private:
    int32_t *data_;
    size_t sizeColumns;
  };

public:
  Matrix() = default;
  Matrix(size_t row, size_t column);
  ~Matrix() = default;
  size_t getRow() const;
  size_t getColumn() const;

  ProxyRow &operator[](size_t _row);
  void operator*=(int32_t scalar);
  bool operator==(Matrix &mat) const;
  bool operator!=(Matrix &mat) const;
  Matrix operator+(Matrix &mat);
  friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);

private:
  ProxyRow *rows;
  size_t RowSize, ColumnSize;
};
