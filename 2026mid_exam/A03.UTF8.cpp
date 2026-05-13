#define _CRT_SECURE_NO_WARNINGS
#include <algorithm> // 用于 std::max
#include <cstring>
#include <iostream>
using namespace std;

// 初始容量常量（教师提供）
const int INIT_CAPACITY = 32;

// ================== 学生需要实现的代码开始 ==================
class FastString
{
private:
    char *data;
    int len; // 字符串长度（不含 '\0'）
    int cap; // 当前分配的数组容量（至少为 len+1）

    // 私有辅助：确保容量足够存放 needLen+1 个字符，并实现容量倍增策略
    // 该函数在需要扩容时会分配新的内存，复制旧数据，并释放旧内存
    // 可以在 operator+= 中调用此函数来确保有足够空间进行拼接
    // 也可以不使用此函数，直接在 operator+= 中实现扩容逻辑
    // 但使用此函数可以提高代码复用性和清晰度
    void ensureCapacity(int needLen)
    {
        if (len + needLen >= cap) {
            int newCap = max(cap * 2, len + needLen + 1);
            char *temp = new char[newCap];
            for (int i = 0; i < len; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            cap = newCap;
        }
    }

public:
    // 构造函数（C 串，默认为空串）
    FastString(const char *c = nullptr);

    // 深拷贝构造函数
    FastString(const FastString &a);

    // 深拷贝赋值运算符（自赋值安全）
    FastString &operator=(const FastString &a);

    // 析构函数
    ~FastString();

    // 获取字符串长度（不含 '\0'）
    int length();

    // 获取当前容量（字节数）
    int capacity();

    // += 拼接单个字符
    FastString &operator+=(char c);
    // += 拼接 C 风格字符chuan
    FastString &operator+=(const char *a);
    // += 拼接另一个 FastString
    FastString &operator+=(const FastString &a);
    // + 单个字符：基于拷贝构造和 += 实现，
    friend FastString operator+(const FastString &s, const char c);
    friend FastString operator+(const FastString &s, const char *c);
    friend FastString operator+(const FastString &s, const FastString &t);
    // 注意返回值类型必须为 FastString 而非 FastString&，
    // 且不得修改当前对象

    // + C 风格字符串：基于拷贝构造和 += 实现，要求同上
    friend FastString operator+=(const FastString &s, const char *a);
    // + C 另一个 FastString：基于拷贝构造和 += 实现，要求同上
    friend FastString operator+=(const FastString &s, const FastString &a);
    // 索引运算符（教师提供 const 和非 const 版本）
    char operator[](int index) const
    {
        if (index < 0 || index >= len)
            throw out_of_range("Index out of range");
        return data[index];
    }

    // 索引运算符（教师提供 const 和非 const 版本）
    char &operator[](int index)
    {
        if (index < 0 || index >= len)
            throw out_of_range("Index out of range");
        return data[index];
    }

    // 友元声明（如有必要）
    friend ostream &operator<<(ostream &os, const FastString &s);
};

// 输出流运算符实现
// 由于字符串可能过长，我们只输出开头和结尾各 80 个字符，中间用“……”隔开

// ================== 学生需要实现的代码结束 ==================

/*
==================== 回答问题（15%） ==========================
问: 采用了"容量倍增"策略，用户每次都重新通过本类提供的 operator+= 用于原地
    修改字符串，也调用基于 += 的 operator+。但是从资源管理和效率角度，分析
    为什么通常推荐使用 operator+= 进行连续拼接，而谨慎使用 operator+（尤其
    是在循环中）。如果你认为你的代码，或在特定场合下 operator + 也可以高效
    使用，请举例说明。

答:
因为 operator+ 通常会创建一个临时对象来存储拼接结果，需要额外的内存分配和数据复制，
在循环中连续使用 operator+ 时，开销会累积，导致性能显著下降。
operator+= 直接在原有对象上进行修改，避免了不必要的对象创建和内存操作，因此更高效。
在特定场合下，如果拼接的字符串数量较少，或者拼接操作不频繁，使用 operator+ 可能不会对性能产生明显影响。
例如，在一次性的字符串拼接中，使用 operator+ 可以使代码更简洁和易读，而不会引入显著的性能问题。
但在需要大量拼接的场景中，建议使用 operator+= 来优化性能。




==================== 程序优化（附加10%，可选）=================
期望优化得分：___3__分（学生填写）。

优化点1：将函数实现在类外，提升代码可读性


优化点2：


……

*/

int main()
{
    const int N = 10000;
    FastString log;
    log += "=== System Log Start ===\n";

    // 模拟大量小字符串拼接
    char numBuf[16];
    for (int i = 0; i < N; i++) {
        sprintf(numBuf, "%d", i);
        FastString entry = FastString("Event #") +
                           numBuf + FastString(" processed") + '.';

        log += "[INFO] ";
        log += entry;
        log += '\n';
    }
    log += "=== System Log End ===\n";

    cout << "Log length:   " << log.length() << " characters" << endl;
    cout << "Log capacity: " << log.capacity() << " bytes" << endl;

    // 输出开头和结尾各 80 个字符
    cout << log << endl;

    // 测试拷贝和赋值`

    cout << "\nTesting copy and assignment...\n"
         << endl;
    FastString copy = log;
    FastString assign;
    assign = log;
    cout << "Copy length:     " << copy.length() << endl;
    cout << "Copy Capacity:   " << copy.capacity() << endl;
    cout << "Assign length:   " << assign.length() << endl;
    cout << "Assign Capacity: " << assign.capacity() << endl;

    return 0;
}

/* 期望的输出示例（长度和容量可能因实现细节而异）：
Log length:   298938 characters
Log capacity: 524288 bytes

Head (80 chars):
=== System Log Start ===
[INFO] Event #0 processed.
[INFO] Event #1 processed.
[
...
Tail (80 chars):
FO] Event #9998 processed.
[INFO] Event #9999 processed.
=== System Log End ===


Testing copy and assignment...

Copy length:     298938
Copy Capacity:   524288
Assign length:   298938
Assign Capacity: 524288
*/

FastString::FastString(const char *c)
{
    if (c == nullptr) {
        data = new char[INIT_CAPACITY];
        data[0] = '\0';
        len = 0;
        cap = INIT_CAPACITY;
    } else {
        int clen = static_cast<int>(strlen(c));
        cap = max(clen + 1, INIT_CAPACITY);
        data = new char[cap];
        for (int i = 0; i < clen; i++) {
            data[i] = c[i];
        }
        data[clen] = '\0';
        len = clen;
    }
}

FastString::FastString(const FastString &a)
{
    len = a.len;
    cap = a.cap;
    data = new char[cap];
    for (int i = 0; i < len; i++) {
        data[i] = a.data[i];
    }
    data[len] = '\0';
}

FastString &FastString::operator=(const FastString &a)
{
    if (this != &a) {
        delete[] data;
        len = a.len;
        cap = a.cap;
        data = new char[cap];
        for (int i = 0; i < len; i++) {
            data[i] = a.data[i];
        }
        data[len] = '\0';
    }
    return *this;
}

FastString::~FastString()
{
    delete[] data;
    data = nullptr;
}

int FastString::length()
{
    return len;
}

int FastString::capacity()
{
    return cap;
}

FastString &FastString::operator+=(char c)
{
    ensureCapacity(1);
    data[len] = c;
    len++;
    data[len] = '\0';
    return *this;
}

FastString &FastString::operator+=(const char *a)
{
    int alen = strlen(a);
    ensureCapacity(alen);
    for (int i = len; i < len + alen; i++) {
        data[i] = a[i - len];
    }
    data[alen + len] = '\0';
    len += alen;
    return *this;
}

FastString &FastString::operator+=(const FastString &a)
{
    int alen = a.len;
    ensureCapacity(alen);
    for (int i = len; i < len + alen; i++) {
        data[i] = a.data[i - len];
    }
    data[alen + len] = '\0';
    len += alen;
    return *this;
}

FastString operator+(const FastString &s, const char c)
{
    FastString result(s);
    result += c;
    return result;
}

FastString operator+(const FastString &s, const char *c)
{
    FastString result(s);
    result += c;
    return result;
}

FastString operator+(const FastString &s, const FastString &t)
{
    FastString result(s);
    result += t;
    return result;
}

FastString operator+=(const FastString &s, const char *a)
{
    FastString result(s);
    result += a;
    return result;
}

FastString operator+=(const FastString &s, const FastString &a)
{
    FastString result(s);
    result += a;
    return result;
}

ostream &operator<<(ostream &os, const FastString &s)
{
    int displayLen = 80;
    if (s.len <= 2 * displayLen) {
        os << s.data;
    } else {
        os.write(s.data, displayLen);
        os << "……";
        os.write(s.data + s.len - displayLen, displayLen);
    }
    return os;
}
