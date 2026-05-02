#include <iostream>
using namespace std;

class Boxes
{
private:
    int *box;       // 指向保管箱数组
    char *flag;     // 指向客户标识符号数组
    static int sum; // 累计物品存入数量
    int size;       // 保管箱数量

public:
    Boxes(int num = 10);
    ~Boxes();
    void put(int n, char m);
    void get(char m);
    void display();
};

int Boxes::sum = 0;

Boxes::Boxes(int num)
{
    size = num;
    box = new int[num];
    flag = new char[num];
    for (int i = 0; i < num; i++) {
        box[i] = 0;
        flag[i] = '\0';
    }
}

Boxes::~Boxes()
{
    delete[] box;
    delete[] flag;
}

void Boxes::put(int n, char m)
{
    for (int i = 0; i < size; i++) {
        if (box[i] == 0) {
            box[i] = n;
            flag[i] = m;
            sum += n;
            return;
        }
    }
    cout << "No empty box." << endl;
}

void Boxes::get(char m)
{
    for (int i = 0; i < size; i++) {
        if (flag[i] == m) {
            sum -= box[i];
            box[i] = 0;
            flag[i] = '\0';
            return;
        }
    }
    cout << "The box is not found." << endl;
}

void Boxes::display()
{
    int used = 0;
    int empty = 0;
    cout << "Box status:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Box " << i << ": ";
        if (box[i] == 0) {
            cout << "empty";
            empty++;
        } else {
            cout << "flag=" << flag[i] << ", count=" << box[i];
            used++;
        }
        cout << endl;
    }
    cout << "Used boxes: " << used << ", Empty boxes: " << empty << endl;
    cout << "Total items stored: " << sum << endl;
}

int main()
{
    Boxes A, B(2);

    A.put(5, 'R');
    B.put(9, 'K');
    A.put(8, 'P');
    B.put(15, 'H');
    B.put(40, 'F');
    B.put(40, 'F');

    cout << "=== Display A ===" << endl;
    A.display();
    cout << "\n=== Display B ===" << endl;
    B.display();

    B.get('H');
    B.get('H');
    B.put(40, 'F');
    A.get('S');
    A.get('R');
    A.put(12, 'M');

    cout << "\n=== Display A ===" << endl;
    A.display();
    cout << "\n=== Display B ===" << endl;
    B.display();

    return 0;
}
