#include "Student.h"
#include "Student.cpp"
#include <iostream>

int main()
{
    Student s;
    std::cout << "学生人数: ";
    int stuCnt; // 学生成绩
    std::cin >> stuCnt;
    s.input(stuCnt);
    s.stat();
    s.print();
    return 0;
}