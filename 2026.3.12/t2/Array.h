#ifndef ARRAY_H
#define ARRAY_H

class Array
{
private:
    int* x;
    int n;
public:
    Array();
    ~Array();
    void input(int* a); // 将一个矩阵赋值给对象中的数组
    void print(); // 按行输出矩阵的值
    void change(); // 转置矩阵
};
#endif 