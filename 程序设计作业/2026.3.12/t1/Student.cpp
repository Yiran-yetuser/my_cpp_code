#include "Student.h"
#include <iostream>
using namespace std;
Student::Student()
{
    n = 0;
    stu = nullptr;
    count = 0;
}

void Student::input(int n)
{
    stu = new float[n];
    cout << "请输入" << n << "名学生的成绩: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> stu[i];
        if (stu[i] > 80) {
            count++;
        }
    }
}

void Student::stat()
{
    cout << "\n===80 分以上的学生 ===" << endl;
    cout << "编号\t成绩" << endl;
    cout << "----------------" << endl;
    Student::Show();
}

void Student::Show()
{
    for (int i = 0;i<10;i++) {
        if (stu[i] > 80) {
            cout << i + 1 << '\t' << stu[i] << endl;
        }
    }
}

void Student::print()
{
    cout << "符合条件的总人数: " << count << endl;
}

Student::~Student()
{
    if (stu) {
        delete[] stu;
        stu = nullptr;
    }
}
