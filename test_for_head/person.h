#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    std::string name;
    int age;
    
public:
    Person(std::string n, int a);
    void introduce();
    int getAge();
};

#endif
