#include <cstring>
#include <iostream>
using namespace std;
struct student {
    char name[20];
    float math;
};
student a[10] = {{"张三", 90}, {"李四", 85}, {"王五", 73}};
int count = 3; // 数组中包含的学生数

void addStudent(student a[], student &newStudent)
{
    if (count >= 10) {
        cout << "人数已满，无法添加" << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        if (a[i].math <= newStudent.math) {
            for (int j = count; j >= i + 1; j--) {
                a[j] = a[j - 1];
            }
            a[i] = newStudent;
            break;
        }
    }
    count++;
    cout << "添加成功！" << endl;
}

// 根据姓名删除学生（假设姓名唯一）
void deleteStudent(student a[], const char *name)
{
    int pos = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(a[i].name, name) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        cout << "未找到姓名为 " << name << " 的学生！" << endl;
        return;
    }
    for (int i = pos; i < count - 1; i++) {
        a[i] = a[i + 1];
    }
    count--;
    cout << "删除成功：" << name << endl;
}

// 测试函数（可选）ai生成
int main()
{
    student a[10] = {{"张三", 90}, {"李四", 85}, {"王五", 73}};
    int count = 3;

    // 添加测试
    student newStu1 = {"赵二", 96};
    student newStu2 = {"钱六", 65};
    student newStu3 = {"孙七", 80};
    addStudent(a, newStu1);
    addStudent(a, newStu2);
    addStudent(a, newStu3);

    // 输出当前数组
    cout << "\n当前学生列表（降序）：" << endl;
    for (int i = 0; i < count; i++) {
        cout << a[i].name << " : " << a[i].math << endl;
    }

    // 删除测试
    deleteStudent(a, "李四");
    deleteStudent(a, "赵二");
    deleteStudent(a, "不存在");

    // 再次输出
    cout << "\n删除后学生列表：" << endl;
    for (int i = 0; i < count; i++) {
        cout << a[i].name << " : " << a[i].math << endl;
    }

    return 0;
}