#include "Stud.cpp"
#include "Stud.h"

#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main()
{
    const int N = 5; // 学生数量
    std::vector<int> inputNumbers(N), inputScores(N);
    std::vector<std::string> inputNames(N);
    Stud students[N];
    for (int i = 0; i < N; i++) {
        int number;
        std::string name;
        int s;

        std::cin >> number >> name >> s;
        inputNumbers.push_back(number);
        inputNames.push_back(name);
        inputScores.push_back(s);
        students[i].SetData(number, name, s);
    }
    std::cout << "Name\tNo.\tscores\n";
    for (int i = 0; i < N; i++) {
        students[i].Disp();
    }
    std::cout << std::setprecision(2) << std::fixed
              << "Average score: " << Stud::Avg() << std::endl;
    std::cout << "Expected average score: "
              << std::accumulate(inputScores.begin(), inputScores.end(), 0) / N
              << std::endl;
    return 0;
}