#include <cstring>
#include <iostream>
using namespace std;

class String
{
private:
    char *str; // 字符串的首地址
    int len;   // 字符串的长度

public:
    // 构造函数：动态申请存储字符串所需的内存空间
    // 既能用参数指定的字符串也能用默认值NULL进行字符串的初始化
    String(const char *s = NULL)
    {
        if (s == nullptr) {
            str = nullptr;
            len = 0;
        } else {
            int s_len = 0;
            while (s[s_len] != '\0') {
                s_len++;
            }
            len = s_len;
            str = new char[s_len + 1];
            strcpy(str, s);
        }
    }

    // 拷贝构造函数（深拷贝）
    String(const String &s)
    {
        len = s.len;
        if (s.str != nullptr) {
            str = new char[len];
            strcpy(str, s.str);
        } else {
            str = nullptr;
        }
    }

    // 析构函数：释放字符串所使用的动态内存空间
    ~String()
    {
        if (str != nullptr) {
            delete[] str;
            str = nullptr;
        }
    }

    // 为字符串赋新值
    void set(const char *s)
    {
        if (str != nullptr) {
            delete[] str;
            str = nullptr;
        }
        if (s == nullptr) {
            str = nullptr;
            len = 0;
        } else {
            int s_len = 0;
            while (s[s_len] != '\0') {
                s_len++;
            }
            str = new char[s_len];
            strcpy(str, s);
        }
    }

    // 显示字符串
    void show()
    {
        if (str == nullptr) {
            cout << "字符串为空！" << endl;
        } else {
            for (int i = 0; str[i] != '\0'; i++) {
                cout << str[i];
            }
            cout << endl;
        }
    }

    // 返回字符串的长度
    int getlen()
    {
        return len;
    }

    // 删除字符串中出现的所有ch字符
    void delchar(char ch)
    {
        if (str == nullptr) {
            return;
        }
        int j = 0; // j指向新字符串的当前位置
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] != ch) {
                str[j] = str[i];
                j++;
            }
        }
        str[j] = '\0'; // 添加字符串结束符
        len = j;       // 更新长度
    }

    // 重载"-"运算符：删除字符串中出现的所有ch字符（如 str-'h'）
    String operator-(char ch)
    {
        String temp(str);
        temp.delchar(ch);
        return temp;
    }

    // 重载"="运算符：实现字符串的直接赋值（深拷贝）
    String &operator=(const String &s)
    {
        if (this == &s) {
            return *this;
        }
        set(s.str);
        return *this;
    }

    // 重载"+="运算符：实现两字符串的拼接
    String &operator+=(const String &s)
    {
        if (s.str == nullptr || s.len == 0) {
            return *this;
        }
        if (str == nullptr) {
            set(s.str);
            return *this;
        }
        int new_len = len + s.len;
        char *new_str = new char[new_len];
        strcpy(new_str, str);
        strcat(new_str, s.str);
        delete[] str;
        str = new_str;
        len = new_len;
        return *this;
    }

    // 重载"=="运算符：进行两字符串的相等性比较
    bool operator==(const String &s)
    {
        if (len != s.len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (str[i] != s.str[i]) {
                return false;
            }
        }
        return true;
    }

    // 友元函数声明：重载"+"运算符，实现两字符串的相加
    friend String operator+(const String &s1, const String &s2);
};

// 友元函数实现：重载"+"运算符，实现两字符串的相加
String operator+(const String &s1, const String &s2)
{
    String temp(s1);
    temp += s2;
    return temp;
}

int main()
{
    cout << "========== 1. 测试构造函数 ==========" << endl;
    String s1("Hello");
    cout << "s1: ";
    s1.show();
    cout << "s1长度: " << s1.getlen() << endl;

    String s2; // 无参构造
    cout << "s2(无参): ";
    s2.show();
    cout << endl;

    cout << "========== 2. 测试拷贝构造函数 ==========" << endl;
    String s3(s1);
    cout << "s3(拷贝s1): ";
    s3.show();
    cout << endl;

    cout << "========== 3. 测试set函数 ==========" << endl;
    s2.set("World");
    cout << "s2(set后): ";
    s2.show();
    cout << endl;

    cout << "========== 4. 测试delchar函数 ==========" << endl;
    String s4("hello world");
    cout << "s4原字符串: ";
    s4.show();
    s4.delchar('l');
    cout << "s4删除'l'后: ";
    s4.show();
    cout << "s4长度: " << s4.getlen() << endl;
    cout << endl;

    cout << "========== 5. 测试operator- ==========" << endl;
    String s5("banana");
    cout << "s5原字符串: ";
    s5.show();
    String s6 = s5 - 'a';
    cout << "s5-'a'结果: ";
    s6.show();
    cout << "s5保持不变: ";
    s5.show();
    cout << endl;

    cout << "========== 6. 测试operator= ==========" << endl;
    String s7;
    s7 = s1;
    cout << "s7(=s1): ";
    s7.show();
    // 测试自赋值
    s7 = s7;
    cout << "s7(自赋值后): ";
    s7.show();
    cout << endl;

    cout << "========== 7. 测试operator+= ==========" << endl;
    String s8("Hello");
    String s9(" World");
    cout << "s8: ";
    s8.show();
    cout << "s9: ";
    s9.show();
    s8 += s9;
    cout << "s8+=s9后: ";
    s8.show();
    cout << endl;

    cout << "========== 8. 测试operator== ==========" << endl;
    String s10("Test");
    String s11("Test");
    String s12("Different");
    cout << "s10==s11: " << (s10 == s11 ? "true" : "false") << endl;
    cout << "s10==s12: " << (s10 == s12 ? "true" : "false") << endl;
    cout << endl;

    cout << "========== 9. 测试友元operator+ ==========" << endl;
    String s13("Good");
    String s14("Morning");
    String s15 = s13 + s14;
    cout << "s13: ";
    s13.show();
    cout << "s14: ";
    s14.show();
    cout << "s13+s14: ";
    s15.show();
    cout << endl;

    cout << "========== 所有测试完成 ==========" << endl;

    return 0;
}
