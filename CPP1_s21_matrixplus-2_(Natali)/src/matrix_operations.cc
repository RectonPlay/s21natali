#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return (false);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) return (false);
    }
  }
  return (true);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Different matrix dimensions");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Matrix dimensions are not compatible for multiplication");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < res.rows_; i++)
    for (int j = 0; j < res.cols_; j++) res.matrix_[i][j] = matrix_[j][i];
  return (res);
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Matrix dimensions are not compatible for determinant");
  }

  S21Matrix res(rows_, cols_);
  if (rows_ == 1)
    res.matrix_[0][0] = matrix_[0][0];
  else {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        minor.CalcSubMatrix(i, j, *this);
        res.matrix_[i][j] = minor.Determinant() * pow(-1, i + j);
      }
    }
  }
  return (res);
}

void S21Matrix::CalcSubMatrix(int row, int col, const S21Matrix &minor) {
  for (int min_x = 0, i = 0; i < minor.rows_; i++) {
    if (i == row) continue;
    for (int min_y = 0, j = 0; j < minor.cols_; j++) {
      if (j == col) continue;
      matrix_[min_x][min_y] = minor.matrix_[i][j];
      min_y++;
    }
    min_x++;
  }
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Matrix dimensions are not compatible for determinant");
  }
  S21Matrix tmp = *this;

  double det = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = i + 1; j < rows_; j++) {
      if (tmp.matrix_[i][i] == 0) {
        bool found = false;
        for (int k = i + 1; k < rows_; k++) {
          if (tmp.matrix_[k][i] != 0) {
            found = true;
            double *tmp_row = tmp.matrix_[i];
            tmp.matrix_[i] = tmp.matrix_[k];
            tmp.matrix_[k] = tmp_row;
            det *= -1;
            break;
          }
        }
        if (!found) {
          det = 0;
          i = j = rows_;
          break;
        }
      }
      double factor = tmp.matrix_[j][i] / tmp.matrix_[i][i];
      for (int k = i; k < rows_; k++) {
        tmp.matrix_[j][k] -= factor * tmp.matrix_[i][k];
      }
    }
    if (det == 0) {
      break;
    }
    det *= tmp.matrix_[i][i];
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  int det = Determinant();
  if (det == 0) {
    throw std::invalid_argument("Determinant == 0");
  }
  S21Matrix result = CalcComplements().Transpose();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] /= det;
    }
  }
  return result;
}
