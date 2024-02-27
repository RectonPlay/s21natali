#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) { MatrixMemoryAllocation(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  MatrixMemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MatrixMemoryAllocation();
  for (int i = 0; i < rows_; i++) {
    memcpy(this->matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  }
};

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

void S21Matrix::MatrixMemoryAllocation() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Invalid matrix size");
  }
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
};

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
};

void S21Matrix::SetNumber(int row, int col, double value) {
  this->matrix_[row][col] = value;
}

int S21Matrix::S21GetRows() noexcept { return rows_; };

int S21Matrix::S21GetCols() noexcept { return cols_; };

void S21Matrix::S21SetRows(int rows) {
  if (rows == this->rows_) {
  } else {
    S21Matrix res(rows, this->cols_);
    int tmp = rows < this->rows_ ? rows : this->rows_;

    for (int i = 0; i < tmp; i++) {
      memcpy(res.matrix_[i], this->matrix_[i], this->cols_ * sizeof(double));
    }
    *this = res;
  }
}

void S21Matrix::S21SetCols(int cols) {
  if (cols == this->cols_) {
  } else {
    S21Matrix res(this->rows_, cols);
    int tmp = cols < this->cols_ ? cols : this->cols_;

    for (int i = 0; i < this->rows_; i++) {
      memcpy(res.matrix_[i], this->matrix_[i], tmp * sizeof(double));
    }
    *this = res;
  }
}

void S21Matrix::Print() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << this->matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
};

int S21Matrix::Find_max_in_row(int curr) {
  int ret = curr;
  for (int i = curr; i < cols_; i++) {
    if (fabs(matrix_[curr][i]) > fabs(matrix_[curr][ret])) {
      ret = i;
    }
  }
  return ret;
}

void S21Matrix::Swap_column(S21Matrix *tempm, int index1, int index2) {
  for (int i = 0; i < tempm->rows_; i++) {
    double temp = tempm->matrix_[i][index1];
    tempm->matrix_[i][index1] = tempm->matrix_[i][index2];
    matrix_[i][index2] = temp;
  }
}
