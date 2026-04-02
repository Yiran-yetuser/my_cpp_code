
#include <iostream>
class Array
{
private:
    int *x; // n*n二维数组作为一维数组存储
    int n;  // 矩阵行数
public:
    Array(int m);
    ~Array();
    void input(int *a); // 将一个矩阵赋值给对象中的数组
    void print();
    void transpose(); // 将对象中的矩阵转置
};

inline Array::Array(int m = 3)
{
    n = m;
    x = new int[m * m];
}

inline Array::~Array()
{
    if (x) {
        delete[] x;
        x = nullptr;
    }
}

inline void Array::input(int *a)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x[i * n + j] = a[i * n + j];
        }
    }
}

inline void Array::print()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << x[i * n + j] << "\t";
        }
        std::cout << std::endl;
    }
}

inline void Array::transpose()
{
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            std::swap(x[i * n + j], x[j * n + i]);
        }
    }
}
