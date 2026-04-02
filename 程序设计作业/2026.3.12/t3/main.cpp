#include "Person.h"
#include "Person.cpp"

#include<iostream>
int main()
{
    Person P1;
    Person P2("David Martinez", 'M', 18);
    Person P3(P2);
    P1.print();
    P2.print();
    P3.print();
    return 0;

}