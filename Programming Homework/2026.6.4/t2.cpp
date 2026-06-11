#include <cstring> // strlen, strcpy 等允许使用
#include <iostream>
using namespace std;

// ========== String 类声明 ==========
class String
{
private:
    char *data;     // 动态分配的字符数组
    int len;        // 字符串长度（不含结尾'\0'）
    int *ref_count; // 引用计数指针（COW 实现）
    // 写时复制：当需要修改字符串时，若共享则创建私有副本
    void detach()
    {
        if (*ref_count == 1)
            return; // 当前对象独占数据，无需复制
        // 创建新内存块
        char *new_data = new char[len + 1];
        strcpy(new_data, data);
        // 减少旧引用计数
        --(*ref_count);
        // 更新为新块的独占引用
        ref_count = new int(1);
        data = new_data;
    }

public:
    // 默认构造：空字符串
    String() : len(0), data(new char[1]{'\0'}), ref_count(new int(1)) {}

    // 从 C 风格字符串构造
    String(const char *cstr)
    {
        // TODO: 实现
        // 如果输入字符串是空串，则只构造终止符
        if (cstr == nullptr) {
            data = new char[1]{'\0'};
            len = 0;
            ref_count = new int(1); // 共享空串的引用计数

            return;
        }

        len = strlen(cstr);
        data = new char[len + 1];
        for (int i = 0; i < len; i++) {
            data[i] = cstr[i];
        }
        data[len] = '\0';
        ref_count = new int(1); // 独占数据，引用计数为 1
    }
    // 拷贝构造（深拷贝）
    String(const String &other)
    {
        // TODO: 实现
        // [重大优化提示 8 分] 若实现写时拷贝（COW），此处应增加引用计数并共享 data指针。
        data = other.data;
        len = other.len;
        ref_count = other.ref_count;
        if (ref_count) {
            (*ref_count)++;
        } else {
            ref_count = new int(1);
        }
    }
    // 析构
    ~String()
    {
        // TODO: 实现
        // [重大优化提示 8 分] 若使用引用计数，需在计数归零时释放内存。
        if (--(*ref_count) == 0) {
            delete[] data;
            delete ref_count;
        }
        data = nullptr;
    }
    // 拷贝赋值运算符（深拷贝，需处理自赋值）
    String &operator=(const String &other)
    {
        // TODO: 实现（注意自赋值、释放旧内存、深拷贝）
        // [一般优化提示 5 分] 在赋值前先检查是否需要分配新内存，若已有空间足够，可复用现有内存以减少动态分配。
        if (this != &other) { // 自赋值检查
            if (*ref_count == 1) {
                delete[] data;
                delete ref_count;
                data = nullptr;
            } else {
                --(*ref_count);
            }
            data = other.data;
            len = other.len;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }
    // 拼接两个字符串，返回新 String
    String operator+(const String &other) const
    {
        // TODO: 实现
        // [一般优化提示 5 分] 若 *this 为空，直接返回 other 的拷贝；若 other 为空，返回 * this 的拷贝。
        if (this->len == 0) {
            return String(other);
        }
        if (other.len == 0) {
            return String(*this);
        }
        // 创建新字符串
        int new_len = this->len + other.len;
        char *new_data = new char[new_len + 1];
        strcpy(new_data, this->data);
        strcat(new_data, other.data);
        String result(new_data);
        delete[] new_data;
        return result;
    }
    // 相等判断
    bool operator==(const String &other) const
    {
        // TODO: 实现
        if (this->len == other.len) {
            if (strcmp(this->data, other.data) == 0) {
                return true;
            }
        }
        return false;
    }
    // 小于判断（字典序）
    bool operator<(const String &other) const
    {
        // TODO: 实现
        return strcmp(this->data, other.data) < 0;
    }
    // 大于判断（利用 < 实现）
    bool operator>(const String &other) const
    {
        // 调用 < 重载实现
        return other < *this;
    }
    // 不等于（利用 == 实现）
    bool operator!=(const String &other) const
    {
        // 调用 == 重载实现
        return !(*this == other);
    }
    // 小于等于（利用 > 实现，即 !(a > b)）
    bool operator<=(const String &other) const
    {
        // 调用已有重载实现
        return !(*this > other);
    }
    // 大于等于（利用 < 实现，即 !(a < b)）
    bool operator>=(const String &other) const
    {
        // 调用 == 重载实现
        return !(*this < other);
    }
    // 索引访问（非 const 版本）
    char &operator[](int index)
    {
        // TODO: 实现
        // [小优化提示 2 分] 可添加边界检查，并在注释中说明健壮性考量。
        if (index < 0 || index >= len) {
            throw out_of_range("Index out of range");
        }
        detach(); // 确保独占数据以允许修改
        return data[index];
    }
    // 索引访问（const 版本）
    const char &operator[](int index) const
    {
        // TODO: 实现
        // [小优化提示 2 分] 同上，可添加边界检查。
        if (index < 0 || index >= len) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    // 返回字符串长度
    int length() const
    {
        // TODO: 实现
        return len;
    }
    // 返回 C 风格字符串（以'\0'结尾）
    const char *c_str() const
    {
        // TODO: 实现
        return data;
    }
};
// ===== 请回答以下问题（写在下方注释中） =====
// Q1: 为什么 String 类需要深拷贝？在你的赋值运算符中如何避免自赋值问题？
// 作答：String类内存在指针指向一个数组，如果使用默认的浅拷贝，多个String对象会指向同一块内存。
// 当一个对象被修改或销毁时，可能会影响其他对象，导致数据混乱或内存泄漏。为了避免这种情况，我们需要实现深拷贝，即为每个对象分配独立的内存并复制数据。
// 使用了if(this != &other)来检查是否是自赋值，如果是自赋值则直接返回当前对象，不进行任何操作，从而避免了自赋值带来的问题。

// Q2: 拷贝赋值运算符中自赋值检查的目的是什么？列举至少两种实现自赋值安全的常见方法。
// 作答：自赋值检查的目的是避免在赋值过程中错误地修改或释放当前对象的数据，导致数据损坏或内存泄漏。常见的实现自赋值安全的方法有：
// 1. 使用 if(this != &other) 来检查是否是自赋值，如果是自赋值则直接返回当前对象，不进行任何操作。
// 2. 使用临时对象来实现赋值操作，先创建一个临时对象来保存要赋值的数据，然后交换当前对象和临时对象的内容，最后让临时对象自动销毁，这样可以确保在整个过程中当前对象的数据始终有效。

// 额外的优化说明(程序原注解中已进行优化提示，且已实现的优化不必在此说明)
// 请在此列出你额外实现且未在上述提示中出现的优化点，并自评对应分值（重大 8 分/一般5 分 / 小 2 分，累计上限 10 分）。
// 1. 在<运算符重载中使用strcmp实现字典序比较，避免了手动逐字符比较的复杂性和潜在错误。（小优化 2 分）
// 2. 在构造函数中添加了对空串的特殊处理，避免了不必要的内存分配和复制操作，提高了效率。（小优化 2 分）
// =========================================
// ========== 主函数（测试用例，不可修改） ==========
int main()
{
    // 测试 1：默认构造与从 C 串构造
    String s1;           // 空串
    String s2("Hello");  // "Hello"
    String s3(" World"); // " World"
    String s4("Hello");  // 与 s2 相同，用于比较测试
    cout << "s1: '" << s1.c_str() << "' length=" << s1.length() << endl;
    cout << "s2: '" << s2.c_str() << "' length=" << s2.length() << endl;
    cout << "s3: '" << s3.c_str() << "' length=" << s3.length() << endl;
    // 测试 2：拼接与拷贝
    String s5 = s2 + s3; // "Hello World"
    String s6(s5);       // 拷贝构造
    cout << "s5 (s2+s3): '" << s5.c_str() << "' length=" << s5.length() << endl;
    cout << "s6 (copy of s5): '" << s6.c_str() << "' length=" << s6.length() << endl;
    // 测试 3：赋值运算符（包括自赋值）
    s1 = s5; // 正常赋值
    s5 = s5; // 自赋值测试
    cout << "s1 after assignment: '" << s1.c_str() << "' length=" << s1.length() << endl;
    cout << "s5 after self-assignment: '" << s5.c_str() << "' length=" << s5.length() << endl;
    // 测试 4：相等与不等比较
    cout << "s2 == s3? " << (s2 == s3 ? "true" : "false") << endl; // false
    cout << "s2 == s4? " << (s2 == s4 ? "true" : "false") << endl; // true
    cout << "s2 != s3? " << (s2 != s3 ? "true" : "false") << endl; // true
    // 测试 5：大小比较（字典序）
    cout << "s2 < s3? " << (s2 < s3 ? "true" : "false") << endl;   // true(H < W)
    cout << "s2 > s3? " << (s2 > s3 ? "true" : "false") << endl;   // false
    cout << "s2 <= s4? " << (s2 <= s4 ? "true" : "false") << endl; // true
    cout << "s2 >= s4? " << (s2 >= s4 ? "true" : "false") << endl; // true
    cout << "s5 > s2? " << (s5 > s2 ? "true" : "false") << endl;   // true (Hello World > Hello)
                                                                   // 测试 6：索引访问与修改
    cout << "s2[0] = " << s2[0] << endl;
    s2[0] = 'h';
    cout << "After s2[0]='h': " << s2.c_str() << endl;
    // 此时 s2 为 "hello" (注意 ASCII: 'h'=104, 'H'=72)
    cout << "Now s2 < s4? " << (s2 < s4 ? "true" : "false") << endl; // false(因为 'h' > 'H')
    // 测试 7：空字符串操作
    String s7;
    String s8 = s7 + s2;
    cout << "s7 (empty) + s2: '" << s8.c_str() << "' length=" << s8.length() << endl;
    cout << "s7 < s2? " << (s7 < s2 ? "true" : "false") << endl;   // true(空串小于非空)
    cout << "s7 == s7? " << (s7 == s7 ? "true" : "false") << endl; // true
    return 0;
}