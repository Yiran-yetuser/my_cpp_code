#include <iostream>
using namespace std;
struct Fraction {
    int numerator;
    int denominator;
};
int gcd(int a, int b) {
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
    Fraction f1 = {1, 2}; // 1/2
    Fraction f2 = {1, 3}; // 1/3
    Fraction f3 = {2, 4}; // 2/4
    Fraction f4 = {3, 6}; // 3/6

    show(add(f1,f2));
    show(add(f1,f4));

    return 0;
}
