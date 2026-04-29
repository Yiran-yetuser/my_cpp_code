#include <iostream>
using namespace std;

// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
// 稳定
template <typename T>
void insertion_sort(T arr[], int len)
{
    for (int i = 1; i < len; i++) {
        T key = arr[i];
        int j = i - 1;
        while ((j >= 0) && (key < arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, len);
    cout << "Sorted array: ";
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}