#include <iostream>
#include <cmath>
using namespace std;
struct Coordinate {
    int x;
    int y;
};

double distance(Coordinate *p1, Coordinate *p2)
{
    double res = sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
    return res;
}
double manhattanDistance(Coordinate *p1, Coordinate *p2)
{
    double res = double(abs(p1->x - p2->x) + abs(p1->y - p2->y));
    return res;
}

int main()
{
    Coordinate *p1 = new Coordinate{1,3};
    Coordinate *p2 = new Coordinate{-2,6};
    cout<<distance(p1,p2)<<endl<<manhattanDistance(p1,p2)<<endl;
    return 0;
}