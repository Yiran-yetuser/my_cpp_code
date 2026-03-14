#ifndef ARRAY_H
#define ARRAY_H

// n*n矩阵
class Array
{
private:
    int* x; // 指向存储一个 n×n 矩阵值的内存区域（二维数组作为一维数组存储）
    int n; // 存储矩阵行数
public:
    Array(int length = 3); // 用一维数组表示二维数组
    ~Array();
    void input(int* a); // 将一个矩阵赋值给对象中的数组
    void print(); // 按行输出矩阵的值
    void change(); // 转置矩阵
};
#endif 