#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 通用容器类模板
template <typename T>
class GenericContainer
{
private:
    vector<T> elements;

public:
    // 构造函数
    GenericContainer() {}

    // 析构函数
    ~GenericContainer() {}

    // 向容器中添加一个元素
    void addElement(const T &element)
    {
        // TODO: 将element添加到elements中
        elements.push_back(element);
    }

    // 从容器中删除一个元素（如果存在）
    void removeElement(const T &element)
    {
        // TODO: 遍历elements，找到第一个匹配的元素并删除
        auto it = find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }

    // 返回容器中元素的数量
    int size() const
    {
        // TODO: 返回elements的大小
        return elements.size();
    }

    // 清空容器中的所有元素
    void clear()
    {
        // TODO: 清空elements
        elements.clear();
    }

    // 对容器中的元素进行排序
    // 如果提供了自定义比较函数则使用该函数，否则使用默认升序排序
    void sort(const function<bool(const T &, const T &)> &compareFunc = nullptr)
    {
        // TODO: 如果compareFunc不为空，使用compareFunc排序
        // 否则使用默认的 < 运算符排序
        if (compareFunc) {
            std::sort(elements.begin(), elements.end(), compareFunc);
        } else {
            std::sort(elements.begin(), elements.end());
        }
    }

    // 打印容器中的所有元素
    void printContainer() const
    {
        // TODO: 遍历elements并输出每个元素，元素之间用空格分隔
        for (int i = 0; i < elements.size(); i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

    // 支持范围for循环：返回起始迭代器
    typename vector<T>::iterator begin()
    {
        // TODO: 返回elements的begin迭代器
        return elements.begin();
    }

    // 支持范围for循环：返回结束迭代器
    typename vector<T>::iterator end()
    {
        // TODO: 返回elements的end迭代器
        return elements.end();
    }

    // const版本的迭代器
    typename vector<T>::const_iterator begin() const
    {
        // TODO: 返回elements的cbegin迭代器
        return elements.cbegin();
    }

    typename vector<T>::const_iterator end() const
    {
        // TODO: 返回elements的cend迭代器
        return elements.cend();
    }
};

// 用户自定义类型：Pair结构体
struct Pair {
    int first;
    int second;

    // 重载 == 运算符，用于removeElement中的比较
    bool operator==(const Pair &other) const
    {
        return first == other.first && second == other.second;
    }

    // 重载 < 运算符，用于默认排序
    bool operator<(const Pair &other) const
    {
        if (first != other.first)
            return first < other.first;
        return second < other.second;
    }

    // 重载 << 运算符，用于输出
    friend ostream &operator<<(ostream &os, const Pair &p)
    {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
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
    // 自定义比较函数：先按first升序，first相同则按second升序
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
