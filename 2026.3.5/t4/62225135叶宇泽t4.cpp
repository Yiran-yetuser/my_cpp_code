#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
struct Player {
    char player_name[20];
    double score[7], aver;
    void delmaxmin()
    {
        aver = 0.0;
        int max = score[0], min = score[0];
        for (int i = 0; i < 7; i++) {
            aver += score[i];
            max = max > score[i] ? max : score[i];
            min = min < score[i] ? min : score[i];
        }
        aver -= (max + min);
        aver /= 5.0;
    }
} PERSON[3];

// 测试用例
int main()
{
    strcpy(PERSON[0].player_name, "li");
    double scores1[7] = {94, 97, 98, 96, 100, 99, 97};
    for (int i = 0; i < 7; i++) {
        PERSON[0].score[i] = scores1[i];
    }
    PERSON[0].aver = 0;

    // 选手2: zhang
    strcpy(PERSON[1].player_name, "zhang");
    double scores2[7] = {96, 97, 98, 98, 100, 97, 96};
    for (int i = 0; i < 7; i++) {
        PERSON[1].score[i] = scores2[i];
    }
    PERSON[1].aver = 0;

    // 选手3: zhou
    strcpy(PERSON[2].player_name, "zhou");
    double scores3[7] = {95, 100, 99, 96, 97, 96, 97};
    for (int i = 0; i < 7; i++) {
        PERSON[2].score[i] = scores3[i];
    }
    PERSON[2].aver = 0;

    // 计算每位选手的平均分
    for (int i = 0; i < 3; i++) {
        PERSON[i].delmaxmin();
    }

    // 按平均分排序
    sort(PERSON, PERSON + 3, [](const Player &a, const Player &b) {
        return a.aver > b.aver;
    });

    // 输出结果
    for (int i = 0; i < 3; i++) {
        cout << setprecision(0) << fixed << PERSON[i].player_name << ": ";
        for (int j = 0; j < 7; j++) {
            cout << "\t" << PERSON[i].score[j];
        }
        cout << "\t" << setprecision(2) << fixed << PERSON[i].aver << endl;
    }

    return 0;
}
