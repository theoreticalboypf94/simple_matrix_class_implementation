#include <iostream>
#include "Matrix.h"
#include <cstdio>

int main() {
    std::cout << "Hello, World!" << std::endl;
    Matrix b(4,4,TRIANGLE_TOP), a(4,4,RND);
    a.Print();
    std::string path = "../out.txt";
    a.wtf(path);


    return 0;
}