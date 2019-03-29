//
// Created by alpharius on 29.03.19.
//

#include <assert.h>
#include "Matrix.h"

#define ACCESS(i,j) _matrix[ i ].row[ j ]
#define LOOP(up1, up2, expression1, expression2)    for(size_t i=0; i<up1; i++) {\
                                                        for(size_t j=0; j<up2; j++){\
                                                            expression1;\
                                                        }\
                                                    expression2;\
                                                    }\

                                    /* конструкторы */

Matrix::Matrix(size_t h, size_t w, MOD mod){
    srand(time(NULL));
    for(size_t i=0; i<h; i++){
        _matrix.push_back(Row(w));
    }
    height = h;
    width = w;

    switch (mod){
        case RND:
            LOOP(height, width, ACCESS(i,j) = rand() % 100, NULL)
            break;
        case ZEROS:
            LOOP(height, width, ACCESS(i,j) = 0, NULL);
            break;
        case ONES:
            LOOP(height, width, ACCESS(i,j) = 1, NULL);
            break;
        case DIAG:
            LOOP(height, width, ACCESS(i,j) = (i==j) ? rand() % 100 : 0, NULL);
            break;
        case TRIANGLE_TOP:
            LOOP(height, width, ACCESS(i,j) = (i<=j) ? rand() % 100 : 0, NULL);
            break;
    }
}

Matrix::Matrix(const std::string &path) {
    // конструктор, считывания параметров матрицы и самой матрицы из текстового файла,
    // первые 2 числа в файле отвечают за число строк и столбцов считываемой матрицы.


    std::ifstream file;
    file.open(path);
    assert(file.is_open());
    std::string point;
    file >> point;
    height = std::stoul(point);
    file >> point;
    width = std::stoul(point);
    int counter = 0;
    while(!file.eof()){
        file >> point;
        ACCESS(counter/width,counter % width ) = std::stod(point);   //TODO провести проверку правильности
        counter += 1;
    }
    file.close();
}

Matrix::Matrix(const Matrix &other) {
    // пока конструкторо копирования не нужен, в том смысле что мои потребности удовлетворяются
    // конструктором-копирования по умолчанию, но в будущем возможно я добавлю указатели и тогда такой конструктор
    // станет необходим, здесь я по сути воспроизведу конструктор по умолчанию.

    std::cout << std::endl << " Copy constructor is launched! \n";
    height = other.height;
    width = other.width;
    LOOP(height, width, ACCESS(i,j) = other._matrix[i].row[j], NULL);
}

Matrix::Matrix() { Matrix(1,1,ZEROS);}

                                    /* операции */

Matrix Matrix::operator+(const Matrix &other) const {
    // проведение доступа через макросы это конечно не эстетично, но оператор [][] я пока не перегрузил, так
    // что читатель, не сердись.

    assert(other.height == height);
    assert(other.width == width);
    Matrix result(other.height, other.width, ZEROS);
    LOOP(height, width, result.ACCESS(i,j) = ACCESS(i,j) + other.ACCESS(i,j), NULL);
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    assert(other.height == height);
    assert(other.width == width);
    Matrix result(other.height, other.width, ZEROS);
    LOOP(height, width, result.ACCESS(i,j) = ACCESS(i,j) - other.ACCESS(i,j), NULL);
    return result;
}

Matrix::Row& Matrix::operator[](int row) {
    return _matrix[row];
}

Matrix Matrix::operator*( Matrix &other) const{
    assert(width == other.height);
    Matrix result(height, other.width, ZEROS);
    double convolution = 0;

    LOOP(height, other.width,
            for(size_t k=0; k<width; k++){
                convolution += ACCESS(i,k) * other[k][j];
            }
                result[i][j] = convolution;
                convolution = 0;,

                NULL
        )
    return result;
}

Matrix operator*(double n, Matrix& m){
    Matrix result(m.height, m.width, ZEROS);
    LOOP(m.height, m.width, result[i][j] = n * m[i][j], NULL);
    return result;
}

Matrix& Matrix::operator=(const Matrix &rvalue) {
    _matrix.clear();
    width = rvalue.width;
    height = rvalue.height;
    for(Row rows : rvalue._matrix){
        _matrix.push_back(rows);
    }
    return *this;
}

Matrix Matrix::operator^(int power) {
    // операция возведения в степень пока определена только для целых и положительных чисел
    // TODO добавить возведение в -1 степень - как обратную матрицу.

    Matrix result(height,width, ONES);
    if (power == 1)
        return result;
    else {
        Matrix result(height,width, ZEROS);
        while(power > 0){
            result = result * (*this);
        }
    }
    return result;
}


                                    /* вспомогательные функции */

void Matrix::Print() const {
    LOOP(height,width, std::cout << ACCESS(i,j) << "| ", std::cout << std::endl;)
    std::cout << std::endl;
}

void Matrix::rff(const std::string &path) {
    std::ifstream file;
    file.open(path);
    assert(!file.is_open());
    _matrix.clear();         // не важно какой у нас была матрица. она изменит размерж

    std::string point;
    file >> point;
    height = std::stoul(point);
    file >> point;
    width = std::stoul(point);

    while(!file.eof()){
        NULL;                                               // TODO  <<<<-----------остановился здесь
    }

}