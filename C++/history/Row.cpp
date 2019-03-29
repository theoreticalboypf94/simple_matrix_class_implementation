//
// Created by alpharius on 05.02.19.
//
/*
 * практические замечания:
 * 1) вложенный класс стоит реализовывать в едином с внешним cpp иначе появлянтся multiply defenition error
 * 2) к 1) можно их декомпозировать как угодно, но нельзя включать один cpp в другой когда там прозодят декларации
 *
 */

#ifndef ROWCPP
#define ROWCPP

#include "Matrix.h"
// вначале реализация вложенного класса

Matrix::Row::Row (int width){                   //тупо кайф ПРОСТРАНСТВО_ИМЕН::ИМЯ_ФУНКЦИИ  пространство имен == Matrix::Row
    _column.assign(width, 0);
    this->width = width;
}

double& Matrix::Row::operator[](int index) {
    return _column[index];
}

double Matrix::Row::operator*(Matrix::Row second){
    double result =0.;
    for(int j=0; j<width; j++){
        result += this->_column[j] * second[j];
    }
    return result;
}

Matrix::Row operator*(double term, Matrix::Row row){
    Matrix::Row result(row.width);
    for(int j=0; j<row.width; j++){
        result[j] = term * row[j];
    }
    return result;
}

Matrix::Row operator*(Matrix::Row row, double term){
    return term * row;
}

Matrix::Row Matrix::Row::operator+(Matrix::Row other) {
    Matrix::Row result(this->width);
    for(int j=0; j<this->width; j++){
        result[j] = _column[j] + other[j];
    }
    return result;
}

void Matrix::Row::swap(Matrix::Row* first, Matrix::Row* second){
    Matrix::Row tmp(first->width);
    tmp = *first;
    *first = *second;
    *second = tmp;
}

Matrix::Row Matrix::Row::operator-(Matrix::Row other){
    Row result(width);
    for(int j=0; j<width; j++){
        result[j] = this->operator[](j) - other[j];
    }
    return result;
}

void Matrix::Row::show() const{
    for(int j=0; j<width; j++){
        std::cout << _column[j] << "\t" ;
    }
    std::cout << std::endl;
}

int Matrix::Row::order_not_zero_element() {
    for(int j=0; j<width; j++){
        if (_column[j] != 0.)
            return j;
    }
    return -1; // all elements is equal to zero;
}


#endif ROWCPP


