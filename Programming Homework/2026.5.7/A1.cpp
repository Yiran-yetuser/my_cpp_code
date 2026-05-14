#define _CRT_SECURE_NO_WARNINGS 0
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

// 表示一个样本集的类
class SampleSet
{
private:
    char name[50]; // 样本集别名
    double *data;  // 指向存储样本集数据的数组的指针
    int size;      // 样本集的大小，即 data所指向数组的长度
    int count;     // 样本个数（该值大于等于 0，最大值为 size）
    double ave;    // 样本集的均值

    // 对data数组执行插入排序，升序
    void insertsort(double arr[], int n)
    {
        double temp = arr[0];
        for (int i = 1; i < n; i++) {
            int j = i;
            temp = arr[i];
            for (; j > 0; j--) {
                if (temp < arr[j - 1])
                    arr[j] = arr[j - 1];
                else
                    break;
            }
            arr[j] = temp;
        }
    }

public:
    // 构造函数1，创建一个空样本集
    SampleSet() : size(0), count(0), data(0) {};

    // 构造函数2，根据已有样本数据序列arr，创建样本集
    // 参数len表示数组arr中的样本个数(不超过n)，n表示样本集的大小
    SampleSet(const double *arr, int len, int n)
    {
        // 填写1：完成构造函数，初始化样本集。（10分）
        // 包括：
        // 对size、count 的初始化
        // 根据给定的样本集大小，为data 动态分配内存，并存储样本数据
        // 计算样本集的平均值ave
        if (len > n) {
            cout << "Wrong! count > size" << endl;
        }
        size = n;
        count = len < n ? len : n; // 对size、count 的初始化
        data = new double[size];

        double sum = 0;
        for (int i = 0; i < count; i++) {
            data[i] = arr[i];
            sum += arr[i];
        } // 根据给定的样本集大小，为data 动态分配内存，并存储样本数据
        ave = sum / count;

        insertsort(data, count);
    }

    // 设置样本集的别名
    void SetName(const char *str) { strcpy(name, str); }

    // 获取样本集的别名
    char *GetName() const { return (char *)name; }

    // 获取样本集的平均值
    double GetAve() const { return ave; }

    // 输出样本集的数量及样本数据
    void Print()
    {
        cout << "样本数量为：" << count << endl;
        for (int i = 0; i < count; i++) {
            cout << left << setw(6) << data[i];
            if ((i + 1) % 10 == 0)
                cout << endl;
        }
        if (count % 10)
            cout << endl;
    }

    // 一些重要的成员函数声明
    void ReSize(int newSize);         // 重置样本集的大小，需要扩充样本集时调用
    void Merge(const SampleSet &set); // 合并2个样本集
    double GetMedian();               // 计算当前样本集的中位数
    ~SampleSet();
};

// 当样本集容量不足时，可调用此函数进行扩容
void SampleSet::ReSize(int newSize)
{
    // 填写2：补充完善函数定义（10分）
    // 注意：
    // 只有新的容量大小newSize大于当前样本集大小时才需要进行扩容；
    // 满足扩容条件时，需要按新的容量大小为data重新分配内存空间；
    // 另一方面，扩容后的样本集仍要保留原来的样本数据。
    if (newSize <= size) {
        return;
    }
    double *temp = new double[count];
    for (int i = 0; i < count; i++) {
        temp[i] = data[i];
    }
    delete[] data; // 注意！！！防止内存泄漏！！！
    data = new double[newSize];
    for (int i = 0; i < count; i++) {
        data[i] = temp[i];
    }
    delete[] temp;
}

// 把另一个样本集合并到当前样本集中
void SampleSet::Merge(const SampleSet &set)
{
    // 填写3：根据提示完成函数定义（10分）
    int oriCount = count; // 记录原样本集数据数量

    ReSize(count + set.count); // 扩容

    for (int i = 0; i < set.count; i++) {
        data[i + oriCount] = set.data[i];
    } // 把set的data合并到原样本集data之中

    count += set.count; // count更新

    ave = (ave * oriCount + set.ave * set.count) / count; // ave更新

    insertsort(data, count); // 排序
}

// 计算样本集的中位数
double SampleSet::GetMedian()
{
    // 填写4：根据提示完成函数定义（8分）
    if (count % 2 == 0) {
        return (data[count / 2 - 1] + data[count / 2]) / 2;
    }
    return data[count / 2];
}

SampleSet::~SampleSet()
{
    if (data) {
        delete[] data;
    }
    data = nullptr;
}

int main()
{
    double a[10] = {1.69, 1.54, 1.70, 1.73, 1.60, 1.81, 1.57, 1.72, 1.71, 1.63}; // 一组身高数据
    double b[5] = {1.85, 1.79, 1.72, 1.68, 1.76};                                // 另一组身高数据

    // 填写5：样本集的初始化(4分)
    // 创建一个空的身高样本集:setHeight，设置样本集的别名为“身高样本集”，2分
    // 使用数组a初始化样本集1:set1，样本集大小设为12，1分
    // 使用数组b初始化样本集2:set2，样本集大小设为10，1分
    SampleSet setHeight;
    setHeight.SetName("身高样本集");
    SampleSet set1(a, 10, 12);
    SampleSet set2(b, 5, 10);
    // 显示两个样本集的数据及其均值
    set1.Print();
    cout << "均值：" << set1.GetAve() << endl
         << endl;
    set2.Print();
    cout << "均值：" << set2.GetAve() << endl
         << endl;

    setHeight.Merge(set1);
    setHeight.Merge(set2);
    cout << setHeight.GetName() << endl;
    setHeight.Print();
    cout << "均值：" << setHeight.GetAve() << endl
         << endl;
    cout << "中位数：" << setHeight.GetMedian() << endl
         << endl;

    return 0;
}

// 问答（8分，请在注解中直接作答）
//  1、Merge函数中第一个参数为什么是引用传递？可以改成值传递吗？为什么？
// 因为SampleSet类中使用了数组，使用引用传递传入的是set的地址，传入的指针直接指向set的data集里面。
// 该类没有自定义拷贝构造函数，默认的浅拷贝会使副本的 data 指针与原对象指向同一块内存。
// 函数结束时形参被销毁，析构函数释放 data，会导致原对象中的 data 变成悬空指针，后续使用时出错
// 同时，引用传递减少了拷贝过程的内存开销

// 2、SampleSet类使用了默认的析构函数，请问是否有必要重载？为什么？
// 需要重载，因为类中data使用了动态分配内存，析构时需要手动删除data