#include <cmath> // 可选，仅为容差优化时使用
#include <iostream>

// ------------------- 问题回答区域 -------------------
// 问题：请在此处回答上述三个子问题（用中文，不超过150字）
/*
    // 问题（回答）：
    1. 不会。构造时owned=false，析构仅当owned为true才释放，故不释放外部数组。
    2. 浅拷贝导致两个对象共享同一内存。若其一析构释放，另一个成悬空指针；
       重复释放也会崩溃。深拷贝避免共享，确保各自独立。
    3. 空指针作默认值，若不传比较器，自动退用defaultCompare实现通用升序；
       传入自定义函数可实现降序等，兼顾简便性与灵活性。
*/

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
        if (low >= high)
            return;

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

// ------------------- 主函数（测试代码） -------------------
int main()
{
    // 1. 测试 int 引用模式（外部数组被修改）
    int intArr[] = {5, 2, 8, 1, 9};
    int lenInt = sizeof(intArr) / sizeof(intArr[0]);
    std::cout << "原始 int 数组: ";
    printArray(intArr, lenInt);

    Sorter<int> sorterRef(intArr, lenInt, false);
    sorterRef.sort(CompareInt);
    std::cout << "排序后原数组: ";
    printArray(intArr, lenInt);

    // 2. 测试 double 拷贝模式（外部数组不变）
    double dblArr[] = {3.2, 1.0, 1.000000001, 2.5};
    int lenDbl = sizeof(dblArr) / sizeof(dblArr[0]);
    std::cout << "\n原始 double 数组: ";
    printArray(dblArr, lenDbl);

    Sorter<double> sorterCopy(dblArr, lenDbl, true);
    sorterCopy.sort(CompareDouble);
    std::cout << "内部排序后: ";
    printArray(sorterCopy.getData(), sorterCopy.getSize());
    std::cout << "外部数组不变: ";
    printArray(dblArr, lenDbl);

    Sorter<int> sorterDesc(intArr, lenInt, false);
    sorterDesc.sort(descendingInt);
    std::cout << "\nint 数组降序: ";
    printArray(intArr, lenInt);

    return 0;
}
