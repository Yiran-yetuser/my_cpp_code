#include <cstring>
#include <iostream>

using namespace std;

class Word
{
private:
    char *str;

public:
    Word(char *s);
    char &operator[](int n);
    void disp();
    ~Word();
};

Word::Word(char *s)
{
    str = new char[strlen(s) + 1];
    strcpy(str, s);
}

char &Word::operator[](int n)
{
    return str[n];
}

void Word::disp()
{
    cout << str << endl;
}

Word::~Word()
{
    delete[] str;
}

int main()
{
    char s[] = "china";
    Word w(s);
    w.disp();
    int n = strlen(s);
    while (n > 0) {
        w[n - 1] = w[n - 1] - 32;
        n--;
    }
    w.disp();
}
