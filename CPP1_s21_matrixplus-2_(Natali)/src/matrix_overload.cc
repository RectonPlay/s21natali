#include "s21_matrix_oop.h"

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    this->~S21Matrix();
    new (this) S21Matrix(other);
  }
  return (*this);
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    this->~S21Matrix();
    new (this) S21Matrix(std::move(other));
  }
  return (*this);
}

S21Matrix operator*(const S21Matrix &matrix, const double num) {
  S21Matrix res(matrix);

  res.MulNumber(num);
  return (res);
}

S21Matrix operator*(const double num, const S21Matrix &matrix) {
  S21Matrix res(matrix);

  res.MulNumber(num);
  return (res);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);

  res.SumMatrix(other);
  return (res);
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);

  res.SubMatrix(other);
  return (res);
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);

  res.MulMatrix(other);
  return (res);
}

bool S21Matrix::operator==(const S21Matrix &other) {
  S21Matrix matrix(*this);

  bool res = matrix.EqMatrix(other);
  return (res);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);

  return (*this);
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);

  return (*this);
}

S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);

  return (*this);
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);

  return (*this);
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Bad indices");
  }

  return (matrix_[row][col]);
}