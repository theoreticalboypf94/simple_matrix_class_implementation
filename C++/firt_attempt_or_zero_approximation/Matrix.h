//
// Created by alpharius on 21.01.19.
//

#ifndef MATRIX_AND_OPERATIONS_MATRIX_H
#define MATRIX_AND_OPERATIONS_MATRIX_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>



/*
 *  https://stackoverflow.com/questions/6969881/operator-overload
 *  первая же проблема в том, что нет возможности перегрузить оператор [][] , можно только вызвать один оператор []
 *  на строку а потом его на элемент этой строки, в общем без внутренней подструктуры это не сделать
 */


class Matrix {
private:
    std::vector<double> _arr;


public:
    int height, width;
    Matrix(int height, int width) : height(height), width(width){
        _arr.assign(height*width, 0);
    }
    void set(int i, int j, double value) { _arr[i*width + j] = value;}
    void print();
    double get(int i, int j) {return _arr[i*width + j];}
    void rff(std::string);
    Matrix operator*(Matrix& b);
    void T();
    void swap_column( int J1, int J2);        //вопрос 1: файл уже достаточно разросся и актуальной становится проблема декомпозиции функций на отдельные
    void swap_row( int I1, int I2);           // подпрограммы - вопрос знатокам- как это делают нормальные люди? (ну например определение класса в хэдере
    void Gauss_method();                     // а имплементации функций в другом хедере) (как лучше?)

    void row_multiplication(int I, double numerator);
    void row_adition(int I1, int I2, double numerator);

};

void Matrix::T(){
    double tmp;
    for(int i=0; i<height; i++){
        for(int j=i; j<width; j++){
            tmp = get(i,j);
            set(i,j, get(j,i));
            //print();
            set(j,i, tmp);
            //print();
        }
    }
}

void Matrix::print(){
    std::cout << std::endl;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            //std::cout << get(i,j) << "\t\t";
            printf("%10.4f",get(i,j));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "height = " << this->height << " width = " << this->width;
    std::cout << std::endl;
}

void Matrix::rff(std::string path){
    // Read From File function
    std::ifstream file;
    std::string st;
    int i=0, j=0;
    file.open(path);
    if (file.is_open()) {
        std::cout << "it opened" << std::endl;
        while (!file.eof()) {
            st = "";
            file >> st;
            //std::cout << st << std::endl;
            if (j == this->width){
                j=0;
                i += 1;
            }
            this->set(i, j, std::stod(st));
            j+=1;
        }
    } else {
        std::cout << "you have an error, yout file didn't open" << std::endl;
    }
}

Matrix Matrix::operator*(Matrix& b){
    if (this->width == b.height){
        Matrix result(this->height, b.width);
        double intermediate = 0.;
        int i,j;
        for (int i=0; i<this->height; i++){
            for(int j=0; j<b.width; j++){
                for(int k=0; k<this->width; k++){
                    intermediate += this->get(i,k)*b.get(k,j);
                }
                result.set(i,j,intermediate);
                intermediate = 0.;
            }
        }
        return result;

    } else {
        std::cout << "fatall error with shape in multiplication" << std::endl;
        throw "ERROR";
    }
}

Matrix operator*(double a, Matrix A){
    /*
     * define multiplication between matrix and double number
     */
    Matrix result(A.height, A.width);
    for(int i=0; i<A.height; i++){
        for(int j=0; j<A.width; j++){
            result.set(i,j, a*A.get(i,j));
        }
    }
    return result;
}

Matrix operator*( Matrix A,double a) {
    return a*A;
}

double det_2to2(Matrix& A){
    // expression to find determinanto from 2x2 matrix.
    return A.get(0,0)*A.get(1,1) - A.get(0,1)*A.get(1,0);
}

Matrix Minor_Matrix(Matrix& A, int I, int J){
    // return Matrix with shape - one row one len
    /*
     *  return minor matrix - matrix produced from origin ones with remote selected row and col.
     */
    Matrix result(A.height-1, A.width-1);
    int loop_i, loop_j;
    for(int i=0; i<A.height; i++){
        for(int j=0; j<A.width; j++){
            loop_i = i<I? i : i-1;
            loop_j = j<J? j : j-1;
            if (i!=I and j!=J)
                result.set(loop_i, loop_j, A.get(i,j));
        }
    }
    return result;
}

