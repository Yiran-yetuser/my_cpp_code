#include <cmath>
#include <iostream>
using namespace std;

const int IMG_WIDTH = 64;
const int IMG_HEIGHT = 64;

// 完成 SobelEdgeDetector 类的定义
// 你的代码开始
class SobelEdgeDetector
{
private:
    static const int Gx[3][3];
    static const int Gy[3][3];

public:
    SobelEdgeDetector();
    void applySobel(
        const unsigned char input[IMG_HEIGHT][IMG_WIDTH],
        unsigned char output[IMG_HEIGHT][IMG_WIDTH]);
    ~SobelEdgeDetector();
};
const int SobelEdgeDetector::Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int SobelEdgeDetector::Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

SobelEdgeDetector::SobelEdgeDetector()
{
    cout << "Detector initialized." << endl;
}

void SobelEdgeDetector::applySobel(
    const unsigned char input[IMG_HEIGHT][IMG_WIDTH],
    unsigned char output[IMG_HEIGHT][IMG_WIDTH])
{
    for (int i = 1; i < IMG_HEIGHT - 1; i++) {
        for (int j = 1; j < IMG_WIDTH - 1; j++) {
            int sumX = 0, sumY = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sumX += input[i + k][j + l] * Gx[k + 1][l + 1];
                    sumY += input[i + k][j + l] * Gy[k + 1][l + 1];
                }
            }
            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            output[i][j] = (magnitude > 255) ? 255 : magnitude;
        }
    }
}

SobelEdgeDetector::~SobelEdgeDetector()
{
    cout << "Detector destroyed." << endl;
}

// 你的代码结束

int main()
{
    // 构建一个简单测试图像（例如一个白色方块在黑色背景上）
    unsigned char testImg[IMG_HEIGHT][IMG_WIDTH] = {0};
    for (int i = 20; i < 40; i++)
        for (int j = 20; j < 40; j++)
            testImg[i][j] = 255;

    unsigned char edgeImg[IMG_HEIGHT][IMG_WIDTH] = {0};

    SobelEdgeDetector detector;
    detector.applySobel(testImg, edgeImg);

    // 简单输出部分边缘强度（非零）
    cout << "Edge strengths around boundary:" << endl;
    for (int i = 18; i < 22; i++) {
        for (int j = 18; j < 22; j++) {
            cout << (int)edgeImg[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
