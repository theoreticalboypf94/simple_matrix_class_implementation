//
// Created by alpharius on 05.02.19.
//

#ifndef MATHEXT
#define MATHEXT

#include <assert.h>
#include "Matrix.h"

double det2to2(Matrix A){
    return A[0][0] * A[1][1] - A[1][0] * A[0][1];
}

double det(Matrix A){
    assert(A.width == A.height);
    auto F = [](int i){return (i%2==0)? 1 : -1;};
    double result=0.;

    if (A.width == 2){
        return det2to2(A);
    } else {
        for (int i = 0; i < A.width; i++) {
            result += F(i) * A[0][i] * det(A.M(0, i));
        }
    }
    return result;
}

Matrix Gauss_method(Matrix A){

}



#endif MATHEXT
