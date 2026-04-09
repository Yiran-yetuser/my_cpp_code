#define _CRT_SECURE_NO_WARNINGS 0
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

// 学生信息类
class Student
{
public:
    int Id;        // 学号
    char Name[20]; // 姓名

    Student() {};

    Student(int id, const char *name)
    {
        Id = id;
        strcpy(Name, name);
    }
};

// 课程类
class Course
{
private:
    char courseName[1024]; // 课程的名称
    Student *stuList;      // 选课学生名单，名单长度即预设选课人数容量
    int courseCapacity;    // 预设的课程选课人数容量
    int numberOfStudents;  // 已选课学生人数

public:
    Course(const char *, int);           // 构造函数，设置课程的名称、选课人数容量
    Course(const Course &);              // 复制构造函数
    ~Course();                           // 析构函数
    char *GetCourseName() const;         // 获得课程名称
    void SetCourseName(const char *);    // 修改课程名称
    bool AddStudent(const Student &stu); // 增加一位选课学生
    bool DropStudentbyId(int id);        // 按学号删除一位退选学生
    int getNumberOfStudents() const;     // 获得已选课学生人数
    void PrintStudents();                // 输出已选课学生名单
};

Course::Course(const char *newCourse, int capacity)
{
    // 填写1，完成构造函数（8分）
    //  capacity表示该课程选课人数容量
    //  请根据课程选课人数容量对stuList进行必要的内存分配
    //   newCourse指向的字符串表示课程名称
    //  需要将 newCourse 指针所指向的字符串，全部拷贝到couseName 指向的字符数组中
    //  可以使用循环结构逐个字符进行拷贝，特别注意字符串以 '\0' 结尾
    //  也可以调用 strcpy函数完成此项功能，strcpy函数原型：char * strcpy(char* _des, const char* scr);
    //  默认已选课人数为0
    numberOfStudents = 0;
    courseCapacity = capacity;
    stuList = new Student[capacity];
    strcpy(courseName, newCourse);
    // 评分标准：4个成员变量的初始化各2分
}

Course::Course(const Course &course) // 复制构造函数
{
    // 填写2，完成复制构造函数（12分）
    // 即要将 course 中所有的成员复制到本对象中
    // 注意对 courseName进行必要的内存分配
    numberOfStudents = course.numberOfStudents;
    courseCapacity = course.courseCapacity;
    stuList = new Student[courseCapacity];
    strcpy(courseName, course.courseName);
    for (int i = 0; i < numberOfStudents; i++) {
        stuList[i] = course.stuList[i];
    }
}

Course::~Course() // 析构函数
{
    // 填写3，完成析构函数（3分）
    // 参照构造函数，完成必要的内存释放
    if (stuList != nullptr) {
        delete[] stuList;
    }
    stuList = nullptr;
}

char *Course::GetCourseName() const
{
    return (char *)courseName;
}

void Course::SetCourseName(const char *name)
{
    strcpy(courseName, name);
}

bool Course::AddStudent(const Student &stu)
{
    // 填写4，完成添加一位选课同学的功能          （10分）
    // 注意判断是否超过选课容量，分情况处理：
    // 如果选课人数未达上限，可以将该学生添加到stuList中，选课人数加1，函数返回true；
    // 否则，表示该学生选课失败，函数返回false即可。
    if (numberOfStudents == courseCapacity) {
        return false;
    }
    numberOfStudents++;
    stuList[numberOfStudents - 1] = stu;
    return true;
}

bool Course::DropStudentbyId(int id)
{
    // 填写5，完成删除一位退选学生的功能          （10分）
    // 请遍历选课学生名单stuList，将当前学生的学号与退选学生的学号进行比较：
    // 如匹配，则停止遍历，并从查找到的位置开始，把后面的学生从后往前依次顺移一位，同时选课人数减1，函数返回true；
    // 如遍历整个名单没有找到匹配项，表示该学生并未选这门课，函数直接返回false即可。
    for (int i = 0; i < numberOfStudents; i++) {
        if (stuList[i].Id == id) {
            for (int j = i; j < numberOfStudents - 1; j++) {
                stuList[j] = stuList[j + 1];
            }
            numberOfStudents--;
            return true;
        }
    }
    return false;
}

int Course::getNumberOfStudents() const
{
    return numberOfStudents;
}

void Course::PrintStudents()
{
    if (numberOfStudents > 0) {
        cout << "选课学生名单：" << endl;
        for (int i = 0; i < numberOfStudents; i++) {
            cout << left << setw(6) << stuList[i].Id << stuList[i].Name << endl;
        }
    } else {
        cout << "暂无人选课，请核实。" << endl;
    }
}

int main()
{
    Course course1("C++ Proramming", 2);
    cout << "课程名称：";
    cout << course1.GetCourseName() << endl;

    cout << "现有2名学生选修该课程..." << endl;
    course1.AddStudent(Student(101, "John"));
    course1.AddStudent(Student(211, "Jack"));
    cout << "当前选课人数：";
    cout << course1.getNumberOfStudents() << endl;
    course1.PrintStudents();
    cout << endl;

    cout << "Mike（Id:102）请求选课" << endl;
    bool result = course1.AddStudent(Student(102, "Mike"));
    if (result)
        cout << "选课成功" << endl;
    else
        cout << "该课程选课人数已满，选课失败！" << endl;
    course1.PrintStudents();
    cout << endl;

    cout << "新增一门课程（默认选课名单与C++相同）：" << endl;
    Course course2(course1);
    course2.SetCourseName("Java Lanuague");
    cout << "课程名称：";
    cout << course2.GetCourseName() << endl;
    cout << "当前选课人数：";
    cout << course1.getNumberOfStudents() << endl;
    course2.PrintStudents();
    cout << endl;

    cout << "John（Id:101）请求退课" << endl;
    if (course2.DropStudentbyId(101))
        cout << "退课成功" << endl;
    course2.PrintStudents();
    cout << endl;

    return 0;
}

// 问答（7分，请在注解中直接作答）
//  1、在Course类中，复制构造函数是否有必要重载？ 请总结一下，一般什么情况下必须要重载复制构造函数？（3分）
//
//  2、在本题中，Student类的2个数据成员均设为公有成员变量，从数据安全的角度并不推荐这么设计，
//       如果把它们设为私有成员变量，会影响Course类中哪几个成员函数的正常使用，你有什么解决办法？（4分）