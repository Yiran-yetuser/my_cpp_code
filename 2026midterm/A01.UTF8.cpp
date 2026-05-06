#include <cmath>
#include <cstdint> // 用于 BMP 文件头中的定长整数类型
#include <cstdio>
#include <iostream>
using namespace std;

// ================== 学生需要实现的代码开始 ==================
// TODO: 写一个RGB类
class RGB
{

private:
    // 按要求完成员变量的定义
    unsigned char r; // 红色，存储 0~255 的通道值
    unsigned char g; // 绿色，存储 0~255 的通道值
    unsigned char b; // 蓝色，存储 0~255 的通道值

public:
    // 按要求完成员函数的定义
    RGB() : r(0), g(0), b(0) {};
    RGB(int red, int green, int blue);
    RGB(double hue, double saturation, double value);
    unsigned char getR() const
    {
        return r;
    };
    unsigned char getG() const
    {
        return g;
    };
    unsigned char getB() const
    {
        return b;
    };
};

RGB::RGB(int red, int green, int blue)
{
    if (red < 0) {
        r = 0;
    } else if (red > 255) {
        r = 255;
    } else {
        r = red;
    }
    if (green < 0) {
        g = 0;
    } else if (green > 255) {
        g = 255;
    } else {
        g = green;
    }
    if (blue < 0) {
        b = 0;
    } else if (blue > 255) {
        b = 255;
    } else {
        b = blue;
    }
}

double clamp(double val, double min, double max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}
RGB::RGB(double hue, double saturation, double value)
{
    // if (hue >= 360) {
    //     hue = hue - (hue / 360) * 360;
    // } else if (hue < 0) {
    //     while (hue < 0) {
    //         hue += 360;
    //     }
    // }
    hue = fmod(hue, 360.0);
    // if (saturation > 1.0) {
    //     saturation = 1.0;
    // } else if (saturation < 0.0) {
    //     saturation = 0.0;
    // }
    saturation = clamp(saturation, 0.0, 1.0);
    // if (value > 1.0) {
    //     value = 1.0;
    // } else if (value < 0.0) {
    //     value = 0.0;
    // }
    value = clamp(value, 0.0, 1.0);
    double H = hue / 60.0;
    double c = (1 - fabs(2 * value - 1)) * saturation,
           x = c * (1 - fabs(fmod(H, 2.0) - 1)),
           m = value - c / 2;
    double R, G, B;
    if (H >= 0 && H < 1) {
        R = c;
        G = x;
        B = 0;
    } else if (H >= 1 && H < 2) {
        R = x;
        G = c;
        B = 0;
    } else if (H >= 2 && H < 3) {
        R = 0;
        G = c;
        B = x;
    } else if (H >= 3 && H < 4) {
        R = 0;
        G = x;
        B = c;
    } else if (H >= 4 && H < 5) {
        R = x;
        G = 0;
        B = c;
    } else if (H >= 5 && H < 6) {
        R = c;
        G = 0;
        B = x;
    }
    r = clamp((R + m) * 255, 0, 255);
    g = clamp((G + m) * 255, 0, 255);
    b = clamp((B + m) * 255, 0, 255);
}

// 回答问题：
//  RGB 类同时提供了直接 RGB 构造和 HSL 构造两种创建对象的方式，
//  但是这两个构造都是三参的，且仅仅以三个int或三个 double 来区
//  分，这将会带来怎样的风险，有没有什么方法可以规避？
/*
答： 可能会产生构造函数重载冲突，因为int类型和double类型可以隐式转换；
同时降低代码可读性，调用者可能不清楚传入的三个参数是RGB还是HSL。
可以通过使用命名工厂函数来规避这个问题，例如：
如。static RGB fromRGB(int r, int g, int b) { return {r, g, b}; }
    static RGB fromHSV(double h, double s, double v) {
        // 转换算法
        return {...};
    }




*/

// ================== 学生需要实现的代码结束 ==================

