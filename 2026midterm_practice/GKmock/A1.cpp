#include <iostream>
using namespace std;

// 请在此处完成 TemperatureSensor 类的定义
// 你的代码开始
class TemperatureSensor
{
private:
    double temperature; // 表示当前温度值（单位：摄氏度）
public:
    TemperatureSensor() : temperature(25.0) {};
    TemperatureSensor(double t) : temperature(t) {};
    ~TemperatureSensor()
    {
        cout << "Sensor distroyed." << endl;
    };
    void setTemperature(double t)
    {
        temperature = t;
    };
    double getTemperature() const
    {
        return temperature;
    };
};

// 你的代码结束

int main()
{
    TemperatureSensor sensor1;       // 默认构造
    TemperatureSensor sensor2(36.5); // 带参构造

    cout << "Sensor1: " << sensor1.getTemperature() << " C" << endl;
    cout << "Sensor2: " << sensor2.getTemperature() << " C" << endl;

    sensor1.setTemperature(28.0);
    cout << "Sensor1 updated: " << sensor1.getTemperature() << " C" << endl;

    return 0;
}
