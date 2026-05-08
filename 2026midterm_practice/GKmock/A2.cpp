#include <iostream>
using namespace std;

// 完成 FilteredTemperatureSensor 类的定义
// 你的代码开始
class FilteredTemperatureSensor
{
private:
    static const int WINDOW_SIZE = 5; // 滑动窗口大小
    double rawHistory[WINDOW_SIZE];   // 存储最近 WINDOW_SIZE 个原始温度
    int historyIndex;                 // 当前写入位置索引（循环缓冲区）
    int validCount;                   // 已存入的有效读数个数（≤ WINDOW_SIZE）
    double filteredValue;             // 上一次滤波结果（可选，用于快速获取）

public:
    FilteredTemperatureSensor()
    {
        for (int i = 0; i < WINDOW_SIZE; i++) {
            rawHistory[i] = 0.0;
        }
        historyIndex = 0;
        validCount = 0;
        filteredValue = 0.0;
    };
    void setRawTemperature(double raw)
    {
        if (validCount <= 4) {
            rawHistory[historyIndex] = raw;
            historyIndex++;
            validCount++;
        } else {
            for (int i = 0; i < WINDOW_SIZE - 1; i++) {
                rawHistory[i] = rawHistory[i + 1];
            }
            rawHistory[WINDOW_SIZE - 1] = raw;
        }
        double sum = 0;
        for (int i = 0; i <= historyIndex; i++) {
            sum += rawHistory[i];
        }
        filteredValue = sum / validCount;
    };
    double getFilteredTemperature() const
    {
        return filteredValue;
    };
    double getRawTemperature() const
    {
        if (validCount == 0) {
            return 0.0;
        }
        int index = historyIndex == 0 ? WINDOW_SIZE - 1 : historyIndex - 1;
        return rawHistory[index];
    };
    ~FilteredTemperatureSensor()
    {
        // 没有动态分配内存，不需要delete
        cout << "Filtered sensor destroyed." << endl;
    };
};

// 你的代码结束

int main()
{
    FilteredTemperatureSensor sensor;
    double testData[] = {25.1, 25.3, 25.0, 25.8, 25.2, 25.1, 25.4};

    for (int i = 0; i < 7; i++) {
        sensor.setRawTemperature(testData[i]);
        cout << "Raw: " << sensor.getRawTemperature()
             << " -> Filtered: " << sensor.getFilteredTemperature() << endl;
    }
    return 0;
}
// （四）回答问题
// 移动平均滤波的窗口大小 WINDOW_SIZE 对滤波效果和响应速度有何影响？
// 从计算思维的角度分析，如果窗口大小从 5 增大到 50，每次计算滤波值的算法时间复杂度是否会变化？
// 若采用“滑动平均的增量更新”方式（每加入一个新值，仅用简单运算更新平均值），能否具体描述一下该方法的细节？

// 窗口越大，对噪声的消除效果越好，但响应速度越慢，因为需要更多的历史数据来计算平均值。相反，窗口越小，响应速度越快，但对噪声的消除效果较差。
// 从计算思维的角度分析，如果窗口大小从 5 增大到 50，每次计算滤波值的算法时间复杂度不会变化，仍然是 O(1)，因为我们只需要更新一个平均值，而不需要重新计算整个窗口的平均值。
// 采用“滑动平均的增量更新”方式时，我们可以维护一个当前的平均值和一个当前窗口内的总和。
// 当加入一个新值时，我们将新值加入总和，并从总和中减去被移除的旧值，然后更新平均值为总和除以窗口大小。
// 这样，每次更新的时间复杂度为 O(1)，因为我们只进行固定数量的运算，而不需要重新计算整个窗口的平均值。