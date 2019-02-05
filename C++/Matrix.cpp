//
// Created by alpharius on 05.02.19.
//

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

