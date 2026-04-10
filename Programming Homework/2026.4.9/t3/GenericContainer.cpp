#define _CRT_SECURE_NO_WARNINGS 0

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class GenericContainer
{
private:
    vector<T> elems; // 用vector存储元素
public:
    GenericContainer(/* args */);
    ~GenericContainer();

    // 向容器中添加一个元素
    void addElement(const T &element);

    // 返回容器中元素的数量
    size_t size() const;

    // 清空容器中的所有元素
    void clear();

    // 打印容器中的所有元素
    void printContainer() const;

    // 对容器中的元素进行排序（使用默认排序规则）
    void sort();
};

template <class T>
GenericContainer<T>::GenericContainer(/* args */)
{
}

template <class T>
GenericContainer<T>::~GenericContainer()
{
}

// 向容器中添加一个元素
template <class T>
void GenericContainer<T>::addElement(const T &element)
{
    elems.push_back(element);
}

// 返回容器中元素的数量
template <class T>
size_t GenericContainer<T>::size() const
{
    return elems.size();
}

// 清空容器中的所有元素
template <class T>
void GenericContainer<T>::clear()
{
    elems.clear();
}

// 打印容器中的所有元素
template <class T>
void GenericContainer<T>::printContainer() const
{
    cout << "Container elements: ";
    for (const auto &elem : elems) {
        cout << elem << " ";
    }
    cout << endl;
}

// 对容器中的元素进行排序（使用默认排序规则）
template <class T>
void GenericContainer<T>::sort()
{
    std::sort(elems.begin(), elems.end());
}

// 用户自定义类型：Pair 结构体
struct Pair {
    int first;
    int second;

    // 为了支持打印使用ostream重载 << 运算符
    friend ostream &operator<<(ostream &os, const Pair &p)
    {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }

    // 为了支持默认排序，重载 < 运算符
    bool operator<(const Pair &other) const
    {
        if (first != other.first) {
            return first < other.first;
        }
        return second < other.second;
    }
};

// 主函数测试用例
int main()
{
    // 测试 int 类型的容器
    cout << "=== Testing int container ===" << endl;
    GenericContainer<int> intContainer;
    intContainer.addElement(5);
    intContainer.addElement(1);
    intContainer.addElement(3);
    intContainer.addElement(2);
    intContainer.addElement(4);
    cout << "Size: " << intContainer.size() << endl;
    intContainer.printContainer();

    // 排序并打印
    intContainer.sort();
    cout << "After sorting: " << endl;
    intContainer.printContainer();
    cout << endl;

    // 测试 string 类型的容器
    cout << "=== Testing string container ===" << endl;
    GenericContainer<string> stringContainer;
    stringContainer.addElement("banana");
    stringContainer.addElement("apple");
    stringContainer.addElement("orange");
    stringContainer.addElement("grape");
    cout << "Size: " << stringContainer.size() << endl;
    stringContainer.printContainer();

    // 排序并打印
    stringContainer.sort();
    cout << "After sorting: " << endl;
    stringContainer.printContainer();
    cout << endl;

    // 测试 Pair 类型的容器
    cout << "=== Testing Pair container ===" << endl;
    GenericContainer<Pair> pairContainer;
    pairContainer.addElement({3, 2});
    pairContainer.addElement({1, 5});
    pairContainer.addElement({2, 1});
    pairContainer.addElement({1, 3});
    cout << "Size: " << pairContainer.size() << endl;
    pairContainer.printContainer();

    // 排序并打印（使用默认排序规则）
    pairContainer.sort();
    cout << "After sorting (default): " << endl;
    pairContainer.printContainer();

    // 清空容器并测试
    pairContainer.clear();
    cout << "After clear, size: " << pairContainer.size() << endl;
    pairContainer.printContainer();

    return 0;
}
