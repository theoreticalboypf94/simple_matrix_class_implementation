//
// Created by alpharius on 05.02.19.
//
#include "Matrix.h"
#include <iostream>
//#include "Math_external.cpp"

// остановился на методе гауса и функции order_not_zero_element
// которая будет считать позиции до первого не нулевого элемента


int main(){
    Matrix A(3,3), B(3,3);
    A.rff("../4x4.txt");
    B.rff("../4x4.txt");
    A.show();
    B.show();
    A = A^-1;
    //A.show();

    return 0;
}