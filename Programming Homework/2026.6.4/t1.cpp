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
// 1. 实现多态，可以根据对象的实际类型调用对应的排序算法，增强灵活性和可扩展性。
// 2. 派生类需要定义自己的拷贝构造函数和赋值运算符，调用基类的对应函数来处理基类成员，并处理新增成员的拷贝/赋值逻辑。
// 3. 可以在主函数或工厂函数中根据数据规模创建不同的 Sorter 派生类对象（如 BubbleSorter、InsertionSorter、QuickSorter），
// 并通过基类指针调用 sort 方法实现自动选择排序算法。

// ==================== 第一部分：修改后的 Sorter<T> 抽象基类 ================
// 请将你第二弹中完成的 Sorter<T> 和完整代码复制到此处，并做以下修改：
//   1. 将 sort 方法声明改为纯虚函数
//   2. 移除原有的 sort 函数实现（函数体）。
//   3. 在 protected 区域添加方法：T* getDataPtr() const { return data; } 和 int getSize() const { return size; }
//   4. 保留所有其他成员（data, size, owned, 构造/析构/拷贝/赋值/下标/输出）。
// 注意：不要重复定义全局比较函数（CompareInt, CompareDouble, defaultCompare 等），它们已经在第一弹中定义过。

// 此处复制你的 Sorter<T> 代码（略）
// ------------------- Sorter 类 -------------------

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

protected:
    T *getDataPtr() const { return data; }
    int getSize() const { return size; }

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
    virtual ~Sorter() // 将析构函数设为虚函数，防止派生类对象通过基类指针删除时发生资源泄漏
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
    friend bool operator<(const Fraction &a, const Fraction &b)
    {
        return Fraction::compare(a, b) < 0;
    }
    friend bool operator>(const Fraction &a, const Fraction &b)
    {
        return Fraction::compare(a, b) > 0;
    }
    // 可选：获取分子/分母（用于自定义比较器，可根据需要添加）
    int getNum() const { return num; }
    int getDen() const { return den; }
};
template <>
int defaultCompare<Fraction>(const Fraction &a, const Fraction &b)
{
    return Fraction::compare(a, b);
}
// 4. 自定义比较器：按分子大小升序
int compareByNumerator(const Fraction &a, const Fraction &b)
{
    // TODO: 返回 -1/0/1，比较 a.getNum() 与 b.getNum()
    return CompareInt(a.getNum(), b.getNum());
}

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
    virtual void sort(int (*cmp)(const T &, const T &) = 0) override
    {
        if (this->getSize() <= 0)
            return;
        auto comparator = cmp ? cmp : defaultCompare<T>;
        for (int i = 1; i < this->getSize(); i++) {
            T key = this->getDataPtr()[i];
            int j = i - 1;
            while (j >= 0 && comparator(key, this->getDataPtr()[j]) < 0) {
                this->getDataPtr()[j + 1] = this->getDataPtr()[j];
                j--;
            }
            this->getDataPtr()[j + 1] = key;
        }
    }
};

// 如果你实现更多排序器（如选择排序、快速排序、归并排序、希尔排序等等），可以继续添加，并作为优化。

// 快速排序器（O(n log n)） - 作为重大优化
template <typename T>
class QuickSorter : public Sorter<T>
{
private:
    void quickSort(int low, int high, int (*cmp)(const T &, const T &))
    {
        if (low >= high) {
            return;
        }

        T pivot = this->getDataPtr()[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (cmp(this->getDataPtr()[j], pivot) < 0) {
                i++;
                T tmp = this->getDataPtr()[i];
                this->getDataPtr()[i] = this->getDataPtr()[j];
                this->getDataPtr()[j] = tmp;
            }
        }
        T tmp = this->getDataPtr()[i + 1];
        this->getDataPtr()[i + 1] = this->getDataPtr()[high];
        this->getDataPtr()[high] = tmp;

        int pi = i + 1;
        quickSort(low, pi - 1, cmp);
        quickSort(pi + 1, high, cmp);
    }

public:
    QuickSorter(T *externalArr, int len, bool copyData = false)
        : Sorter<T>(externalArr, len, copyData) {}
    virtual void sort(int (*cmp)(const T &, const T &) = 0) override
    {
        if (this->getSize() <= 0)
            return;
        auto comparator = cmp ? cmp : defaultCompare<T>;
        quickSort(0, this->getSize() - 1, comparator);
    }
};

// ==================== 第三部分：主函数测试 ====================
int main()
{
    // 准备数据（int 数组和 Fraction 数组）
    int intArr[] = {5, 2, 8, 1, 9, 3};
    int lenInt = sizeof(intArr) / sizeof(intArr[0]);
    // 假设 Fraction 类已在第二弹中定义，此处可以直接使用
    Fraction fracArr[] = {Fraction(1, 2), Fraction(3, 4), Fraction(1, 3), Fraction(2, 1)};
    int lenFrac = sizeof(fracArr) / sizeof(fracArr[0]);

    // 1. 使用 BubbleSorter 对 int 数组排序（引用模式）
    BubbleSorter<int> bubbleSorter(intArr, lenInt, false);
    std::cout << "冒泡排序前: " << bubbleSorter << std::endl;
    bubbleSorter.sort(CompareInt);
    std::cout << "冒泡排序后: " << bubbleSorter << std::endl;

    // 2. 使用 InsertionSorter 对 Fraction 数组排序（拷贝模式，不修改原数组）
    InsertionSorter<Fraction> insertionSorter(fracArr, lenFrac, true);
    std::cout << "\n插入排序前: " << insertionSorter << std::endl;
    insertionSorter.sort(); // 使用默认比较器（Fraction::compare）
    std::cout << "插入排序后（按值）: " << insertionSorter << std::endl;
    std::cout << "原 Fraction 数组未修改: [";
    for (int i = 0; i < lenFrac; i++) {
        std::cout << fracArr[i];
        if (i < lenFrac - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    // 3. 多态演示：基类指针指向派生类对象
    Sorter<int> *sorter = new BubbleSorter<int>(intArr, lenInt, false);
    std::cout << "\n多态调用冒泡排序: " << *sorter << std::endl;
    sorter->sort(CompareInt);
    std::cout << "排序后: " << *sorter << std::endl;
    delete sorter;

    // 4. 如果你实现了第三种排序算法，可以在这里测试
    // ...      return 0;

    // 测试快速排序
    QuickSorter<Fraction> quickSorter(fracArr, lenFrac, true);
    std::cout << "\n快速排序前: " << quickSorter << std::endl;
    quickSorter.sort(); // 使用默认比较器（Fraction::compare）
    std::cout << "\n快速排序后（按值）: " << quickSorter << std::endl;

    QuickSorter<Fraction> numSorter(fracArr, lenFrac, true);
    numSorter.sort(compareByNumerator);
    std::cout << "按分子排序: " << numSorter << std::endl;
}

// ==================== 优化说明区 ====================
// 请在此列出你实现的优化点（每条一行）：
// - 优化点名称:
//   档次: 简单(3分)/一般(5分)/重大(8分)
//   实现情况: 已做且已在代码注释中说明
//
// （学生自行填写）
// 1. 实现了快速排序算法，作为冒泡和插入排序的重大优化（8分）
// 2. 在 Sorter 类中使用了拷贝交换惯用法实现赋值运算符，简化代码并提高异常安全性（5分）
// 3. 在构造函数中处理了 len <= 0 的情况，避免不必要的内存分配（3分）
// 4. 在析构函数中释放内存后将指针置为 nullptr，防止悬空指针（3分）
