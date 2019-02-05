//
// Created by alpharius on 05.02.19.
//

#ifndef C_MATRIX_H
#define C_MATRIX_H
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class Matrix {
public:
    class Row{
    public:
        int width;

        Row(int);
        double operator*(Row);
        friend Matrix::Row operator*(double term, Matrix::Row row);
        friend Matrix::Row operator*(Matrix::Row row,double term);
        double& operator[](int);
        Row operator+(Row);
        void swap(Row*, Row*);
        void show() const;
        int order_not_zero_element();
    private:
        std::vector<double> _column;
    };

    int height, width;
    Matrix(int, int);
    void rff(const std::string& path);
    void show() const;
    Matrix::Row& operator[] (int);
    Matrix M(int, int); // Matrix Minor
    Matrix T();                         //this transform can change shepe



private:
    std::vector<Row> _row;
};

#endif //C_MATRIX_H

//
////это  просто полигон того как проходит наследование классов и конструкторов - практической ценности не имеет
//class Row2 : public Row{
//public:
//    std::string g = "glory to respublic";
//    Row2(int a) : Row( a) {};
//};