double det(Matrix& A){
    double result = 0.;
    auto Sign = [](int h) {return h%2 == 0? 1 : -1;};
    if (A.height == 2)              //определитель есть только у квадратных матриц
        return det_2to2(A);
    else {
        for(int j=0; j<A.height; j++){ //
            Matrix loop = Minor_Matrix(A, 0, j);
            result += Sign(j) * det(loop) * A.get(0,j);
        }
    }
    return result;
}

Matrix reverse(Matrix& A){
    /*
     *  function find reverse matrix to input A
     *  A^-1 * A = A * A^-1 = E
     *
     *  A^-1 = 1/det(A) * matrix_transformed_algebraitic_adiction
     */
    double denominator = det(A), loop_result;
    Matrix result(A.height, A.width);
    Matrix minor_matrix(A.height-1, A.width-1);
    auto Sign = [](int arg){ return (arg%2==0)? 1 : -1;};
    for(int i=0; i<A.height; i++){
        for(int j=0; j<A.width; j++){
            minor_matrix = Minor_Matrix(A,i,j);
            loop_result = 1./denominator * Sign(i+j) * det(minor_matrix);
            result.set(i,j, loop_result);
        }
    }
    result.T();
    return result;
}

void Matrix::swap_column( int J1, int J2) {
    /*
     *  elementvise swap column between J1 and J2 troughout temporary variable
     */
    double tmp;
    for(int i=0; i<height; i++){
        tmp = get(i, J1);
        set(i, J1, get(i, J2));
        set(i, J2, tmp);
    }
}

void Matrix::swap_row( int I1, int I2){
    /*
     *  element vise swap two rows troughout third variable
     */
    double tmp = 0;
    for(int j=0; j<width; j++){
        tmp = get(I1, j);
        set(I1, j, get(I2,j));
        set(I2, j, tmp);
    }
}

void Matrix::row_multiplication(int I, double numerator) {
    /*
     *  private method for gaus alghoritm
     *  elementvesi multiplication elemenths to selected row
     */
    for(int j=0; j<width; j++){
        set(I, j, numerator * get(I, j));
    }
}

void Matrix::row_adition(int I1, int I2, double numerator) {
    /*
     *  private method for Gauss alghoritm
     *  It goal to elementvise addition one row to another one
     *  from I1 to I2
     */
    for(int j=0; j<width; j++){
        set(I2, j, get(I2,j) + numerator * get(I1, j));
    }
}

void Matrix::Gauss_method(){
    /*
     *
     *  TODO add english doc.
     *  последняя строка будет играть роль расширенной матрицы.
     *  тогда слау будет 3 уравнения 3 неизвестных будет представлена здесь как матрица 3 на 4
     *
     *  Да, тут реализован наиболее простой метод гауса который работает на заведомо лояльных
     *  входных данных - определитель отличен от нуля, нет нулевых элементов, ранг основной
     *  матрицы равен рангу расширенной матрицы. Just for learn goal
     *
     *  2.2 3.4 6.5 4
     *  5.6 6.7 5.5 4   -даст ответ->  (-0.7697, 0.9136, 0.3980)
     *  5 4 3 1
     */

    // прямой ход метода Гаусса
    for(int j=0; j<width-1; j++ ){
        for(int i=j; i<height; i++){
            row_multiplication(i, 1./get(i,j));
        }
        for(int i=j+1; i<height; i++){
            row_adition(j,i,-1);
        }
    }
    print();
    // обратный ход метода Гаусса
    for(int j=width-2; j>-1; j--){
        for(int i=j-1; i>-1; i--){
            row_multiplication(j, get(i,j));
            row_adition(j,i, -1);
            row_multiplication(j,1./get(j,j));
        }
    }





}

#endif //MATRIX_AND_OPERATIONS_MATRIX_H
