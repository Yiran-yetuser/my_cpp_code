#include "Stud.h"

#include<iostream>


int Stud::totalScore = 0;
int Stud::stuCnt = 0;
Stud::Stud()
{
    number = 0;
    name = "";
    score = 0;
}

Stud::~Stud()
{
}

void Stud::SetData(int n, std::string nm, int s)
{
    number = n;
    name = nm;
    score = s;
    totalScore+=s;
    stuCnt++;
}

void Stud::Disp()
{
    std::cout<<name<<"\t"<<number<<"\t"<<score<<std::endl;
}

double Stud::Avg()
{
    return 1.0*totalScore/stuCnt;
}
