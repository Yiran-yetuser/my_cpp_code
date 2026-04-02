#include "NN.cpp"
#include "NN.h"

#include <iostream>
int main()
{
    float input[5] = {1.2, 3.5, 2.3, 3.2, 2.8};
    float w[5] = {0.5, 0.8, 1.2, 1.8, 1.1};
    double sigma = 1;

    NN n1(w, sigma);
    n1.fun(input);
    n1.print();
    return 0;
}