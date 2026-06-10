#include <cmath> // 可选
#include <iostream>

// ==================== 问题回答区 ====================
// 问题：
// 1. 为什么将 sort 函数设计为纯虚函数？这样做有什么好处？
// 2. 在本设计中，基类 Sorter<T> 的拷贝构造函数和赋值运算符是深拷贝的。
//    如果派生类新增了成员变量，应该如何处理拷贝控制？请简要说明。
// 3. 假设你想在运行时根据数据规模自动选择排序算法
//    （例如小数组用插入排序，大数组用快速排序）。在不修改已有类的前提下，
//    请给出一种设计方案（不需要写代码，描述思路即可）。
//
// 回答（请在此处填写）：

// ==================== 第一部分：修改后的 Sorter<T> 抽象基类 ================
// 请将你第二弹中完成的 Sorter<T> 和完整代码复制到此处，并做以下修改：
//   1. 将 sort 方法声明改为纯虚函数
//   2. 移除原有的 sort 函数实现（函数体）。
//   3. 在 protected 区域添加方法：T* getDataPtr() const { return data; } 和 i nt getSize() const { return size; }
//   4. 保留所有其他成员（data, size, owned, 构造/析构/拷贝/赋值/下标/输出）。
// 注意：不要重复定义全局比较函数（CompareInt, CompareDouble, defaultCompare 等），它们已经在第一弹中定义过。

// 此处复制你的 Sorter<T> 代码（略）
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

    // // 私有快速排序函数
    // void quickSort(int low, int high, int (*cmp)(const T &, const T &))
    // {
    //     if (low >= high) {
    //         return;
    //     }

    //     T pivot = data[high];
    //     int i = low - 1;
    //     for (int j = low; j < high; ++j) {
    //         if (cmp(data[j], pivot) < 0) {
    //             i++;
    //             T tmp = data[i];
    //             data[i] = data[j];
    //             data[j] = tmp;
    //         }
    //     }
    //     T tmp = data[i + 1];
    //     data[i + 1] = data[high];
    //     data[high] = tmp;

    //     int pi = i + 1;
    //     quickSort(low, pi - 1, cmp);
    //     quickSort(pi + 1, high, cmp);
    // }

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
    virtual void sort(int (*cmp)(const T &, const T &) = 0) = 0;

    // 访问器
    T *getDataPtr() const { return data; }
    int getSize() const { return size; }
};

// 请将你第二弹中完成的Fraction类和完整代码复制到此处

// 此处复制你的 Fraction代码（略）
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

// ==================== 第二部分：派生类实现不同的排序算法 ===================
// 每个派生类必须：
//   - 继承自 Sorter<T>
//   - 实现 sort 方法
//   - 可以添加自己的辅助函数（如 swap 等）
// 学生至少需要实现两种不同的 O(n²) 排序算法（如冒泡、插入、选择等）。
// 以下给出两个示例框架。

// 冒泡排序器（O(n²)）
template <typename T>
class BubbleSorter : public Sorter<T>
{
public:
    // 继承基类的构造函数（C++98 需要手动声明）
    BubbleSorter(T *externalArr, int len, bool copyData = false)
        : Sorter<T>(externalArr, len, copyData)
    {
    }
    virtual void sort(int (*cmp)(const T &, const T &) = 0)
    {
        // TODO: 实现冒泡排序，使用比较器 cmp（若为 0 则用 defaultCompare<T>）
        // 注意：通过 this->getDataPtr() 和 this->getSize() 访问数据
        if (this->getSize() <= 0)
            return;
        auto comparator = cmp ? cmp : defaultCompare<T>;
        for (int i = 0; i < this->getSize() - 1; i++) {
            for (int j = 0; j < this->getSize() - 1 - i; j++) {
                if (comparator(this->getDataPtr()[j], this->getDataPtr()[j + 1]) > 0) {
                    // 交换
                    T temp = this->getDataPtr()[j];
                    this->getDataPtr()[j] = this->getDataPtr()[j + 1];
                    this->getDataPtr()[j + 1] = temp;
                }
            }
        }
    }
};

// 插入排序器（O(n²)）
template <typename T>
class InsertionSorter : public Sorter<T>
{
public:
    InsertionSorter(T *externalArr, int len, bool copyData = false)
        : Sorter<T>(externalArr, len, copyData) {}
    virtual void sort(int (*cmp)(const T &, const T &) = 0)
    {
        // TODO: 实现插入排序
        if (this->getSize() <= 0)
            return;
        auto comparator = cmp ? cmp : defaultCompare<T>;
        for (int i = 1; i < this->getSize(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (comparator(this->getDataPtr()[j], this->getDataPtr()[i]) > 0) {
                    T temp = this->getDataPtr()[i];
                    for (int idx = i - 1; idx >= j + 1; idx--) {
                        this->getDataPtr()[idx] = this->getDataPtr()[idx - 1];
                    }
                    this->getDataPtr()[j] = temp;
                }
            }
        }
    }
};

// 如果你实现更多排序器（如选择排序、快速排序、归并排序、希尔排序等等），可以继续添加，并作为优化。

// ==================== 第三部分：主函数测试 ====================
int main()
{
    // 准备数据（int 数组和 Fraction 数组）
    int intArr[] = {5, 2, 8, 1, 9, 3};
    int lenInt = sizeof(intArr) / sizeof(intArr[0]);
    // 假设 Fraction 类已在第二弹中定义，此处可以直接使用
    Fraction fracArr[] = {Fraction(1, 2), Fraction(3, 4), Fraction(1, 3), Fract ion(2, 1)};
    int lenFrac = sizeof(fracArr) / sizeof(fracArr[0]);

    // 1. 使用 BubbleSorter 对 int 数组排序（引用模式）
    BubbleSorter<int> bubbleSorter(intArr, lenInt, false);
    std::cout << "冒泡排序前: " << bubbleSorter << std::endl;
    bubbleSorter.sort(CompareInt);
    std::cout << "冒泡排序后: " << bubbleSorter << std::endl;

    // 2. 使用 InsertionSorter 对 Fraction 数组排序（拷贝模式，不修改原数组）
    InsertionSorter<Fraction> insertionSorter(fracArr, lenFrac, true);
    std::cout << "\n插入排序前: " << insertionSorter << std::endl;
    insertionSorter.sort(); // 使用默认比较器（Fraction::compare）     std::cout << "插入排序后（按值）: " << insertionSorter << std::endl;

    // 3. 多态演示：基类指针指向派生类对象
    Sorter<int> *sorter = new BubbleSorter<int>(intArr, lenInt, false);
    std::cout << "\n多态调用冒泡排序: " << *sorter << std::endl;
    sorter->sort(CompareInt);
    std::cout << "排序后: " << *sorter << std::endl;
    delete sorter;

    // 4. 如果你实现了第三种排序算法，可以在这里测试
    // ...      return 0;
}

// ==================== 优化说明区 ====================
// 请在此列出你实现的优化点（每条一行）：
// - 优化点名称:
//   档次: 简单(3分)/一般(5分)/重大(8分)
//   实现情况: 已做且已在代码注释中说明
//
// （学生自行填写）