// ========== 以下 drawBitmap 函数已提供，无须学生实现 ==========
// 功能：将 100×100 的 RGB 图像数据保存为 24 位 BMP 文件
// 参数：filename - 保存路径（如 "C:/image.bmp"）
//       image    - 二维 RGB 数组 [height][width]
//       width, height - 图像宽高（本题固定为 100）
void drawBitmap(const char *filename, RGB image[100][100],
                int width, int height)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        cerr << "Cannot open file: " << filename << endl;
        return;
    }

    // BMP 文件头 (14 字节)
    unsigned char bfType[2] = {'B', 'M'};
    uint32_t bfSize = 14 + 40 + width * height * 3; // 无调色板
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 14 + 40;

    fwrite(bfType, 1, 2, fp);
    fwrite(&bfSize, sizeof(bfSize), 1, fp);
    fwrite(&bfReserved1, sizeof(bfReserved1), 1, fp);
    fwrite(&bfReserved2, sizeof(bfReserved2), 1, fp);
    fwrite(&bfOffBits, sizeof(bfOffBits), 1, fp);

    // BMP 信息头 (40 字节)
    uint32_t biSize = 40;
    int32_t biWidth = width;
    int32_t biHeight = -height; // 负值表示自上而下存储
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24;
    uint32_t biCompression = 0;     // BI_RGB 不压缩
    uint32_t biSizeImage = 0;       // 不压缩时可设为 0
    int32_t biXPelsPerMeter = 2835; // 72 DPI
    int32_t biYPelsPerMeter = 2835;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;

    fwrite(&biSize, sizeof(biSize), 1, fp);
    fwrite(&biWidth, sizeof(biWidth), 1, fp);
    fwrite(&biHeight, sizeof(biHeight), 1, fp);
    fwrite(&biPlanes, sizeof(biPlanes), 1, fp);
    fwrite(&biBitCount, sizeof(biBitCount), 1, fp);
    fwrite(&biCompression, sizeof(biCompression), 1, fp);
    fwrite(&biSizeImage, sizeof(biSizeImage), 1, fp);
    fwrite(&biXPelsPerMeter, sizeof(biXPelsPerMeter), 1, fp);
    fwrite(&biYPelsPerMeter, sizeof(biYPelsPerMeter), 1, fp);
    fwrite(&biClrUsed, sizeof(biClrUsed), 1, fp);
    fwrite(&biClrImportant, sizeof(biClrImportant), 1, fp);

    // 像素数据 (BGR 顺序，自上而下，因为 biHeight 为负)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char bgr[3] = {
                image[i][j].getB(),
                image[i][j].getG(),
                image[i][j].getR()};
            fwrite(bgr, 1, 3, fp);
        }
        // width=100，每行 300 字节，已为 4 的倍数，无需填充
    }

    fclose(fp);
    cout << "Image saved to " << filename << endl;
}
// ==============================================================

// 请在此处完成 RGB 类的定义
// 你的代码开始

// 你的代码结束

int main()
{
    // 简单测试直接 RGB 构造及钳位
    RGB testColor(300, -20, 128);
    cout << "Test (300,-20,128): R=" << (int)testColor.getR()
         << " G=" << (int)testColor.getG()
         << " B=" << (int)testColor.getB() << endl;

    cout << endl;
    cout << "BITMAP TESTING ... \n";
    const int SIZE = 100;
    RGB img[SIZE][SIZE]; // 调用默认构造函数，初始化为黑色

    cout << "WRITING RGB ... \n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // 构建彩虹
            img[i][j] = RGB((i + j) * 360.0 / 2 / SIZE, 1.0, 0.5); // 使用直接 RGB 构造
        }
    }

    string filename = "C:/color_image.bmp";
    drawBitmap(filename.c_str(), img, SIZE, SIZE);

    string cmd = "start \"\" \"" + filename + "\"";
    system(cmd.c_str());

    cout << "OPEN BITMAP ... \n";

    return 0;
}
