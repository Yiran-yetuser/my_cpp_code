#ifndef STUD_H
#define STUD_H
#include<string>
class Stud
{
private:
    static int totalScore; // 总成绩
    static int stuCnt; // 学生人数
    int number; // 学号
    std::string name; // 姓名
    int score; // 成绩

public:
    Stud(/* args */);
    ~Stud();
    void SetData(int n, std::string name, int s);
    void Disp(); // 输出数据
    static double Avg();
};



#endif