#pragma once

#include <vector>
#include <cstddef>

class Matrix
{
public:
  Matrix(int rows, int cols);

  Matrix(std::vector<std::vector<int>> matrix);

  Matrix(const Matrix &matrix);

  // Compares matrices by their rows and columns and their values
  bool operator==(const Matrix &other) const;

  // Compares matrices by their rows and columns and their values
  bool operator!=(const Matrix &other) const;

  Matrix &operator=(const Matrix &other);

  // Accesses `row` index of this->data
  std::vector<int> &operator[](size_t row);

  /* Performs matrix addition
      Matrix dimensions must match */
  Matrix operator+(const Matrix &other) const;

  /* Peforms matrix subtraction.
    Matrix dimensions must match */
  Matrix operator-(const Matrix &other) const;

  /* Computes product of matrices. The first
    matrix's total columns must equal second's total rows */
  Matrix operator*(const Matrix &other) const;

  // Performs scalar multiplication
  Matrix operator*(int scalar) const;

  // Computes product of matrix and another's inverse
  Matrix operator/(const Matrix &other) const;

  // Computes scalar division
  Matrix operator/(int scalar) const;

  // Returns a matrix with `row` row and `col` col removed
  Matrix getMinor(size_t row, size_t col) const;

  // Switch rows by columns
  Matrix transpose() const;

  /*  Computes the inverse of the matrix by swapping
        rows and columns and flipping the sign of elements
        that do not belong to the same row and column.
      Returns the inverse matrix. */
  Matrix inverse() const;

  /* For simple matrices determinant is calculated
      using their respective methods. Otherwise,
      use a laplace expansion along the first row */
  int determinant() const;

  // Returns whether number of rows equals columns
  bool isSquare() const;

  // Returns the number of rows
  size_t getRows() const;

  // Returns the number of columns
  size_t getCols() const;

private:
  size_t rows;
  size_t cols;
  std::vector<std::vector<int>> data;
};

namespace utility
{
  // Calculates the number of digits in a number
  int digits(int num);

  // Prints a matrix and it's dimensions
  void print(Matrix &matrix);
}