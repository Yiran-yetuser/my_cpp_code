#include <iostream>
using namespace std;

// 时间复杂度：O(n^(3/2))，最坏情况为O(n^2)
// 空间复杂度：O(1)
// 不稳定
template <typename T>
void shell_sort(T array[], int length)
{
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                std::swap(array[j], array[j - h]);
            }
        }
        h = h / 3;
    }
}

// 测试函数
int main()
{
    int arr[] = {12, 34, 54, 2, 3};
    int length = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    shell_sort(arr, length);

    cout << "Sorted array: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}