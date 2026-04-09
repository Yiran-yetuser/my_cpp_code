#include "NN.h"

#include <cmath>
#include <iostream>

NN::NN(float t[], float d)
{
    w = new float[5];
    x = new float[5];
    for (int i = 0; i < 5; i++) {
        w[i] = t[i];
        x[i] = 0.0f;
    }
    dt = d;
    y = 0.0f;
}

NN::~NN()
{
    if (w) {
        delete[] w;
        w = nullptr;
    }
    if (x) {
        delete[] x;
        x = nullptr;
    }
}

void NN::fun(float t[])
{
    double temp = 0.0;
    for (int i = 0; i < 5; i++) {
        x[i] = t[i];
        temp += (x[i] - w[i]) * (x[i] - w[i]);
    }
    temp = temp / (-2 * dt * dt);
    temp = exp(temp);
    y = (float)temp;
}

void NN::print()
{
    std::cout << "Input signals: ";
    for (int i = 0; i < 5; i++) {
        std::cout << x[i] << "\t";
    }
    std::cout << "\nOutput signal: " << y << std::endl;
}
