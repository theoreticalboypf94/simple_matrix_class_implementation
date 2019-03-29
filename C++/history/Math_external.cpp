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

void Normalization(Matrix::Row *row){
    double denominator = 0.;
    for(int j=0; j<row->width; j++){
        if(row->operator[](j) != 0){
            //denominator = row->operator[](j);
            denominator = (*row)[j];
            break;
        }
    }
    if (denominator == 0){
        std::cout <<"Normalization: all elements equal to zero" << std::endl;
    } else {
        *row = (*row) * (1. / denominator);
    }
}

Matrix Gauss_method(Matrix &A){         //TODO проверить по производительности выполнение метода Гаусса, с сылкой и без нее
    assert(A.height == A.width-1); //простейший метод гаусса
    for(int i=0; i<A.height; i++){
        if (i != A[i].order_not_zero_element()){
            std::cout << "faced with bad situation, need to swap rows";
            for(int ii=i; ii<A.height; ii++){
                if (A[ii].order_not_zero_element() == i){
                    Matrix::Row::swap(&A[i], &A[ii]);           //невозможна ситуалция с тотально нулевыми элементами ниже - потеря единственности решения, формируется ФСР
                }
            }
        }
        //прямой ход метода гаусса
        Normalization(&A[i]);
        for(int ii=i+1; ii<A.height; ii++){
            Normalization(&A[ii]);
            if (A[ii].order_not_zero_element() == i)
                A[ii] = A[ii] - A[i];
        }
    }

    // обратный ход метода гаусса
    for(int i=A.height-1; i>=0; i--){
        for(int ii=i-1; ii>=0; ii--){
            A[ii] = A[ii] - A[i] * A[ii][i];
        }
    }
    return A;
}



#endif MATHEXT
