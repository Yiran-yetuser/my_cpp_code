#include <cmath>
#include <iostream>
using namespace std;

// 完成 MicrostepMotor 类的定义
// 提示：角度归一化可使用 fmod 或 while 循环处理
// 你的代码开始
class MicrostepMotor
{
private:
    double currentAngle;                  // 当前电角度（弧度，0~2π）
    double phaseACurrent;                 // A相电流（-1.0 ~ 1.0）
    double phaseBCurrent;                 // B相电流
    static const int STEPS_PER_REV = 200; // 整步一圈脉冲数

public:
    MicrostepMotor(double angle = 0);
    void setElectricalAngle(double angle);
    void step(int microsteps);
    double getPhaseACurrent() const;
    double getPhaseBCurrent() const;
    ~MicrostepMotor();
};

MicrostepMotor::MicrostepMotor(double angle)
{
    setElectricalAngle(angle);
}

void MicrostepMotor::setElectricalAngle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    angle = fmod(angle, 2 * M_PI);
    phaseACurrent = cos(angle);
    phaseBCurrent = sin(angle);
    currentAngle = angle;
}

void MicrostepMotor::step(int microsteps)
{
    double delta = (2.0 * M_PI) / (STEPS_PER_REV * microsteps);
    currentAngle += delta;
    setElectricalAngle(currentAngle);
}

double MicrostepMotor::getPhaseACurrent() const
{
    return phaseACurrent;
}

double MicrostepMotor::getPhaseBCurrent() const
{
    return phaseBCurrent;
}

MicrostepMotor::~MicrostepMotor()
{
    cout << "Motor driver released." << endl;
}

// 你的代码结束

int main()
{
    MicrostepMotor motor(0.0); // 初始角度 0

    cout << "Initial currents: A=" << motor.getPhaseACurrent()
         << ", B=" << motor.getPhaseBCurrent() << endl;

    motor.setElectricalAngle(M_PI / 2.0); // 90度
    cout << "After set to 90 deg: A=" << motor.getPhaseACurrent()
         << ", B=" << motor.getPhaseBCurrent() << endl;

    motor.step(4); // 4微步，即整步分为4步
    cout << "After one microstep: A=" << motor.getPhaseACurrent()
         << ", B=" << motor.getPhaseBCurrent() << endl;

    return 0;
}

// 在嵌入式系统中，sin() 和 cos() 浮点运算开销较大。若微控制器算力有限，工程上常采用正弦查表法替代实时计算。
//  从计算思维角度，查表法属于哪种空间换时间的策略？请简述若需要 256 细分精度，查表数组至少需要多大？
//  使用查表法时，如何进行角度到数组索引的映射？
//  答：
//  查表法属于以空间换时间的策略。为了实现 256 细分精度，查表数组至少需要 256 个元素。
//  利用正弦函数的对称性（sin(θ) 在四象限的对称关系），可进一步压缩到 65 个元素（存储 0° ~ 90° 的 1/4 周期值，256/4 + 1 = 65），通过符号和偏移还原全周期值，此时空间换时间的代价更小。
//  角度到数组索引的映射可以通过将角度归一化到 0~360 度范围内，然后根据细分精度计算索引。