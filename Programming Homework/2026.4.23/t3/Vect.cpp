#include <iostream>
using namespace std;

class Vect
{
private:
    float *p; // 指向向量的指针
    int n;    // 向量元素个数

public:
    Vect(int size = 0, float *data = nullptr);
    ~Vect();
    Vect operator+(const Vect &v) const;
    friend Vect operator-(const Vect &v1, const Vect &v2);
    void display() const;
};

Vect::Vect(int size, float *data)
{
    n = size;
    if (size > 0) {
        p = new float[size];
        if (data != nullptr) {
            for (int i = 0; i < size; i++) {
                p[i] = data[i];
            }
        } else {
            for (int i = 0; i < size; i++) {
                p[i] = 0;
            }
        }
    } else {
        p = nullptr;
    }
}

Vect::~Vect()
{
    if (p != nullptr) {
        delete[] p;
    }
}

Vect Vect::operator+(const Vect &v) const
{
    if (n != v.n) {
        cout << "Error: vectors must have the same size for addition." << endl;
        return Vect();
    }
    Vect result(n);
    for (int i = 0; i < n; i++) {
        result.p[i] = p[i] + v.p[i];
    }
    return result;
}

Vect operator-(const Vect &v1, const Vect &v2)
{
    if (v1.n != v2.n) {
        cout << "Error: vectors must have the same size for subtraction." << endl;
        return Vect();
    }
    Vect result(v1.n);
    for (int i = 0; i < v1.n; i++) {
        result.p[i] = v1.p[i] - v2.p[i];
    }
    return result;
}

void Vect::display() const
{
    cout << "(";
    for (int i = 0; i < n; i++) {
        cout << p[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
}

int main()
{
    float data1[] = {1.0, 2.0, 3.0};
    float data2[] = {4.0, 5.0, 6.0};
    Vect v1(3, data1);
    Vect v2(3, data2);

    cout << "v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();

    Vect v3 = v1 + v2;
    cout << "v1 + v2 = ";
    v3.display();

    Vect v4 = v1 - v2;
    cout << "v1 - v2 = ";
    v4.display();

    float data3[] = {1.0, 2.0};
    Vect v5(2, data3);
    cout << "\nTest different sizes:" << endl;
    Vect v6 = v1 + v5;

    return 0;
}
