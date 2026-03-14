#include "Array.cpp"
#include "Array.h"
#include <iostream>

int main()
{
    Array A;
    int a[] ={1,3,5,2,4,6,7,9,11};
    A.input(a);
    A.print();
    A.change();
    A.print();
    return 0;
}