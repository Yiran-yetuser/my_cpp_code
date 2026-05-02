#include <iostream>
using namespace std;

class Book
{
private:
    int No;       // 图书序号
    int cap;      // 图书库存数量（库存最多允许 10 本）
    double Price; // 图书价格
    int lend;     // 已借出图书数量
public:
    Book(int a = 0, int b = 0, double c = 0); // 构造函数（a,b,c 初始化数据成员中的序号、数量和价格，lend赋值 0）
    int input(double m);                      // 添加图书数量 m 本（若 cap+m 超过 10 则提示“只能添加 x 本”。返回-x。x 表示能添加的数量）
    void lendout(int n);                      // 借出 n 本图书（如果库存足够，给出“借书成功！”的提示，
                                              // 否则显示数量差额的提示信息。），对有关的数据成员 cap 和 lend 做相应的运算。
    void giveback(int n);                     // 归还图书 n 本（cap 和 lend 相应加减 n）
    int getcap();                             // 返回图书数量
    int getlend();                            // 返回借出图书数量
    double getprice();                        // 返回图书价格
    void display();                           // 输出序号、数量、价格和借出数量
    ~Book();
};

Book::Book(int a, int b, double c)
{
    No = a;
    cap = b;
    Price = c;
    lend = 0;
}

Book::~Book()
{
}

int Book::input(double m)
{
    if (cap + m > 10) {
        cout << "只能添加" << 10 - cap << "本。" << endl;
        return cap - 10;
    }
    cap += m;
    return 0;
}

void Book::lendout(int n)
{
    if (cap >= n) {
        cout << "借书成功！" << endl;
        cap -= n;
        lend += n;
    } else {
        lend += cap;
        cout << "借书失败！"
             << "还差" << n - cap << "本书" << endl;
        cap = 0;
    }
}

void Book::giveback(int n)
{
    cap += n;
    lend -= n;
}

int Book::getcap()
{
    return cap;
}

int Book::getlend()
{
    return lend;
}

double Book::getprice()
{
    return Price;
}

void Book::display()
{
    cout << "No." << No << "\t库存数量：" << cap
         << "\t价格：" << Price << "\t已借出数量：" << lend << endl;
}

int main()
{
    int t, sum = 0;
    Book A(101, 2, 35.8), B(102, 5, 66.2);
    t = A.input(3);
    if (t < 0)
        A.input(-t);
    t = B.input(8);
    if (t < 0)
        B.input(-t);
    A.display();
    B.display();
    if (A.getprice() > B.getprice()) {
        A.lendout(3);
        B.lendout(8);
    } else {
        B.lendout(3);
        A.lendout(8);
    }
    A.display();
    B.display();
    A.giveback(4);
    B.giveback(3);
    A.display();
    B.display();
    sum = A.getcap() + A.getlend() + B.getcap() + B.getlend();
    cout << "所有图书的总数量=" << sum << endl;
    return 0;
}