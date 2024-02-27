#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_
#include <cmath>
#include <cstring>
#include <iostream>
#include <typeinfo>

class S21Matrix {
 public:
  void Print();
  void SetNumber(int row, int col, double value);
  S21Matrix();                        // Default constructor
  S21Matrix(int rows, int cols);      // parameterized constructor
  S21Matrix(const S21Matrix& other);  // copy costructor
  S21Matrix(S21Matrix&& other);       // move costructor
  ~S21Matrix();                       // Destructor

  int S21GetRows() noexcept;
  int S21GetCols() noexcept;
  void S21SetRows(int rows);
  void S21SetCols(int cols);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  // Overload

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& matrix, const double num);
  friend S21Matrix operator*(const double num, const S21Matrix& matrix);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int col);

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  int Find_max_in_row(int curr);
  void Swap_column(S21Matrix* temp, int index1, int index2);
  void MatrixMemoryAllocation();  // method for matrix memory allocation
  void CalcSubMatrix(int row, int col, const S21Matrix& minor);
};

#endif  // S21_MATRIX_OOP_H_