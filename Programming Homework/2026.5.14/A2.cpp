#include <iostream>
using namespace std;

class PolyLine;

// 类Point的定义
class Point
{
    double x, y;

public:
    // 缺省构造函数
    Point(double px = 0, double py = 0) : x(px), y(py) {}

    // 输出运算符的全局重载
    friend ostream &operator<<(ostream &out, const Point &p);
    friend class PolyLine;
};

// 输出运算符的全局重载
ostream &operator<<(ostream &out, const Point &p)
{
    // 请填写代码------------6分-------------------
}

// 类PolyLine的定义
class PolyLine
{
    Point *pLine;
    int size;

public:
    // 构造函数，动态分配空间
    PolyLine(double *xArr, double *yArr, int size)
    {
        this->size = size;
        pLine = new Point[size];

        for (int i = 0; i < size; i++) {
            pLine[i].x = xArr[i];
            pLine[i].y = yArr[i];
        }
    }

    // 将点p添加到折线中。注意，由于空间不够，需要重新分配空间（3分），
    // 并完成新旧数组之间的拷贝（3分），再加入新数据（3分），
    // 同时不得发生内存泄漏（3分）
    PolyLine &operator+=(const Point &p)
    {
        // 请填写代码------------12分-------------------
    }

    // 获取折线上第i个点的数据
    Point operator[](int i) const
    {
        // 请填写代码------------4分-------------------
    }

    // 析构函数，释放动态分配空间
    ~PolyLine()
    {
        delete[] pLine;
    }
};

// 输出运算符重载函数，输出折线上所有点的数据
ostream &operator<<(ostream &out, const PolyLine &pl)
{
    // 请填写代码------------6分-------------------
    // 请在没有 friend 的情况下完成输出工作
    // 注意：如有必要，可以对PolyLine类进行适当改造，但不得开启对本函数的友元
}

int main()
{
    double xArr[] = {0, 7.7, 32.6, 12.4, 20.1, 0};         // 折线所有对应点的x坐标
    double yArr[] = {0, -23.7, -23.7, 38.4, -62.1, -47.4}; // 折线所有对应点的y坐标

    PolyLine poly(xArr, yArr, 6);
    cout << "数据点：\n"
         << poly << endl
         << endl;

    poly += poly[0]; // 将折线的第0个点坐标值添加到折线最后
    cout << "添加数据点后：\n"
         << poly << endl;
    return 0;
}

// 在注解中回答问题：（7分）
//  借助题目中的一段人机对话对话，说一说你在实现PolyLine类的“<<”非友元重载时做的工作，
//  和对话中的描述相匹配吗？这里应当采用通用方案，而非为了运行通过的临时方案。