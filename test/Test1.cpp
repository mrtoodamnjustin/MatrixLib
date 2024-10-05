#include <iostream>

#include "matrix.h"

int main(int argc, char **argv)
{
  Matrix m1(3, 3);

  m1[0] = {1, 2, 3};
  m1[1] = {4, 5, 6};
  m1[2] = {7, 8, 9};

  utility::print(m1);

  return 0;
}