#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
#define PI 3.1415926535897

// 存储集合的类
class Collection
{
    int *data;    // 指向存储集合中数据的数组的指针
    int capacity; // 集合的容量，即 data 指向的数组的长度
    int count;    // 集合中有效数据的个数（ 大于等于 0，且最大为 capacity）
public:
    Collection(int capacity = 100) // 构造函数，初始化集合。参数 capacity 指定了集合内存数组的大小，默认 100
    {
        // 填写1： 完成构造函数（5分）
        //  即
        //  对 data 内存的申请，
        //  以及对 this->capacity、this->count 的初始化
        //  由于一开始集合是空的，this->count 一开始应为 0
        data = new int[capacity];
        this->capacity = capacity;
        this->count = 0;
    }

    ~Collection() // 析构函数
    {
        delete[] data;
    }

    void SetCapacity(int newCapacity) //  重新申请长度为newCapacity的动态空间
    {
        // 填写2：当容量不足时，调用此函数重新定义容量（10分）
        // 主要要将原来的 data 删除，并保留原来的数据

        if (newCapacity <= capacity) {
            return;
        }
        int *temp = new int[count]; // 注意防止内存泄漏！！！
        for (int i = 0; i < count; i++) {
            temp[i] = data[i];
        }
        delete[] data; // 删除原data
        capacity = newCapacity;
        data = new int[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = temp[i];
        }
        delete[] temp;
    }

    void Print(void) const
    {
        for (int i = 0; i < count; i++)
            cout << data[i] << "  ";
        cout << endl;
    }

    // 设置集合中的第 index 个数据
    void SetValue(int index, int value) { data[index] = value; }

    // 向集合中添加一个数据
    void Add(int value)
    {
        if (count < capacity)
            data[count++] = value;
    }

    // 删除集合中的第 index 个数字
    void RemoveAt(int index)
    {
        if (index < 0)
            return;
        if (index >= count)
            return;

        for (int i = index + 1; i < count; ++i)
            data[i - 1] = data[i];

        count--;
    }

    // 获得集合中第 index 个数据
    int GetValue(int index) const { return data[index]; }

    // 返回集合中有效数据的个数
    int GetCount() const { return count; }

    // 返回集合的容量
    int GetCapacity() const { return capacity; }

    friend void Union(Collection &a, const Collection &b);     //  并两个集合，存入 a 中
    friend void Intersect(Collection &a, const Collection &b); //  交两个集合，存入 a 中
};

void Union(Collection &a, const Collection &b) //  并两个集合，存入 a 中
{
    // 填写3：a、b 合并到 a （15 分）
    // 注意：
    //  1. 注意检查 a 的容量，可能需要扩容
    //  2. 消除重复的数字

    a.SetCapacity(a.count + b.count);
    for (int i = 0; i < b.count; i++) {
        int value = b.GetValue(i);
        bool exists = false;
        for (int j = 0; j < a.count; j++) {
            if (a.GetValue(j) == value) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            a.Add(value);
        }
    }
}

void Intersect(Collection &a, const Collection &b) //  交两个集合，存入 a 中
{
    // 填写4：a、b 相交到 a （10 分）
    for (int i = 0; i < a.count; i++) {
        int value = a.GetValue(i);
        bool exists = false;
        for (int j = 0; j < b.count; j++) {
            if (b.GetValue(j) == value) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            a.RemoveAt(i);
            i--; // 调整索引
        }
    }
}

int main()
{
    // TEST A:
    {
        Collection a(5); // 容量为 5
        Collection b(5); // 容量为 5
        a.Add(5);
        a.Add(7);
        a.Add(3);
        a.Add(1);
        b.Add(2);
        b.Add(1);
        b.Add(3);
        b.Add(9);

        Union(a, b);

        cout << "合并后的 a：";
        a.Print();
    }

    // TEST B:
    {
        Collection a(5); // 容量为 5
        Collection b(5); // 容量为 5
        a.Add(5);
        a.Add(7);
        a.Add(3);
        a.Add(1);
        b.Add(2);
        b.Add(1);
        b.Add(3);
        b.Add(9);

        Intersect(a, b);

        cout << "相交后的 a：";
        a.Print();
    }

    return 0;
}

// 问：(10分！）
//  friend void Union(Collection& A, const Collection& b);
//  函数中第一个参数为什么是引用传递？可以改成值传递吗？为什么？
// 答：第一个参数是引用传递的，因为我们需要修改集合 A 的内容。
// 如果改成值传递，那么函数内部对 A 的修改将不会影响到外部的 A，因为值传递会创建一个 A 的副本，函数内部修改的是这个副本，而不是原来的 A。
// 同时，会导致悬空指针问题
