#include "Convert.h"
#include <iostream>

int main()
{
    Convert con(1234, 16); // 对象调构造函数，其中 1234 是待转换的十进制数,16 表示 16 进制
    con.conv();            // 调用转换函数
    con.show();            // 调用输出函数
    return 0;
}