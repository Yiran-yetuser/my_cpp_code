#define _CRT_SECURE_NO_WARNINGS 0
#include <iostream>
#include <string>

using namespace std;

class Time
{
private:
    int day;    // 表示天数
    int hour;   // 表示小时数，值不超过24
    int minute; // 表示分钟数，值不超过60
    int second; // 表示秒数，值不超过60

    // 仅返回"时:分:秒" 表示的总秒数（不包含天数部分）
    // 即对Time对象中，不超过24小时的那部分时间换算成秒数
    int toSeconds() const
    {
        return (hour * 60 + minute) * 60 + second;
    }

public:
    // 使用表示时间的总秒数来构造Time对象，总秒数是个非负整数
    // 即将总秒数totalseconds换算成天数、小时数、分钟数和秒数。
    Time(int totalseconds = 0)
    {
        second = totalseconds % 60;
        int mm = totalseconds / 60;
        minute = mm % 60;
        int hh = mm / 60;
        hour = hh % 24;
        day = hh / 24;
    }

    int GetDay() const { return day; }
    int GetHour() const { return hour; }
    int GetMinute() const { return minute; }
    int GetSecond() const { return second; }

    // 实现时间对象到字符串格式的转换，用于输出到屏幕
    string ToString()
    {
        char strToFill[512];
        int len;
        if (day != 0)
            len = sprintf(strToFill, "%d天 %02d:%02d:%02d\0", day, hour, minute, second);
        else
            len = sprintf(strToFill, "%02d:%02d:%02d\0", hour, minute, second);
        return string(strToFill);
    }

    // 填写1：请在此补充必要的成员函数声明（包括构造函数等）（5分）
    Time(int h, int m, int s = 0, int d = 0);
    Time(const Time &t) : hour(t.hour), minute(t.minute), second(t.second), day(t.day) {} // 拷贝构造函数

    Time GetTimeInterval(Time);
    Time AddTime(Time);
};

// 填写2： 根据主函数和部分成员函数中涉及到的Time类对象的多种创建场景，
//               在【类外】补充必要的构造函数（不限制构造函数的数量）（15分）

Time::Time(int h, int m, int s, int d)
{
    second = s % 60;
    m += s / 60;
    minute = m % 60;
    h += m / 60;
    hour = h % 24;
    day = d + h / 24;
}

// Time类成员函数
// 计算当前时刻t1 到 t2 时刻流逝的时间（t1即到t2的时间间隔）
// 调用时要求满足： t1 < t2
Time Time::GetTimeInterval(Time t2)
{
    int timedelta = t2.toSeconds() - toSeconds(); //  获取时间部分的总秒数差
    int dd = t2.day - day;                        // 获取天数差

    // 如果总秒数差小于0，则需要从t2的天数中借1天（24小时）
    // 再把这1天的时间转换成86400秒，叠加到当前总秒数差中，以保证总秒数差值是个正数
    if (timedelta < 0) {
        dd--;               // t的天数减1
        timedelta += 86400; // 时间差加上1天所表示的秒数
    }

    // 注意：这里使用总秒数构造了一个Time对象tt
    // 该对象其实仅表示t1到t2所流逝的时间的时，分，秒部分，天数部分的计算结果存储在变量dd中。
    Time tt(timedelta);

    // 函数返回一个Time对象，该对象通过时、分、秒和天数这4个参数进行构造（注意参数次序）。
    // 其中，分和秒的输入参数值均小于60
    return Time(tt.hour, tt.minute, tt.second, dd);
}

// Time类成员函数
// 计算当前时刻流逝了deltatime表示的时长后的新时刻
Time Time::AddTime(Time deltatime)
{
    // 填写2：参照GetTimeInterval函数的处理思路，按提示补充代码（12分）
    Time t2(toSeconds() + deltatime.toSeconds());
    return t2;
}

int main()
{
    Time t0;             // 创建时间对象t0: 默认0天0时0分0秒
    Time t1(22, 30, 59); // 创建时间对象t1，表示时刻: 22小时30分59秒
    Time t2(75, 20);     // 创建时间对象t2，表示时刻: 75小时20分0秒

    cout << "t0:" << t0.ToString() << endl;
    cout << "t1:" << t1.ToString() << endl;
    cout << "t2:" << t2.ToString() << endl;
    cout << endl;

    cout << "从t1时刻逝去30小时50分后的时刻为：" << endl;

    // 填写3：计算从t1时刻逝去30时50分后的时刻，保存在时间对象t3中（4分）
    Time deltaTime1(30, 50);
    Time t3 = t1.AddTime(deltaTime1);
    cout << t3.ToString() << endl;
    cout << endl;

    cout << "从时刻t1到t2逝去的时间为：" << endl;
    // 填写4：计算并输出从时刻t1到t2逝去的时间（时间间隔）（4分）
    Time deltaTime2 = t1.GetTimeInterval(t2);
    cout << deltaTime2.ToString() << endl;
    cout << endl;
}

// 回答（10分，请在注解中直接作答）
// 1) 说明Time类中返回值类型为int，以Get开头的4个公有成员函数的作用和特点。（4分）
//     int GetDay() const { return day; }
//     int GetHour() const { return hour; }
//     int GetMinute() const { return minute; }
//     int GetSecond() const { return second; }
//
//     作用：这四个函数是Time类的getter函数，用于获取Time对象的各个时间分量的值。
//     特点：
//     1. 都是公有成员函数，允许外部代码访问Time对象的私有成员变量
//     2. 都是const成员函数，不会修改对象的状态
//     3. 遵循了封装原则，通过公有的访问器方法访问私有成员

// 2) Time类的两个成员函数：GetTimeInterval和AddTime，输入参数均是同类对象，
//     请你从减少对象拷贝次数的角度，考虑如何改进设计，优化程序性能？（6分）
//
//     改进方法：将输入参数改为const和&引用传递，避免对象拷贝：
//        Time GetTimeInterval(const Time& t2);
//        Time AddTime(const Time& deltatime);
