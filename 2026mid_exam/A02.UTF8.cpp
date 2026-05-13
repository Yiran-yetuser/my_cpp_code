#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

// ========== 教师提供的 Image 类 ==========================
class Image
{
public:
    static const int WIDTH = 64;
    static const int HEIGHT = 64;
    unsigned char data[HEIGHT][WIDTH];

    Image()
    {
        memset(data, 0, sizeof(data));
    }

    int getWidth() const { return WIDTH; }
    int getHeight() const { return HEIGHT; }

    // 生成复杂测试图像：包含渐变、条带等
    static Image createTestImage()
    {
        Image img;
        for (int i = 0; i < 64; i++)
            for (int j = 0; j < 64; j++)
                img.data[i][j] = i + j * 2;

        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j += 3) {
                img.data[i][j] = 128;
            }
        }

        for (int i = 0; i < 64; i += 3) {
            for (int j = 0; j < 64; j++) {
                img.data[i][j] = 200;
            }
        }
        return img;
    }
};
// ============================================================

// ================== 学生需要实现的代码开始 ==================
class ConvKernel
{
public:
    static const int KERNEL_SIZE = 3; // 定义卷积核大小为3×3

private:
    double data[KERNEL_SIZE][KERNEL_SIZE]; // 卷积核数据，3×3 的二维数组

public:
    ConvKernel(double v[KERNEL_SIZE * KERNEL_SIZE], int count);
    ~ConvKernel();
    // double *operator[](int row);
    const double *operator[](int row) const;
    int getRows() { return KERNEL_SIZE; };
    int getCols() { return KERNEL_SIZE; };

    // 友元函数声明（如有必要）
};

// 全局运算符重载：Image * ConvKernel，
// 注意，可以参照教师提供的 Conv 函数实现卷积逻辑，而非简单调用 Conv 函数实现 operator*

ConvKernel::ConvKernel(double v[KERNEL_SIZE * KERNEL_SIZE], int count)
{
    int idx = 0;
    for (int i = 0; i < KERNEL_SIZE; i++) {
        for (int j = 0; j < KERNEL_SIZE; j++) {
            data[i][j] = v[idx];
            idx++;
        }
    }
}

ConvKernel::~ConvKernel()
{
}

// double *ConvKernel::operator[](int row)
// {
//     return data[row];
// }

const double *ConvKernel::operator[](int row) const
{
    return data[row];
}

Image operator*(const Image &img, const ConvKernel &conv)
{
    Image result;
    int half = ConvKernel::KERNEL_SIZE / 2;
    for (int i = half; i < Image::HEIGHT - half; i++) {
        for (int j = half; j < Image::WIDTH - half; j++) {
            double sum = 0.0;
            for (int ki = -half; ki <= half; ki++) {
                for (int kj = -half; kj <= half; kj++) {
                    sum += conv[ki + half][kj + half] * img.data[i + ki][j + kj];
                }
            }
            if (sum < 0)
                sum = 0;
            if (sum > 255)
                sum = 255; // 钳位
            result.data[i][j] = (unsigned char)sum;
        }
    }
    return result;
}
// ================== 学生需要实现的代码结束 ==================

/*
==================== 回答问题（15%） =============================
问: 为什么不对 ConvKernel 类设计拷贝构造函数，且不对赋值运算符进行重载，
    其底层核心逻辑是什么？

答:因为 ConvKernel 类中没有动态分配内存资源，成员变量是一个固定大小的二维数组，
编译器提供的默认拷贝构造函数和赋值运算符已经能够正确地进行成员变量复制，因此不需要自定义拷贝构造函数和赋值运算符。
底层核心逻辑是：当类成员没有涉及动态内存管理时，编译器生成的默认函数足以满足需求，无需额外实现。




==================== 程序优化（附加10%，可选）====================
期望优化总分：_5__分（学生填写）

优化点1：


优化点2：将函数实现在类外，提升代码可读性


……

*/

// 原始卷积函数（教师提供），学生需参考它实现 operator*
Image Conv(const Image &img, const ConvKernel &conv)
{
    Image result;
    int half = ConvKernel::KERNEL_SIZE / 2; // 1
    for (int i = half; i < Image::HEIGHT - half; i++) {
        for (int j = half; j < Image::WIDTH - half; j++) {
            double sum = 0.0;
            for (int ki = -half; ki <= half; ki++) {
                for (int kj = -half; kj <= half; kj++) {
                    sum += conv[ki + half][kj + half] * img.data[i + ki][j + kj];
                }
            }
            if (sum < 0)
                sum = 0;
            if (sum > 255)
                sum = 255;
            result.data[i][j] = (unsigned char)sum;
        }
    }
    return result;
}

int main()
{
    double sobelXData[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    ConvKernel sobelX(sobelXData, 9);

    double sobelYData[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    ConvKernel sobelY(sobelYData, 9);

    Image testImg = Image::createTestImage();

    Image gradX = testImg * sobelX;
    Image gradY = testImg * sobelY;

    // 输出渐变边缘区域（行30-39，列30-39）
    cout << "Gradient X center values:" << endl;
    for (int i = 30; i < 40; i++) {
        for (int j = 30; j < 40; j++) {
            cout << setw(3) << (int)gradX.data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Gradient Y center values:" << endl;
    for (int i = 30; i < 40; i++) {
        for (int j = 30; j < 40; j++) {
            cout << setw(3) << (int)gradY.data[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

/* 期望的输出示例（仅供参考，实际数值可能因测试图像而异）：

Gradient X center values:
  8   0  72   8   0  60   8   0  48   8
 12   0 104  12   0  86  12   0  68  12
 12   0 103  12   0  85  12   0  67  12
  8   0  66   8   0  54   8   0  42   8
 12   0  95  12   0  77  12   0  59  12
 12   0  94  12   0  76  12   0  58  12
  8   0  60   8   0  48   8   0  36   8
 12   0  86  12   0  68  12   0  50  12
 12   0  85  12   0  67  12   0  49  12
  8   0  54   8   0  42   8   0  30   8

Gradient Y center values:
  4   6   6   4   6   6   4   6   6   4
  0   0   0   0   0   0   0   0   0   0
255 255 255 255 255 255 255 255 255 255
  4   6   6   4   6   6   4   6   6   4
  0   0   0   0   0   0   0   0   0   0
255 255 255 255 255 255 255 255 255 255
  4   6   6   4   6   6   4   6   6   4
  0   0   0   0   0   0   0   0   0   0
255 255 255 255 255 255 255 255 255 255
  4   6   6   4   6   6   4   6   6   4

*/
