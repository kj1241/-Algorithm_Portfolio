//¹è¿­ µ¡¼À
#include <iostream>
using namespace std;

int arr1[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
int arr2[3][3] = { 1, 2, 3, 4, 5, 6, 7 };

void AddAry(int* param, int len, int add)
{
    int i;
    for (i = 0; i < len; ++i)
        param[i] += add;
}

int main(void)
{
    int arr[3] = { 1, 2, 3 };
    AddAry(arr, sizeof(arr) / sizeof(int), 1);

    for (int i = 0; i <  3; ++i)
    {
        cout << i << ": " << arr[i]<<" / ";
    }
}
