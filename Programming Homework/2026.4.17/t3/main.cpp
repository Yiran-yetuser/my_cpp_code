#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 函数模板：对数组进行升序排序
template <typename T>
void sortArray(T arr[], int size)
{
    // TODO: 使用 std::sort 对数组进行升序排序
    std::sort(arr, arr + size);
}

// 打印数组的函数模板
template <typename T>
void printArray(T arr[], int size)
{
    // TODO: 遍历数组并输出每个元素，元素之间用空格分隔
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 用户自定义类型：Pair结构体
struct Pair {
    int first;
    int second;

    // 重载 < 运算符，用于排序（按first升序，first相同则按second升序）
    bool operator<(const Pair &other) const
    {
        // TODO: 定义比较规则
        if (first != other.first) {
            return first < other.first;
        }
        return second < other.second;
    }

    // 重载 << 运算符，用于输出
    friend ostream &operator<<(ostream &os, const Pair &p)
    {
        // TODO: 输出格式为 (first, second)
        os << "(" << p.first << ", " << p.second << ")" << endl;
        return os;
    }
};

int main()
{
    // 测试 int 类型数组
    int intArr[] = {5, 2, 9, 1, 5, 6};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    cout << "Before sorting int array: ";
    printArray(intArr, intSize);
    sortArray(intArr, intSize);
    cout << "After sorting int array: ";
    printArray(intArr, intSize);
    cout << endl;

    // 测试 float 类型数组
    float floatArr[] = {3.5, 1.2, 4.7, 2.3};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    cout << "Before sorting float array: ";
    printArray(floatArr, floatSize);
    sortArray(floatArr, floatSize);
    cout << "After sorting float array: ";
    printArray(floatArr, floatSize);
    cout << endl;

    // 测试 Pair 自定义类型数组
    Pair pairArr[] = {{5, 2}, {1, 9}, {3, 7}, {4, 6}};
    int pairSize = sizeof(pairArr) / sizeof(pairArr[0]);
    cout << "Before sorting Pair array: ";
    printArray(pairArr, pairSize);
    sortArray(pairArr, pairSize);
    cout << "After sorting Pair array: ";
    printArray(pairArr, pairSize);

    return 0;
}
