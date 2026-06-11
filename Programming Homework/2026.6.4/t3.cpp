#include <iostream>
#include <stdexcept>
using namespace std;

// ========== TODO: 请在此处设计并实现 Matrix<T> 类模板 ==========
// 要求：
// - 支持构造、拷贝构造、析构、赋值运算符（深拷贝）
// - 重载 operator+ 实现同尺寸矩阵相加，维度不同时应输出错误信息并返回空矩阵
// - 重载 operator* 实现矩阵乘法，维度不合法时输出错误信息并返回空矩阵
// - 重载 operator<< 用于流输出矩阵，格式：每行元素用空格分隔，行间换行
// - 使用 int 表示维度与索引，禁止使用 size_t
// - 所有成员函数在类定义内部实现（内联）
//
// 提示：可使用动态数组（T* data）一维数组模拟二维数组，在构造函数中分配 rows * cols 的空间。
// [重大优化提示 8分] 在 operator+ 或 operator* 返回对象时，利用返回值优化（NRVO），
// 直接在返回语句中构造临时对象，避免不必要的拷贝。
// [一般优化提示 5分] 在矩阵乘法中引入临时缓存，先在局部一维数组中累加计算结果，
// 再写入目标矩阵，可改善缓存局部性。
// [小优化提示 2分] 在 operator() 或 at 中增加边界检查（若实现）。
// [小优化提示 2分] 赋值运算符中检查自赋值。

template <typename T>
class Matrix
{
private:
    T *data;   // 二维动态数组
    int nRows; // 行数
    int nCols; // 列数

public:
    // 构造：创建 rows 行 cols 列的矩阵，可初始化为默认值 T()
    Matrix(int rows, int cols)
    {
        // TODO: 实现
        nRows = rows;
        nCols = cols;
        data = new T[nRows * nCols];
    }

    // 拷贝构造（深拷贝）
    Matrix(const Matrix &other)
    {
        // TODO: 实现
        nRows = other.nRows;
        nCols = other.nCols;
        data = new T[nRows * nCols];
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                data[i * nCols + j] = other.data[i * nCols + j];
            }
        }
    }

    // 析构
    ~Matrix()
    {
        // TODO: 实现
        if (data != nullptr) {
            delete[] data;
        }
        data = nullptr;
    }

    // 赋值运算符（深拷贝）
    Matrix &operator=(const Matrix &other)
    {
        // TODO: 实现
        if (this != &other) {
            nRows = other.nRows;
            nCols = other.nCols;
            delete[] data;
            data = new T[nRows * nCols];
            for (int i = 0; i < nRows; ++i) {
                for (int j = 0; j < nCols; ++j) {
                    data[i * nCols + j] = other.data[i * nCols + j];
                }
            }
        }
        return *this;
    }

    // 矩阵加法
    Matrix operator+(const Matrix &other) const
    {
        // TODO: 实现
        if (nRows != other.nRows || nCols != other.nCols) {
            cout << "矩阵维度不匹配，无法进行加法运算。" << endl;
            return Matrix(0, 0); // 返回空矩阵
        }

        Matrix result(nRows, nCols);
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                result.data[i * nCols + j] = data[i * nCols + j] + other.data[i * nCols + j];
            }
        }
        return result;
    }

    // 矩阵乘法
    // 原代码中的 operator* 可以修改为 i-k-j 顺序
    Matrix operator*(const Matrix &other) const
    {
        if (nCols != other.nRows) {
            std::cout << "维度不匹配：当前列数(" << nCols
                      << ") != 右矩阵行数(" << other.nRows << ")，无法相乘。" << std::endl;
            return Matrix(0, 0);
        }

        Matrix result(nRows, other.nCols);
        // 将 result 所有元素初始化为 T()（例如 0）
        for (int i = 0; i < nRows * other.nCols; ++i)
            result.data[i] = T();

        // 为每一行分配一个局部缓存数组
        for (int i = 0; i < nRows; ++i) {
            // 局部一维数组，存储第 i 行的临时结果
            T *rowCache = new T[other.nCols];
            for (int j = 0; j < other.nCols; ++j)
                rowCache[j] = T();

            for (int k = 0; k < nCols; ++k) {
                T aik = data[i * nCols + k];
                for (int j = 0; j < other.nCols; ++j) {
                    rowCache[j] += aik * other.data[k * other.nCols + j];
                }
            }
            // 一次性将行缓存写入 result 的第 i 行
            for (int j = 0; j < other.nCols; ++j)
                result.data[i * other.nCols + j] = rowCache[j];
            delete[] rowCache;
        }
        return result;
    }
    // 流输出（友元函数可在类内直接定义）
    friend ostream &operator<<(ostream &os, const Matrix<T> &m)
    {
        // TODO: 实现
        for (int i = 0; i < m.nRows; ++i) {
            for (int j = 0; j < m.nCols; ++j) {
                os << m.data[i * m.nCols + j] << " ";
            }
            os << endl;
        }
        return os;
    }

    // 可选：获取行数、列数、访问元素等辅助函数
    int rows() const { return nRows; }
    int cols() const { return nCols; }
    T &at(int r, int c)
    {
        if (r < 0 || r >= nRows || c < 0 || c >= nCols)
            throw std::out_of_range("Matrix::at index out of range");
        return data[r * nCols + c];
    }
    const T &at(int r, int c) const
    {
        if (r < 0 || r >= nRows || c < 0 || c >= nCols)
            throw std::out_of_range("Matrix::at index out of range");
        return data[r * nCols + c];
    }
};

