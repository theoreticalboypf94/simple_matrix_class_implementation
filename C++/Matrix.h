/*
 *  Написано "Во славу Себе и на благо Отечества" (Макиавелли)
 *
 *
 *  Какую матрицу мы хотим:
 *  Конструкторы - разнообразные допускающие различное формирование
 *  Matrix(height, width, MOD : enumerate, )
 *
 *  не плохо бы еще визуализацию сделать
 *
 */

#ifndef C_MATRIX_H
#define C_MATRIX_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <fstream>


enum MOD {
    RND,
    ZEROS,
    ONES,
    TRIANGLE_TOP,
    DIAG
};

class Matrix {
public:

    class Row{
    public:
        std::vector<double> row;
        Row(size_t len){ row.resize(len);};
        double& operator[](int j) {return (j>=0)? row.at(j) : row.at(row.size() - j - 1);} // чтобы было как в питоне
    };

    size_t height, width;
    /* конструкторы и деструктор*/
    Matrix();
    Matrix(size_t h, size_t w, MOD mod);  // задаем размер и способ заполнения
    Matrix(const std::string &path);               // считываем из указанного файла
    Matrix(const Matrix& other);                                // конструктор копирования
    //Matrix()          //TODO добавить конструктор через { {} {} }
    ~Matrix() {};       // ТОДО надо сделать когда буду алоцировать память

    /* операции */
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(Matrix&) const;
    Matrix operator^(int);
    Matrix& operator=(const Matrix&);
    Row& operator[](int row);

    friend Matrix operator*(double num, Matrix& m);
    /* вспомогательные функции */
    void Print() const;
    void rff(const std::string& path);
    void rtf(const std::string& path) const;

    /* математические функции */
    friend double det(const Matrix& m);
    friend double Gaus_Alghoritm(Matrix& m);
    friend void Statistical_Information();

private:
    std::vector<Row> _matrix;
};


#endif //C_MATRIX_H
