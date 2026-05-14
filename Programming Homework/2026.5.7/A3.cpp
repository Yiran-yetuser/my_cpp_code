#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

class Fraction
{
    // 这个类中所有的构造、析构请答题者自行建构
    // （50分）
private:
    // 填充必要的成员变量
    int n; //	代表分子
    int m; //  代表分母

    // 如还要需要其他成员变量，请自行补充

public:
    // 填充必要的成员函数

    // 单参数构造，输入分子，分母置 1
    Fraction(int numerator)
    {
        n = numerator;
        m = 1;
    }

    // 双参数构造，输入分子、分母
    Fraction(int numerator, int denominator)
    {
        // 内容请自行填写
        if (denominator == 0) {
            cout << "Wrong!" << endl;
            exit(1);
        }
        n = numerator;
        m = denominator;
        Reduce();
    }

    // AddWith
    void AddWith(Fraction &other)
    {
        if (m == other.m) {
            n += other.n;
        } else {
            n = n * other.m + other.n * m;
            m = m * other.m;
        }
        Reduce();
    }

    // MulWith
    void MulWith(Fraction &other)
    {
        // 内容请自行补充
        n = n * other.n;
        m = m * other.m;
        Reduce();
    }

    void Print() const
    {
        if (n == 0) {
            cout << 0;
        } else if (m == 1) {
            cout << n;
        } else {
            cout << n << " / " << m;
        }
    }

    // 如果还需要增加其他成员函数，请自行补充
    void Reduce()
    {
        int g = gcd(n, m);
        n /= g;
        m /= g;
        if (m < 0) { // 保持分母为正
            n = -n;
            m = -m;
        }
    }
};

// 构建一个Fraction 分数类，完成分数的计算，
// 所有的数据都必须以分数，即"a / b"的形式输出，如果b为1，则只输出a
// 并且注意， a/b 是约分后的结果

int main()
{
    // 输出 1 + (1/2)*(1/2) + (1/3)*(1/3) + ... + (1/10)(1/10) 的结果
    // 以分数形式输出
    Fraction sum(0); // sum = 0，即 0/1，这里调用了单参数构造
    for (int i = 1; i <= 10; ++i) {
        Fraction item(1, i); // 实现 item = 1/i
        item.MulWith(item);  // 实现 item = item * item
        sum.AddWith(item);   // 实现 sum += item
    }

    sum.Print();
}
