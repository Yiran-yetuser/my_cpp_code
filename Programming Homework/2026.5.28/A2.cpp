#include <cassert>
#include <cmath> // 可选，仅为容差优化时使用
#include <iostream>

// ------------------- 全局比较函数 -------------------
int CompareInt(const int &a, const int &b)
{
    // TODO: 返回 -1/0/1 表示 a<b, a==b, a>b
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

int CompareDouble(const double &a, const double &b)
{
    // TODO: 返回 -1/0/1，直接使用 <, >, == 即可
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

// ------------------- 默认比较器模板 -------------------
template <typename T>
int defaultCompare(const T &a, const T &b)
{
    // TODO: 使用 < 和 > 实现三态比较
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

// double 特化版本（可直接调用 CompareDouble）
template <>
int defaultCompare<double>(const double &a, const double &b)
{
    // TODO: 调用 CompareDouble
    return CompareDouble(a, b);
}

// ------------------- Sorter 类 -------------------
template <typename T>
class Sorter
{
private:
    T *data;
    int size;
    bool owned; // 是否拥有内存

    void swap(Sorter &other) noexcept
    {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(owned, other.owned);
    }

    // 私有快速排序函数
    void quickSort(int low, int high, int (*cmp)(const T &, const T &))
    {
        if (low >= high) {
            return;
        }

        T pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (cmp(data[j], pivot) < 0) {
                i++;
                T tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
        T tmp = data[i + 1];
        data[i + 1] = data[high];
        data[high] = tmp;

        int pi = i + 1;
        quickSort(low, pi - 1, cmp);
        quickSort(pi + 1, high, cmp);
    }

public:
    // 构造函数
    Sorter(T *externalArr, int len, bool copyData = false)
    {
        // TODO: 实现 copyData 逻辑
        // 优化点：处理 len <= 0 的情况
        if (len <= 0) {
            data = nullptr;
            size = 0;
            owned = false;
            return;
        }

        // 深拷贝
        if (copyData == true) {
            size = len;
            owned = true;
            data = new T[len];
            for (int i = 0; i < len; i++) {
                data[i] = externalArr[i];
            }
        }

        // 浅拷贝
        if (copyData == false) {
            data = externalArr;
            size = len;
            owned = false;
        }
    }

    // 析构函数
    ~Sorter()
    {
        // TODO: 释放内存（如果 owned）
        // 优化点：释放后将 data 置为 NULL
        if (owned) {
            delete[] data;
            data = nullptr;
        }
    }

    // 拷贝构造函数
    Sorter(const Sorter &other)
    {
        // TODO: 深拷贝 other 的数据，设置 owned = true
        // 优化点：检查 other.data 是否为 NULL
        if (other.data == nullptr) {
            data = nullptr;
            size = 0;
            owned = false;
            return;
        }

        size = other.size;
        owned = true;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // 赋值运算符
    Sorter &operator=(const Sorter &other)
    {
        // TODO: 自赋值检查、释放原有内存、深拷贝
        // 优化点：使用拷贝交换惯用法（copy-and-swap）
        // if (this == &other) { // 自赋值检查
        //     return *this;
        // }
        // delete[] data;
        // size = other.size;
        // owned = true;
        // data = new T[size];
        // for (int i = 0; i < size; i++) {
        //     data[i] = other.data[i];
        // }
        // return *this;

        if (this != &other) {   // 自赋值检查
            Sorter temp(other); // 利用拷贝构造函数创建临时副本
            swap(temp);         // 交换当前对象与临时副本的内容
        } // temp 离开作用域，自动释放旧资源
        return *this;
    }

    T &operator[](int idx)
    {
        assert(idx >= 0 && idx < size);
        return data[idx];
    }
    const T &operator[](int idx) const
    {
        assert(idx >= 0 && idx < size);
        return data[idx];
    }

    friend std::ostream &operator<<(std::ostream &os, const Sorter &s)
    {
        os << "[";
        for (int i = 0; i < s.size; i++) {
            os << s.data[i];
            if (i < s.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    // 排序方法
    void sort(int (*cmp)(const T &, const T &) = 0)
    {
        // TODO: 实现选择排序或冒泡排序，使用 comparator
        // 优化点：对于小数组（size<10）使用插入排序提高性能（普通优化）
        //         或者实现通用的快速排序（重大优化）
        if (size <= 0)
            return;
        auto comparator = cmp ? cmp : defaultCompare<T>;
        quickSort(0, size - 1, comparator);
    }

    // 访问器
    T *getData() const { return data; }
    int getSize() const { return size; }
};

// ------------------- 辅助打印函数 -------------------
template <typename T>
void printArray(const T *arr, int len)
{
    std::cout << "[";
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i];
        if (i < len - 1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// 3. 测试降序（自定义比较器）
int descendingInt(const int &a, const int &b)
{
    if (a > b)
        return -1;
    if (a < b)
        return 1;
    return 0;
}

// ==================== 问题回答区 ====================
// 问题：
// 1. 在 Sorter 类中，下标运算符 operator[] 为什么要同时提供 const 和非 const 两个版本？
//    如果只提供非 const 版本会有什么问题？
//
// 2. 对于 Fraction 类，为什么比较函数 compare 要设计为静态成员函数？
//    与普通全局函数相比有何优点？
//
// 3. 在 Fraction 的算术运算符重载中，返回类型为什么是 Fraction（值返回）而不是引用？
//    如果返回引用会有什么风险？
//
// 回答（请在此处填写）：
// 回答：
// 1. 非const版用于读写，const版用于只读。只提供非const版，const对象或引用无法调用，限制了const场景下的访问。
// 2. 静态成员可访问私有成员num/den，无需友元，封装性更好；不依赖特定对象，逻辑独立。
// 3. 运算符产生新结果，不能返回局部对象的引用（悬垂）；返回值语义安全，符合值语义预期。
// ==================== 分数类 Fraction 框架 ====================
class Fraction
{
private:
    int num; // 分子
    int den; // 分母（保持正数）

    // 约分函数（欧几里得算法）
    void reduce()
    {
        // TODO: 求最大公约数，约分，并确保分母为正
        int a = abs(num);
        int b = abs(den);
        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        num /= a;
        den /= a;
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

public:
    // 构造函数（默认值为 0/1）
    Fraction(int n = 0, int d = 1)
    {
        // TODO: 初始化 num, den，调用 reduce()
        num = n;
        if (d == 0) {
            d = 1;
        }
        den = d;
        reduce();
    }

    // 算术运算符重载（返回新对象）
    Fraction operator+(const Fraction &other) const
    {
        // TODO: 实现分数加法
        Fraction res;
        res.den = den * other.den;
        res.num = den * other.num + other.den * num;
        res.reduce();
        return res;
    }

    Fraction operator-(const Fraction &other) const
    {
        // TODO: 实现分数减法
        Fraction res;
        res.den = den * other.den;
        res.num = other.den * num - den * other.num;
        res.reduce();
        return res;
    }

    Fraction operator*(const Fraction &other) const
    {
        // TODO: 实现分数乘法
        Fraction res;
        res.den = den * other.den;
        res.num = num * other.num;
        res.reduce();
        return res;
    }

    Fraction operator/(const Fraction &other) const
    {
        // TODO: 实现分数除法（假设 other 不为 0）
        Fraction res;
        res.den = den * other.num;
        res.num = num * other.den;
        res.reduce();
        return res;
    }

    // 静态比较函数（三态比较）
    static int compare(const Fraction &a, const Fraction &b)
    {
        // TODO: 交叉相乘比较，返回 -1/0/1
        int left = a.num * b.den;
        int right = b.num * a.den;
        return CompareInt(left, right);
    }

    // 可选：友元输出（用于调试，不强制，但可作为优化加分）
    friend std::ostream &operator<<(std::ostream &os, const Fraction &f)
    {
        // TODO: 输出格式 "num/den"
        os << f.num << "/" << f.den;
        return os;
    }

    // 可选：获取分子/分母（用于自定义比较器，可根据需要添加）
    int getNum() const { return num; }
    int getDen() const { return den; }
};

// 特化 defaultCompare 模板，使得 Sorter<Fraction> 可以直接使用
template <>
int defaultCompare<Fraction>(const Fraction &a, const Fraction &b)
{
    // TODO: 调用 Fraction::compare
    return Fraction::compare(a, b);
}

// 4. 自定义比较器：按分子大小升序
int compareByNumerator(const Fraction &a, const Fraction &b)
{
    // TODO: 返回 -1/0/1，比较 a.getNum() 与 b.getNum()
    return CompareInt(a.getNum(), b.getNum());
}

// ==================== 主函数框架 ====================
int main()
{
    // 1. 创建 Fraction 数组并初始化
    Fraction arr[] = {
        Fraction(1, 2), // 1/2
        Fraction(3, 4), // 3/4
        Fraction(1, 3), // 1/3
        Fraction(2, 1)  // 2/1
    };
    int len = sizeof(arr) / sizeof(arr[0]);

    // 2. 使用 Sorter<Fraction> 排序（默认比较器，按值升序）
    Sorter<Fraction> sorter(arr, len, false); // 引用外部数组
    std::cout << "排序前: ";
    // TODO: 使用重载的 operator<< 输出 sorter（需要先实现输出运算符）
    // 例如: std::cout << sorter << std::endl;
    std::cout << sorter << std::endl;

    sorter.sort(); // 使用默认比较器（特化后的 defaultCompare<Fraction>）
    std::cout << "排序后（按值升序）: ";
    // TODO: 输出 sorter
    std::cout << sorter << std::endl;
    // 3. 测试下标运算符修改元素
    sorter.getData()[0] = Fraction(5, 2); // 将第一个元素改为 5/2
    std::cout << "修改下标0为5/2后: ";
    // TODO: 输出 sorter
    std::cout << sorter << std::endl;
    sorter.sort();
    std::cout << "重新排序后: ";
    // TODO: 输出 sorter
    std::cout << sorter << std::endl;
    // 重新创建一个 Sorter 对象（使用拷贝模式，避免影响原数组）
    Sorter<Fraction> sorter2(arr, len, true);
    std::cout << "\n按分子排序前: ";
    // TODO: 输出 sorter2
    std::cout << sorter2 << std::endl;
    sorter2.sort(compareByNumerator);
    std::cout << "按分子升序排序后: ";
    // TODO: 输出 sorter2
    std::cout << sorter2 << std::endl;

    return 0;
}

// ==================== 优化说明区 ====================
// 请在此列出你实现的优化点（每条一行）：
// 示例：
// - 优化点名称: 下标越界检查
//   档次: 简单(3分)
//   实现情况: 已做且已在代码注释中说明
//
// （学生自行填写）

// - 优化点名称: 快速排序
//   档次: 重大(8分)
//   实现情况: 已做且已在代码注释中说明

// - 优化点名称: 下标越界检查
//   档次: 简单(3分)
//   实现情况: 已做且已在 operator[] 中加入 assert