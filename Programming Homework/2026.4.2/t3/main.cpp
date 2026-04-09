// 设计一个函数模板 sortArray，该函数模板能够对任意类型的数组进行排序。你可以
// 使用C++标准库中的排序算法（如 std::sort）来实现这个功能。同时，请编写一个主
// 函数来测试你的模板函数，测试类型包括 int、float 和用户自定义的类型（如一个包含
// 两个整数字段的结构体）。
// 具体要求：
// 1. 定义一个函数模板 sortArray，它接受一个数组和数组的大小作为参数，对数组
// 进行升序排序。
// 2. 在主函数中，定义并初始化三个不同类型的数组：int 类型数组、float 类型数
// 组和一个用户自定义的结构体数组。结构体可以命名为 Pair，包含两个 int 类
// 型的成员变量 first 和 second。
// 3. 对每个数组调用 sortArray 函数进行排序。
// 4. 在排序前后打印每个数组的内容，以验证排序是否正确。
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void sortArray(T *arr, int size)
{
    std::sort(arr, arr + size);
}

struct Pair {
    int first;
    int second;
};

template <>
void sortArray<Pair>(Pair *arr, int size)
{
    std::sort(arr, arr + size, [](const Pair &a, const Pair &b) {
        return a.first < b.first;
    });
}

int main()
{
    // 测试 int 类型数组
    int intArr[] = {5, 2, 9, 1, 5};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    cout << "Before sorting int array: ";
    for (int i = 0; i < intSize; i++) {
        cout << intArr[i] << " ";
    }
    cout << endl;
    sortArray(intArr, intSize);
    cout << "After sorting int array: ";
    for (int i = 0; i < intSize; i++) {
        cout << intArr[i] << " ";
    }
    cout << endl;

    // 测试 float 类型数组
    float floatArr[] = {3.5f, 2.1f, 4.6f, 1.0f};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    cout << "Before sorting float array: ";
    for (int i = 0; i < floatSize; i++) {
        cout << floatArr[i] << " ";
    }
    cout << endl;
    sortArray(floatArr, floatSize);
    cout << "After sorting float array: ";
    for (int i = 0; i < floatSize; i++) {
        cout << floatArr[i] << " ";
    }
    cout << endl;

    // 测试用户自定义的结构体数组
    Pair pairArr[] = {{3, 4}, {1, 2}, {2, 3}};
    int pairSize = sizeof(pairArr) / sizeof(pairArr[0]);
    cout << "Before sorting Pair array: ";
    for (int i = 0; i < pairSize; i++) {
        cout << "(" << pairArr[i].first << ", " << pairArr[i].second << ") ";
    }
    cout << endl;
    sortArray(pairArr, pairSize);
    cout << "After sorting Pair array: ";
    for (int i = 0; i < pairSize; i++) {
        cout << "(" << pairArr[i].first << ", " << pairArr[i].second << ") ";
    }
    cout << endl;

    return 0;
}