#include "Array.h"
#include <iostream>

Array::Array(int length) // 默认参数已在.h文件中声明过，在.cpp文件中不能包含
{
    n = length;
    x = new int[length * length];
}

Array::~Array()
{
    if (x) {
        delete[] x;
        x = nullptr;
    }
}

void Array::input(int *a)
{
    for(int i = 0;i<n*n;i++) {
        x[i] = a[i];
    }
}

void Array::print()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << x[i * n + j]<<"\t";
        }
        std::cout << std::endl;
    }
}

void Array::change()
{
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            std::swap(x[i * n + j], x[j * n + i]);
        }
    }
}
