#include <iostream>
using namespace std;
struct Fraction {
    int numerator;
    int denominator;
};
int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
void show(Fraction f)
{
    cout << f.numerator << "/" << f.denominator;
}
void reduce(Fraction *f)
{
    int factor = gcd(f->denominator, f->numerator);
    f->denominator /= factor;
    f->numerator /= factor;
    if (f->denominator < 0) {
        f->numerator = -f->numerator;
        f->denominator = -f->denominator;
    }
}
Fraction add(Fraction a, Fraction b)
{
    Fraction res;
    res.denominator = a.denominator * b.denominator;
    res.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    reduce(&res);
    return res;
}
Fraction mul(Fraction a, Fraction b)
{
    Fraction res;
    res.denominator = a.denominator * b.denominator;
    res.numerator = a.numerator * b.numerator;
    reduce(&res);
    return res;
}

// 测试主函数
int main()
{
    // 测试用例1: 两个正分数
    cout << "=== 测试用例1: 正分数运算 ===" << endl;
    Fraction a, b, result;
    a.numerator = 1;
    a.denominator = 2;
    b.numerator = 1;
    b.denominator = 3;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl
         << endl;

    // 测试用例2: 一个正分数和一个负分数
    cout << "=== 测试用例2: 正负分数运算 ===" << endl;
    a.numerator = -1;
    a.denominator = 2;
    b.numerator = 2;
    b.denominator = 3;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl
         << endl;

    // 测试用例3: 涉及零的分数
    cout << "=== 测试用例3: 零分数运算 ===" << endl;
    a.numerator = 0;
    a.denominator = 1;
    b.numerator = 3;
    b.denominator = 4;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl
         << endl;

    // 测试用例4: 分母为负的分数（在运算中自动规范化）
    cout << "=== 测试用例4: 分母为负的分数运算 ===" << endl;
    a.numerator = 1;
    a.denominator = -2; // 表示 -1/2
    b.numerator = 1;
    b.denominator = 3;
    cout << "原始分数 a: ";
    show(a);
    cout << " (约分后: ";
    Fraction temp = a;
    reduce(&temp);
    show(temp);
    cout << ")" << endl;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl
         << endl;

    // 测试用例5: 需要约分的分数
    cout << "=== 测试用例5: 约分测试 ===" << endl;
    a.numerator = 2;
    a.denominator = 4; // 等价 1/2
    b.numerator = 2;
    b.denominator = 6; // 等价 1/3
    cout << "原始分数 a: ";
    show(a);
    cout << ", b: ";
    show(b);
    cout << endl;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl
         << endl;

    // 测试用例6: 相同分母的分数
    cout << "=== 测试用例6: 同分母分数运算 ===" << endl;
    a.numerator = 3;
    a.denominator = 5;
    b.numerator = 2;
    b.denominator = 5;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl
         << endl;

    // 测试用例7: 结果为整数的分数
    cout << "=== 测试用例7: 结果为整数 ===" << endl;
    a.numerator = 1;
    a.denominator = 2;
    b.numerator = 2;
    b.denominator = 1;
    cout << "加法: ";
    show(a);
    cout << " + ";
    show(b);
    cout << " = ";
    result = add(a, b);
    show(result);
    cout << endl;
    cout << "乘法: ";
    show(a);
    cout << " * ";
    show(b);
    cout << " = ";
    result = mul(a, b);
    show(result);
    cout << endl;

    return 0;
}