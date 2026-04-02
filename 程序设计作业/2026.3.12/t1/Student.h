#ifndef STUDENT_H
#define STUDENT_H

class Student
{
private:
    /* data */
    int n; // 编号
    float *stu; // 考试成绩
    int count; // 符合条件的总人数
public:
    Student(/* args */);
    void input(int n); // —输入学生成绩，并统计满足条件的人 数存入 count 变量
    void stat(); // 查找符合条件的编号、成绩，并调用成员函数 Show 输出对应的编号、成绩
    void Show(); // 输出符合条件的编号、成绩
    void print(); // 输出符合条件的总人数
    ~Student();
};
#endif
