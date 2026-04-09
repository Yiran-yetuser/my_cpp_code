#include "Person.h"

#include <iostream>
Person::Person()
{
    name = "Unknown";
    age = -1;
    gender = 'U';
}

Person::Person(std::string n, char g, int a)
{
    name = n;
    gender = g;
    age = a;
}

Person::Person(const Person &p)
{
    name = p.name;
    gender = p.gender;
    age = p.age;
}

Person::~Person()
{
    // No need to manually delete name since it's a std::string
}

void Person::print()
{
    std::cout << "Name: " << name << std::endl
              << "Gender: " << gender << std::endl
              << "Age: " << age << std::endl;
}
