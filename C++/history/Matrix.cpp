//
// Created by alpharius on 05.02.19.
//

#ifndef MATRIXCPP
#define MATRIXCPP

#include "Matrix.h"



Matrix::Matrix(int _height, int _width) {
    height = _height;
    width = _width;
    _row.assign(height,Row(width));
}

void Matrix::rff(const std::string& path){
    std::fstream file;
    file.open(path);
    if(file.is_open()){
        std::string loop;
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                file >> loop;
                _row[i][j] = std::stod(loop);
            }
        }
    } else {
        std::cout << "ERROR can't open file";
    }
}

void Matrix::show() const {
    for(int i=0; i<height; i++){
        _row[i].show();
    }
    std::cout << std::endl;
}

Matrix::Row& Matrix::operator[](int i) {
    return _row[i];
}

Matrix Matrix::M(int I, int J){
    Matrix result(width-1, height-1);
    int index1, index2;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            index1 = (i < I)? i : i-1;
            index2 = (j < J)? j : j-1;

            if (i!=I && j!=J){
                result[index1][index2] = _row[i][j];
            }
        }
    }
    return result;
}

Matrix Matrix::T(){
    Matrix result(width, height);
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            result[j][i] = _row[i][j];
        }
    }
    return result;
}

Matrix operator*(Matrix A, float term){
    for(int i=0; i<A.width; i++){
        for(int j=0; j<A.height; j++){
            A[i][j] = A[i][j] * term;
        }
    }
    return A;
}

Matrix&  Matrix::operator^(int power) {
    Matrix result(height, width);
    std::cout << "HERE";
    if(power == -1){
        std::cout << "calculate reverse matrix";
        double reverse_det = 1./det(*this);
        auto F = [](int i) {return (i%2 == 0)? 1 : -1;};
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                result[i][j] = F(i+j) * det(this->M(i,j));
            }
        }

        result = result * reverse_det;
        result = result.T();
    }
    return result;
}

#endif

