#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
using namespace std;

// 通用容器类模板（C风格原生数组实现）
template <typename T>
class GenericContainer
{
private:
    T *arr;       // 动态数组
    int capacity; // 容量
    int count;    // 当前元素数量

public:
    // 构造函数
    GenericContainer(T *array = nullptr, int capacity = 0, int count = 0)
    {

        arr = new T[capacity];
        this->capacity = capacity;
        this->count = count;
        if (this->capacity < this->count || this->count < 0 || this->capacity < 0) {
            cout << "Invalid capacity or count" << endl;
            exit(1);
        }
        memcpy(arr, array, sizeof(T) * count); // 使用 memcpy 进行深拷贝
    }

    // 析构函数
    ~GenericContainer()
    {
        // TODO: 释放 data
        if (arr) {
            delete[] arr;
        }
        arr = nullptr;
    }

    // 拷贝构造函数
    GenericContainer(const GenericContainer &other)
    {
        // TODO: 深拷贝
        arr = new T[other.capacity];
        capacity = other.capacity;
        count = other.count;
        memcpy(arr, other.arr, sizeof(T) * other.count); // 使用 memcpy 进行深拷贝
    }

    // 向容器中添加一个元素
    void addElement(const T &element)
    {
        // TODO: 如果满了先扩容，然后将element添加到数组末尾
        if (count == capacity) {
            T *newArr = new T[capacity + 1];
            memcpy(newArr, arr, sizeof(T) * count);
            newArr[count] = element;
            delete[] arr;
            arr = newArr;
            capacity++;
            count++;
        }
    }

    // 从容器中删除一个元素（删除第一个匹配的）
    void removeElement(const T &element)
    {
        // TODO: 遍历数组找到匹配元素，将后面的元素前移，count减1
        for (int i = 0; i < count; i++) {
            if (arr[i] == element) {
                for (int j = i; j < count - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                count--;
                break;
            }
        }
    }

    // 返回容器中元素的数量
    int size() const
    {
        // TODO: 返回 count
        return count;
    }

    // 清空容器中的所有元素
    void clear()
    {
        // TODO: 将 count 置为 0
        count = 0;
        memset(arr, 0, sizeof(T) * capacity);
    }

    // 对容器中的元素进行排序
    void sort(const function<bool(const T &, const T &)> &compareFunc = nullptr)
    {
        // TODO: 如果compareFunc不为空，使用compareFunc排序
        // 否则使用默认的 < 运算符排序
        // 使用 std::sort(data, data + count, ...)
        if (compareFunc) {
            std::sort(arr, arr + count, compareFunc);
        } else {
            std::sort(arr, arr + count);
        }
    }

    // 打印容器中的所有元素
    void printContainer() const
    {
        // TODO: 遍历数组并输出每个元素，元素之间用空格分隔
        for (int i = 0; i < count; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // 支持范围for循环：返回起始指针
    T *begin()
    {
        // TODO: 返回 arr
        return arr;
    }

    T *end()
    {
        // TODO: 返回 arr + count
        return arr + count;
    }

    const T *begin() const
    {
        // TODO: 返回 data
        return arr;
    }

    const T *end() const
    {
        // TODO: 返回 arr + count
        return arr + count;
    }
};

// 用户自定义类型：Pair结构体
struct Pair {
    int first;
    int second;

    // 重载 == 运算符
    bool operator==(const Pair &other) const
    {
        // TODO: 比较两个Pair是否相等
        return first == other.first && second == other.second;
    }

    // 重载 < 运算符
    bool operator<(const Pair &other) const
    {
        // TODO: 先按first升序，first相同则按second升序
        return first < other.first || (first == other.first && second < other.second);
    }

    // 重载 << 运算符
    friend ostream &operator<<(ostream &os, const Pair &p)
    {
        // TODO: 输出格式为 (first, second)
        return os << "(" << p.first << ", " << p.second << ")";
    }
};

int main()
{
    // 测试 int 类型容器
    cout << "Testing GenericContainer with int type:" << endl;
    GenericContainer<int> intContainer;
    intContainer.addElement(3);
    intContainer.addElement(1);
    intContainer.addElement(4);
    intContainer.addElement(1);
    intContainer.addElement(5);
    cout << "Before sorting: ";
    intContainer.printContainer();
    intContainer.sort();
    cout << "After sorting: ";
    intContainer.printContainer();
    intContainer.removeElement(1);
    cout << "After removing one '1': ";
    intContainer.printContainer();
    intContainer.clear();
    cout << "After clearing: ";
    intContainer.printContainer();
    cout << endl;

    // 测试 string 类型容器
    cout << "Testing GenericContainer with string type:" << endl;
    GenericContainer<string> strContainer;
    strContainer.addElement("apple");
    strContainer.addElement("banana");
    strContainer.addElement("cherry");
    strContainer.addElement("date");
    strContainer.addElement("fig");
    cout << "Before sorting: ";
    strContainer.printContainer();
    strContainer.sort();
    cout << "After sorting: ";
    strContainer.printContainer();
    strContainer.removeElement("banana");
    cout << "After removing one 'banana': ";
    strContainer.printContainer();
    strContainer.clear();
    cout << "After clearing: ";
    strContainer.printContainer();
    cout << endl;

    // 测试 Pair 自定义类型容器
    cout << "Testing GenericContainer with Pair type:" << endl;
    GenericContainer<Pair> pairContainer;
    pairContainer.addElement({3, 2});
    pairContainer.addElement({1, 9});
    pairContainer.addElement({3, 7});
    pairContainer.addElement({4, 6});
    pairContainer.addElement({3, 8});
    cout << "Before sorting: ";
    pairContainer.printContainer();
    pairContainer.sort([](const Pair &a, const Pair &b) {
        if (a.first != b.first)
            return a.first < b.first;
        return a.second < b.second;
    });
    cout << "After sorting: ";
    pairContainer.printContainer();
    pairContainer.removeElement({3, 7});
    cout << "After removing one '(3, 7)': ";
    pairContainer.printContainer();
    pairContainer.clear();
    cout << "After clearing: ";
    pairContainer.printContainer();

    return 0;
}
