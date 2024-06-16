
#include <iostream>

using namespace std;
/*
int arr1[3][3] = { 1,2,3,4,5,6,7,8,9 }

int arr2[3][3] = [1, 2, 3, 4, 5, 6, 7}

void AddAry(int* param, int len, int add)
{
	int i;
	for (i = 0; i < len; i++)
		param[i] += add;
}




int main(void)
{
	int arr[3] = { 1,2,3 };
	AddAray(arr, sizeof(arr) / sizeof(int), 1);
}

*/


int arr[100][100] = { 0, };


int main()
{
	int n;    
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (i == 0 || j == 0)
				arr[i][j] = 1;
			else
				arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}
