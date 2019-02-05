//
// Created by alpharius on 05.02.19.
//
#include "Matrix.h"
#include <iostream>
#include "Math_external.cpp"



int main(){
    Matrix A(3,3);
    A.rff("../4x4.txt");
    A.show();

    //A.M(0,0).show();
    std::cout << det(A);

    return 0;
}