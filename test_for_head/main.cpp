#include "person.h"
#include <iostream>

// 构造函数定义
Person::Person(std::string n, int a) : name(n), age(a) {}

// 成员函数定义
void Person::introduce()
{
    std::cout << "Hi, I'm " << name << ", " << age << " years old." << std::endl;
}

int Person::getAge()
{
    return age;
}

int main()
{
    Person p("Alice", 25);
    p.introduce();
    std::cout << "Age: " << p.getAge() << std::endl;
    return 0;
}
