#include <iostream>
using namespace std;

// 求最大公因数（欧几里得算法）
int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 阶乘计算
// 迭代版本
int factorialIter(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
// 递归版本
int factorialRec(int n)
{
    if (n <= 1)
        return 1;
    return n * factorialRec(n - 1);
}

// 斐波那契数列
//  递归版本（效率低，仅用于理解）
int fibonacciRec(int n)
{
    if (n <= 1)
        return n;
    return fibonacciRec(n - 1) + fibonacciRec(n - 2);
}
// 迭代版本（推荐）
int fibonacciIter(int n)
{
    if (n <= 1)
        return n;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// 通分分数加法
void fractionAddition(int n1, int d1, int n2, int d2, int &tempN, int &tempD)
{
    tempD = d1 * d2;
    tempN = n1 * d2 + n2 * d1;
}

// 约分
void fractionSimplify(int &n, int &d)
{
    int temp = gcd(n, d);
    n = n / temp;
    d = d / temp;
}

// 拆分正整数并统计各数字出现次数
void split(int num, int freq[])
{
    while (num > 0) {
        int digit = num % 10;
        freq[digit]++;
        num = num / 10;
    }
}

// 算出整数位数
int countDigits(int num)
{
    int count = 0;
    num = abs(num);

    do {
        count++;
        num /= 10;
    } while (num > 0);

    return count;
}

// 从小到大排序的bubble sort
void bubble(int *p, int n)
{
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (p[j] > p[j + 1]) {
                int tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
}
// 升序快速排序
void quickSort(int *arr, int low, int high)
{
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 实现字符串小写转换
// 注意,小写字母的ASCII值比大写字母大32！
void toLowercase1(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] <= 'Z' && str[i] >= 'A') {
            str[i] += 32;
        }
    }
}
// 或者,也可以使用<ctype>库的函数
void toLowercase2(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

// 字符串的字典比较法
int cmp(char *str1, char *str2)
{
    // 返回值为正，代表str1更大
    // 返回值为负，代表str2更大
    // 返回值为零，代表两者大小相同
    int i = 0;
    for (; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] > str2[i])
            return 1;
        else if (str1[i] < str2[i])
            return -1;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
        return 0;
    else if (str1[i] == '\0')
        return -1;
    else
        return 1;
}

// 任意进制打印数字
void PrintAny(unsigned int n, unsigned int base)
{
    if (n == 0) {
        cout << "0" << endl;
        return;
    }
    if (n < base) {
        cout << n;
        return;
    }
    // 终止条件：n<base或n=0时，n必然是最后一位
    else {
        PrintAny(n / base, base);
        cout << n % base;
    }
}

// 数乘运算
template <class A>
A MultiArray(const A *arr1, const A *arr2, const int len)
{
    A result = 0;
    for (int i = 0; i < len; i++) {
        result += arr1[i] * arr2[i];
    }
    return result;
}

/**
 * 顺序查找函数
arr 要查找的数组
size 数组大小
target 要查找的目标值
如果找到，返回目标值的索引；否则返回-1
 */
int sequentialSearch(const int arr[], int size, int target)
{
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // 找到，返回索引
        }
    }
    return -1; // 未找到
}

// 二维数组输出函数(第一个参变量要用*!!!,就是要传递的是mat的第一行第一列的地址!)
// 可以写如*mat,mat[0],&mat[0][0](类型都是int*)
// 如果写mat,传递的类型是int(*)[col],是指向整个第一行的指针
void show2Dmatrix(int *mat, int row, int col)
{
    int count = 0;
    for (int i = 0; i < row * col; i++) {
        cout << mat[i] << "\t";
        count++;
        if (count == col) {
            cout << endl;
            count = 0;
        }
    }
}

// 序列合并函数
/**
【算法说明】
有序序列归并的基本思想：
1) 设置i,j,k，分别表示数组arrA、数组arrB及合并后数组arrC的起始位置;
2) 比较i,j下标处元素的值，将较小的元素添加到结果数组中，并将对应下标值
向后移动一位。如：arrA[i]<arrB[j],则将arrA[i] 添加到结果数组arrC中，
i和k向后移一位；
3) 重复过程2），直至有一个数组中的元素已全部添加到结果数组中
4) 将另一个数组的剩余元素依次添加到结果数组的末尾
**/
int *merge(const int *arrA, int sizeA, const int *arrB, int sizeB, int &sizeC)
{
    int i = 0, j = 0, k = 0;
    sizeC = sizeA + sizeB;
    int *arrC = new int[sizeC];
    for (; k < sizeC; k++) {
        if (i >= sizeA) {
            arrC[k] = arrB[j];
            j++;
            continue;
        }
        if (j >= sizeB) {
            arrC[k] = arrA[i];
            i++;
            continue;
        }

        if (arrA[i] >= arrB[j]) {
            arrC[k] = arrB[j];
            j++;
        } else {
            arrC[k] = arrA[i];
            i++;
        }
    }
    return arrC;
}

int findMax(int arr[], int n)
{
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}
int findMin(int arr[], int n)
{
    int minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}
int sumArray(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
double averageArray(int arr[], int n)
{
    int sum = sumArray(arr, n);
    return static_cast<double>(sum) / n;
}
void reverseArray(int arr[], int n)
{
    int left = 0, right = n - 1;
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}
int stringLength(const char *str)
{
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
void stringCopy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
void stringConcat(char *dest, const char *src)
{
    int destLen = stringLength(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';
}
int stringCompare(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}
bool isPalindrome(const char *str)
{
    int len = stringLength(str);
    int left = 0, right = len - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
#include <cmath>
// 需要cmath库
bool isPerfectSquare(int n)
{
    if (n < 0)
        return false;
    int root = sqrt(n);
    return root * root == n;
}

// 计算组合数
// 方法1：使用公式 C(n,k) = C(n-1,k-1) + C(n-1,k)
int combination(int n, int k)
{
    if (k == 0 || k == n)
        return 1;
    return combination(n - 1, k - 1) + combination(n - 1, k);
}

// 方法2：使用公式 C(n,k) = n! / (k! * (n-k)!)
int combinationFormula(int n, int k)
{
    if (k > n - k)
        k = n - k; // 利用对称性减少计算

    long long result = 1;
    for (int i = 1; i <= k; i++) {
        result = result * (n - k + i) / i;
    }
    return result;
}
/*枚举
enum 枚举名 {
    标识符1,
    标识符2,
    标识符3,
    ...
};
*/