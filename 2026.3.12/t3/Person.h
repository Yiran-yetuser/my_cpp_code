#ifndef PERSON_H
#define PERSON_H

#include <string>
class Person
{
private:
    std::string name;
    char gender;
    int age;

public:
    Person();
    Person(std::string n,char g,int a);
    Person(const Person& p);
    ~Person();
    void print();
};
#endif