// ===== 请回答以下问题（写在下方注释中） =====
// Q1: 模板类的声明与实现为何通常放在同一个头文件中？如果分离到 .h 和 .cpp 会有什么问题？
// 作答：
// 模板类的声明与实现必须放在同一个头文件中，因为模板在编译时需要进行实例化。
// 当编译器遇到模板类的使用（如 Matrix<int>）时，需要看到完整的模板定义才能生成
// 对应的具体代码。如果将实现分离到 .cpp 文件中，编译器在编译使用该模板的源文件
// 时无法看到模板的实现，导致链接错误（undefined reference）。这是因为模板不是真
// 正的代码，而是代码生成的"蓝图"，只有在实例化时才会生成实际的目标代码。
//
// Q2: 在矩阵乘法中如何检查维度合法性？从优化循环顺序的角度，你建议如何改进常见的
// i-j-k 三重循环，以提升缓存命中率？
// 作答：
// 维度合法性检查：在 operator* 中，检查 this->nCols == other.nRows，如果不相等
// 则输出错误信息并返回空矩阵（行数和列数为 0 的矩阵）。
//
// 循环顺序优化：常见的 i-j-k 顺序在计算 C[i][j] += A[i][k] * B[k][j] 时，对 B 的
// 访问是按列跳跃的，缓存命中率低。建议改为 i-k-j 顺序：
//   for (int i = 0; i < rows; ++i)
//       for (int k = 0; k < colsA; ++k)
//           for (int j = 0; j < colsB; ++j)
//               C[i][j] += A[i][k] * B[k][j];
// 这样在內层循环中，A[i][k] 保持不变，B[k][j] 按行连续访问，C[i][j] 也按行连续访问，
// 充分利用缓存的空间局部性，显著提升性能。
//
// 额外的优化说明 (程序原注解中已进行优化提示，且已实现的优化不必在此说明)
// 请在此列出你额外实现且未在上述提示中出现的优化点，并自评对应分值（重大8分/一般5分/小2分，累计上限10分）。
// 作答：
// 1. 矩阵乘法中，检查维度合法性时，如果 nCols != other.nRows，直接输出错误信息并返回空矩阵。（小）
// 2. 矩阵乘法中，循环顺序改为 i-k-j，以提升缓存命中率。（一般）
// 3. [重大优化提示 8分] 在 operator+ 或 operator* 返回对象时，利用返回值优化（NRVO），
// 直接在返回语句中构造临时对象，避免不必要的拷贝。
// =========================================

// ========== 主函数（测试用例，不可修改） ==========
int main()
{
    int r1, c1, r2, c2;

    // 读入矩阵A
    cout << "输入矩阵 A的行数和列数: ";
    cin >> r1 >> c1;
    Matrix<int> A(r1, c1);
    cout << "输入矩阵 A的元素 (" << r1 << " x " << c1 << "):" << endl;
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c1; ++j) {
            int val;
            cin >> val;
            A.at(i, j) = val; // 假设提供了 at 方法，若未提供可直接访问 data
                              // （但 data 为 private，需学生自己设计访问方式）
                              // 提示：学生需自行提供合理的访问接口，如 at() 或 operator()
        }

    // 读入矩阵B
    cout << "输入矩阵 B的行数和列数: ";
    cin >> r2 >> c2;
    Matrix<int> B(r2, c2);
    cout << "输入矩阵 B的元素 (" << r2 << " x " << c2 << "):" << endl;
    for (int i = 0; i < r2; ++i)
        for (int j = 0; j < c2; ++j) {
            int val;
            cin >> val;
            B.at(i, j) = val;
        }

    // 测试输出
    cout << "\n矩阵 A:" << endl
         << A << endl;
    cout << "矩阵 B:" << endl
         << B << endl;

    // 测试加法（同尺寸）
    if (r1 == r2 && c1 == c2) {
        Matrix<int> C = A + B;
        cout << "A + B:" << endl
             << C << endl;
    } else {
        cout << "A和 B尺寸不同，无法进行加法运算。" << endl;
    }

    // 测试乘法
    if (c1 == r2) {
        Matrix<int> D = A * B;
        cout << "A * B:" << endl
             << D << endl;
    } else {
        cout << "A的列数不等于 B的行数，无法进行乘法运算。" << endl;
    }

    // 测试拷贝与赋值
    Matrix<int> E = A; // 拷贝构造
    Matrix<int> F(1, 1);
    F = B; // 赋值
    cout << "拷贝构造的 E (来自 A):" << endl
         << E << endl;
    cout << "赋值后的 F (来自 B):" << endl
         << F << endl;

    return 0;
}
