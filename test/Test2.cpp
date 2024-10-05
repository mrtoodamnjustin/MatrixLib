#include <iostream>
#include <string>

#include "matrix.h"

using std::stoi;

int main(int argc, char **argv)
{
  if (argc != 10)
  {
    std::cout << "Usage: test.exe <element_1> <element_2> ... <elemenet_9>";
    return 1;
  }

  Matrix m1({{stoi(argv[1]), stoi(argv[2]), stoi(argv[3])},
             {stoi(argv[4]), stoi(argv[5]), stoi(argv[6])},
             {stoi(argv[7]), stoi(argv[8]), stoi(argv[9])}});

  utility::print(m1);

  std::cout << "Determinant: " << m1.determinant();
}