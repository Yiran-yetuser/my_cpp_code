#include "Array.h"
#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "请输入矩阵的行数：";
    cin >> n;
    Array arr(n);
    int *a = new int[n * n];
    cout << "请输入矩阵的元素：" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i * n + j];
        }
    }
    arr.input(a);
    cout << "输入的矩阵为：" << endl;
    arr.print();
    arr.transpose();
    cout << "转置后的矩阵为：" << endl;
    arr.print();
    delete[] a;
    return 0;
}