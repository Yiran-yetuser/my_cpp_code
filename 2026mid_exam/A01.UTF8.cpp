#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
using namespace std;

// ================== 学生需要实现的代码开始 ==================
class Vector3D
{

private:
    double x;
    double y;
    double z;

public:
    explicit Vector3D(double a = 0, double b = 0, double c = 0);
    ~Vector3D();
    friend Vector3D operator+(const Vector3D &a, const Vector3D &b);
    friend Vector3D operator-(const Vector3D &a, const Vector3D &b);
    friend double operator*(const Vector3D &a, const Vector3D &b); // 点乘
    friend Vector3D operator*(const Vector3D &a, const double b);
    Vector3D &operator/(const Vector3D &other);
    Vector3D operator/(double scalar) const;

    // 友元声明，允许 operator<< 访问私有成员
    friend ostream &operator<<(ostream &os, const Vector3D &v);
    double length();
    Vector3D &normalize();
    Vector3D cross(const Vector3D &other);
};

Vector3D::Vector3D(double a, double b, double c)
{
    x = a;
    y = b;
    z = c;
}

Vector3D::~Vector3D()
{
}

Vector3D &Vector3D::operator/(const Vector3D &other)
{
    if (other.x == 0) { // 处理分母为零的情况，输出异常并返回
        cout << "Error!" << endl;
    } else {
        x /= other.x;
    }

    if (other.y == 0) {
        cout << "Error!" << endl;

    } else {
        y /= other.y;
    }
    if (other.z == 0) {
        cout << "Error!" << endl;

    } else {
        z /= other.z;
    }
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const
{
    if (scalar == 0) {
        cout << "Error!" << endl;
        return Vector3D();
    }
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

double Vector3D::length()
{
    return sqrt(x * x + y * y + z * z);
}

Vector3D &Vector3D::normalize()
{
    int len = length();
    x = x / len;
    y = y / len;
    z = z / len;
    return *this;
}

Vector3D Vector3D::cross(const Vector3D &other)
{
    Vector3D res;
    res.x = y * other.z - z * other.y;
    res.y = z * other.x - x * other.z;
    res.z = x * other.y - y * other.x;
    return res;
}
// Vector3D operator*(const Vector3D &v, const double a)
// {
//     Vector3D res;
//     res.x = a * v.x;
//     res.y = a * v.y;
//     res.z = a * v.z;
//     return res;
// }

Vector3D operator+(const Vector3D &a, const Vector3D &b)
{
    Vector3D res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return res;
}
Vector3D operator-(const Vector3D &a, const Vector3D &b)
{
    Vector3D res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return res;
}

double operator*(const Vector3D &a, const Vector3D &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3D operator*(const Vector3D &a, const double b)
{
    Vector3D res;
    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    return res;
}

// ================== 学生需要实现的代码结束 ==================
// 友元函数实现（教师提供）
ostream &operator<<(ostream &os, const Vector3D &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

/*
==================== 回答问题（15%） =============================
问: operator* 在本类中被重载了两次：一次用于向量与标量相乘，一次用于向量点积。
    这种“同一个运算符因参数类型不同而表现出不同行为”的机制在 C++ 中叫作什么？
    从面向对象的角度，它如何帮助提升代码的可读性和自然性？

答: 运算符重载。运算符重载可以让自定义类型的运算更加直观，减少难读的代码，提升阅读的自然性。让代码更直观。

==================== 程序优化（附加10%，可选）====================
期望优化得分：_10_分（学生填写）

优化点1：Vector3D &operator/(const Vector3D &other)
        处理分母为零的情况，输出异常并返回

优化点2：将函数实现在类外，提升代码可读性

……

*/

int main()
{
    // 定义三角形的三个顶点
    Vector3D A(0, 0, 0);
    Vector3D B(1, 2, 3);
    Vector3D C(4, 1, 0);

    // 计算三角形两条边向量
    Vector3D AB = B - A; // 需要 operator-
    Vector3D AC = C - A;

    // 计算法向量（叉积）
    Vector3D N = AB.cross(AC); // 需要 cross
    // cout << "       Normal vector: " << N
    //      << " (length = " << N.length() << ")" << endl;

    // 归一化法向量
    Vector3D normal = N.normalize(); // 需要 normalize

    cout << "   Triangle vertices: A" << A << ", B" << B << ", C" << C << endl;
    cout << "       Normal vector: " << normal
         << " (length = " << normal.length() << ")" << endl;

    // 给定入射光线方向（指向物体）
    Vector3D lightDir(0.0, 0.0, 1.0);

    // 计算光线在表面上的反射方向 (镜面反射)
    // R = L - 2 * (L·N) * N
    double dot = lightDir * normal; // 需要 operator* (点积)
    Vector3D reflect = lightDir - normal * (2.0 * dot);
    // 需要 operator* (标量乘), operator-
    // 类型辨析：
    // 1. lightDir * normal 是点积，结果 dot 是 double 类型
    // 2. normal * (2.0 * dot) 是标量乘，
    //    是 Vector3D * double，结果是 Vector3D 类型
    // 3. lightDir - (normal * (2.0 * dot)) 是向量减法，
    //    是 Vector3D - Vector3D，结果是 Vector3D 类型

    cout << "     Light direction: " << lightDir << endl;
    cout << "Reflection direction: " << reflect
         << " (length = " << reflect.length() << ")" << endl;

    // 额外测试：缩放
    Vector3D scaled = normal * 5.0; // 需要 operator*
    Vector3D shrunk = scaled / 2.5; // 需要 operator/
    cout << "     Scaled & shrunk: " << scaled << " -> " << shrunk << endl;

    return 0;
}

/* 期望输出（数值可能略有差异）
   Triangle vertices : A(0, 0, 0), B(1, 2, 3), C(4, 1, 0)
       Normal vector : (-0.211079, 0.844317, -0.492518) (length = 1)
     Light direction : (0, 0, 1)
Reflection direction : (-0.207921, 0.831683, 0.514851) (length = 1)
      Scaled& shrunk : (-1.0554, 4.22159, -2.46259) -> (-0.422159, 1.68863, -0.985037)
*/
