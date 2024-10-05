#include "matrix.h"

#include <stdexcept>
#include <cstddef>
#include <iomanip>
#include <iostream>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<int>(cols, 0))
{
}

Matrix::Matrix(std::vector<std::vector<int>> matrix) : rows(matrix.size()), cols(matrix.empty() ? 0 : matrix[0].size()), data(matrix)
{
}

Matrix::Matrix(const Matrix &other) : rows(other.rows), cols(other.cols), data(other.data)
{
}

bool Matrix::operator==(const Matrix &other) const
{
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols())
    return false;

  for (size_t i = 0; i < this->getRows(); i++)
  {
    for (size_t j = 0; j < this->getCols(); j++)
    {
      if (this->data[i][j] != other.data[i][j])
        return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix &other) const
{
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols())
    return true;

  for (size_t i = 0; i < this->getRows(); i++)
  {
    for (size_t j = 0; j < this->getCols(); j++)
    {
      if (this->data[i][j] != other.data[i][j])
        return true;
    }
  }
  return false;
}

Matrix &Matrix::operator=(const Matrix &other)
{
  if (this != &other)
  {
    this->rows = other.rows;
    this->cols = other.cols;
    this->data = other.data; // This now works because both are std::vector
  }
  return *this;
}

std::vector<int> &Matrix::operator[](size_t row)
{
  if (row < 0 || row >= rows)
  {
    throw std::out_of_range("Row index out of range");
  }
  return data[row];
}

Matrix Matrix::operator+(const Matrix &other) const
{
  if (this->rows != other.rows || this->cols != other.cols)
  {
    throw std::invalid_argument("Matrix dimensions must match for addition.");
  }

  Matrix result(rows, cols);

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      result[i][j] = this->data[i][j] + other.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
  if (this->rows != other.rows || this->cols != other.cols)
  {
    throw std::invalid_argument("Matrix dimensions must match for subtraction.");
  }

  Matrix result(rows, cols);

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      result[i][j] = this->data[i][j] - other.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
  if (this->cols != other.rows)
  {
    throw std::invalid_argument("First matrices total columns must match the second's rows to multiply matrices");
  }

  Matrix result(this->rows, other.cols);

  for (size_t i = 0; i < this->rows; ++i)
  {
    for (size_t j = 0; j < other.cols; ++j)
    {
      int sum = 0;
      for (size_t k = 0; k < this->cols; ++k)
      {
        sum += this->data[i][k] * other.data[k][j];
      }
      result[i][j] = sum; // set the element to the dot product of each matrices tuple
    }
  }
  return result;
}

Matrix Matrix::operator*(int scalar) const
{
  Matrix result(rows, cols);
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      result[i][j] = this->data[i][j] * scalar;
    }
  }
  return result;
}

Matrix Matrix::operator/(const Matrix &other) const
{
  /* Matrix division is defined as the first matrix
     times the inverse of the other */
  return *this * other.inverse();
}

Matrix Matrix::operator/(int scalar) const
{
  if (scalar == 0)
  {
    throw std::invalid_argument("Division by zero.");
  }

  Matrix result(rows, cols);

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      result[i][j] = this->data[i][j] / scalar;
    }
  }
  return result;
}

Matrix Matrix::getMinor(size_t row, size_t col) const
{
  Matrix minorMatrix(this->getRows() - 1, this->getCols() - 1);

  for (size_t i = 0, minor_i = 0; i < this->getRows(); ++i)
  {
    if (i == row)
      continue; // Skip the specified row

    for (size_t j = 0, minor_j = 0; j < this->getCols(); ++j)
    {
      if (j == col)
        continue; // Skip the specified column

      minorMatrix.data[minor_i][minor_j] = this->data[i][j];
      minor_j++;
    }

    minor_i++;
  }

  return minorMatrix;
}

Matrix Matrix::transpose() const
{
  // Flip the number of rows and cols in the result
  Matrix result(this->getCols(), this->getRows());

  for (size_t i = 0; i < this->getRows(); i++)
  {
    for (size_t j = 0; j < this->getCols(); j++)
    {
      // If [i][j] goes into [j][i] the elements are swapped by row and column!
      result.data[j][i] = this->data[i][j];
    }
  }

  return result;
}

Matrix Matrix::inverse() const
{
  // A matrix must be square for it to have an inverse
  if (!this->isSquare())
  {
    throw std::domain_error("The inverse is not defined for non-square matrices");
  }

  Matrix result(this->getRows(), this->getCols());

  for (size_t i = 0; i < this->getRows(); i++)
  {
    for (size_t j = 0; j < this->getCols(); j++)
    {
      result[j][i] = this->data[i][j] * (i == j ? 1 : -1);
    }
  }

  return result;
}

int Matrix::determinant() const
{
  // The determinant only exists for square matrices
  if (!this->isSquare())
  {
    throw std::domain_error("The determinant is not defined for non-square matrices");
  }

  size_t length = this->getRows();

  // 1x1: the determinant is the only element
  if (length == 1)
    return this->data[0][0];

  // 2x2: determinant is ad - bc
  // | a b |
  // | c d |
  if (length == 2)
    return this->data[0][0] * this->data[1][1] - this->data[1][0] * this->data[0][1];

  // nxn: recursive solution using Laplace expansion along the first row
  int det = 0;
  for (size_t col = 0; col < length; ++col)
  {
    // Get the minor matrix (excluding the first row and current column)
    Matrix minorMatrix = this->getMinor(0, col);

    // Alternate signs: (-1)^(row+col) * element * determinant of minor
    int sign = (col % 2 == 0) ? 1 : -1;
    det += sign * this->data[0][col] * minorMatrix.determinant();
  }

  return det;
}

bool Matrix::isSquare() const
{
  // Does the number of rows equal the number of columns?
  return this->getCols() == this->getRows();
}

size_t Matrix::getRows() const
{
  return this->rows;
}

size_t Matrix::getCols() const
{
  return this->cols;
}

namespace utility
{
  int digits(int num)
  {
    int digits = 0;

    if (num == 0)
      return digits;

    while (num % 10 != 0)
    {
      num /= 10;
      digits++;
    }

    return digits;
  }

  void print(Matrix &matrix)
  {

    int greatestNumberOfDigits = 0;

    for (size_t i = 0; i < matrix.getRows(); i++)
    {
      for (size_t j = 0; j < matrix.getCols(); j++)
      {
        int digits = utility::digits(matrix[i][j]);
        if (digits > greatestNumberOfDigits)
          greatestNumberOfDigits = digits;
      }
    }

    std::cout << "Dimensions: " << matrix.getRows() << "x" << matrix.getCols() << "\n";
    for (size_t i = 0; i < matrix.getRows(); i++)
    {
      for (size_t j = 0; j < matrix.getCols(); j++)
      {
        std::cout << std::left << std::setw(greatestNumberOfDigits * 1.3 + 3) << matrix[i][j];
      }
      std::cout << '\n';
    }
  }
}