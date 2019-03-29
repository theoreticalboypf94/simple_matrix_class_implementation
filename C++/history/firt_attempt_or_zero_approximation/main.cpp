#include <iostream>
#include "Matrix.h"
#include <vector>
#define def_print(a) std::cout << a << std::endl;
#include <bitset>

int main() {
    // presintation of Gauss method
    Matrix m(3,4);
    m.rff("../minor_matrix_test.txt");
    m.print();
    m.Gauss_method();
    // presentation of matrix multiplication
    Matrix A(2,2), B(2,3);
    A.rff("../matrix1.txt");
    B.rff("../matrix2.txt");
    A.print();
    B.print();
    (A*B).print();
    m.print();
    return 0;
}

