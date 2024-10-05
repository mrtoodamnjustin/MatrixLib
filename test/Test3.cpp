#include <iostream>

#include "matrix.h"

int main()
{
  Matrix m1({{0, 9, 8}, {7, 6, 5}});

  Matrix m2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  Matrix product = m1 * m2;

  std::cout << "Matrix One:\n";
  utility::print(m1);

  std::cout << "Matrix Two:\n";
  utility::print(m2);

  std::cout << "Matrix Product:\n";
  utility::print(product);

  if (product.isSquare())
    std::cout << "Product's determinant: " << product.determinant();
}