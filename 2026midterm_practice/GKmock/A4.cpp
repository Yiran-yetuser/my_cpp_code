#include <iostream>
using namespace std;

// 完成 BatteryPack 类的定义
// 需自行定义静态常量 BALANCE_THRESHOLD 和 BALANCE_STEP
// 你的代码开始
class BatteryPack
{
    static const int MAX_CELLS = 12;

private:
    int cellCount;                         // 实际电芯数量（≤12）
    double cellVoltages[MAX_CELLS];        // 电压值数组
    bool balancing[MAX_CELLS];             // 均衡开启标志
    static const double BALANCE_THRESHOLD; // 均衡启动压差阈值 0.02V
    static const double BALANCE_STEP;      // 每次均衡操作降低的电压 0.005V

public:
    BatteryPack(int n); // 构造函数：接收电芯数量 n，检查合法性；将电压初始化为 3.70V，所有均衡标志置 false。
    void setVoltage(int idx, double v);
    double getVoltage(int idx);
    void updateBalancingDecision();
    void performBalancing();
    double getMaxMinDiff() const;
    ~BatteryPack();
};

const double BatteryPack::BALANCE_THRESHOLD = 0.02;
const double BatteryPack::BALANCE_STEP = 0.005;

BatteryPack::BatteryPack(int n)
{
    if (n > 12 || n < 0) {
        cout << "Invalid count!" << endl;
        return;
    }
    cellCount = n;
    for (int i = 0; i < n; i++) {
        cellVoltages[i] = 3.70;
    }
    for (int i = 0; i < MAX_CELLS; i++) {
        balancing[i] = false;
    }
}

void BatteryPack::setVoltage(int idx, double v)
{
    if (idx < 0 || idx >= cellCount) {
        cout << "Invalid index!" << endl;
        cellCount = 0;
        return;
    }
    cellVoltages[idx] = v;
}

double BatteryPack::getVoltage(int idx)
{
    return cellVoltages[idx];
}

void BatteryPack::updateBalancingDecision()
{
    double maxV = cellVoltages[0], minV = cellVoltages[0];
    int maxIdx = 0;
    for (int i = 1; i < cellCount; i++) {
        if (cellVoltages[i] > maxV) {
            maxV = cellVoltages[i];
            maxIdx = i;
        }
        if (cellVoltages[i] < minV) {
            minV = cellVoltages[i];
        }
    }
    for (int i = 0; i < MAX_CELLS; i++) {
        balancing[i] = false;
    }
    if ((maxV - minV) > BALANCE_THRESHOLD) {
        balancing[maxIdx] = true;
    }
}

void BatteryPack::performBalancing()
{
    double minV = cellVoltages[0];
    for (int i = 1; i < cellCount; i++) {
        if (cellVoltages[i] < minV) {
            minV = cellVoltages[i];
        }
    }
    for (int i = 0; i < cellCount; i++) {
        if (balancing[i] == true) {
            cellVoltages[i] = cellVoltages[i] - BALANCE_STEP >= minV ? cellVoltages[i] - BALANCE_STEP : minV;
        }
    }
    updateBalancingDecision();
}

double BatteryPack::getMaxMinDiff() const
{
    double maxV = cellVoltages[0], minV = cellVoltages[0];
    for (int i = 1; i < cellCount; i++) {
        if (cellVoltages[i] > maxV) {
            maxV = cellVoltages[i];
        }
        if (cellVoltages[i] < minV) {
            minV = cellVoltages[i];
        }
    }
    return maxV - minV;
}

BatteryPack::~BatteryPack()
{
    cout << "Battery pack data cleared." << endl;
}

// 你的代码结束

int main()
{
    BatteryPack pack(6);
    // 模拟不一致状态
    pack.setVoltage(0, 3.75);
    pack.setVoltage(1, 3.71);
    pack.setVoltage(2, 3.70);
    pack.setVoltage(3, 3.68);
    pack.setVoltage(4, 3.72);
    pack.setVoltage(5, 3.69);

    for (int cycle = 0; cycle < 5; cycle++) {
        pack.updateBalancingDecision();
        pack.performBalancing();
        cout << "Cycle " << cycle << " max-min diff: " << pack.getMaxMinDiff() << " V" << endl;
    }

    return 0;
}

// 均衡算法中每次只对电压最高的电芯放电，这种策略被称为“最大值均衡”。
// 若电池组处于放电末端，电压普遍较低，但其中一节因内阻大而电压骤降，此时均衡策略会如何表现？
// 从工程安全思维考虑，BMS在放电末期应如何调整均衡策略以避免对落后电芯的过度消耗？

// 放电末端时，电压普遍较低，但其中一节因内阻大而电压骤降，这时最大值均衡策略会持续对电压最高的电芯进行放电，可能导致该电芯过度消耗，甚至损坏。
// 为了避免这种情况，BMS在放电末期应调整均衡策略，例如：
// 1. 降低均衡阈值：在放电末期，可以降低均衡启动的压差阈值，使得更多电芯参与均衡，避免单一电芯过度放电。
// 2. 限制均衡电流：在放电末期，可以限制均衡电流，减少对电芯的压力，保护电芯不被过度消耗。
// 3. 监控电芯状态：BMS应实时监控每个电芯的电压和温度 ，及时调整均衡策，确保每个电芯都在安全范围内工作，避免过度放电导致的损坏。
// 4. 引入多级均衡策略：在放电末期，可以引入多级均衡策略，根据电芯的电压差异和状态，动态调整均衡方式，确保每个电芯都得到适当的保护。