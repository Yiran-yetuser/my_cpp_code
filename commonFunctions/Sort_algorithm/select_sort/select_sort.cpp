#include <iostream>
using namespace std;

// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
// 不稳定
template <typename T> // 整數或浮點數皆可使用，若要使用物件（class）時必須設定大於（>）的運算子功能
void selection_sort(std::vector<T> &arr)
{
    for (int i = 0; i < arr.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[min])
                min = j;
        std::swap(arr[i], arr[min]);
    }
}
int main()
{
    vector<int> arr = {61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62};
    selection_sort(arr);
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ' ';
    cout << endl;
    vector<float> arrf = {17.5, 19.1, 0.6, 1.9, 10.5, 12.4, 3.8, 19.7, 1.5, 25.4, 28.6, 4.4, 23.8, 5.4};
    selection_sort(arrf);
    for (int i = 0; i < arrf.size(); i++)
        cout << arrf[i] << ' ';
    cout << endl;
    return 0;
}