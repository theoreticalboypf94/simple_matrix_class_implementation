#include <iostream>
#include "Matrix.h"
#include <vector>
#define def_print(a) std::cout << a << std::endl;
#include <bitset>

int main() {
    Matrix m(3,4);
    m.rff("../minor_matrix_test.txt");
    return 0;
}

