#include <iostream>
using namespace std;

// 바로 생각해서 구현하는 버블정렬
int main()
{
	int n, temp;
	int array[10];

	cout << "요소 갯수를 입력하시오(<= 10): ";
	cin >> n;

	cout << "입력된 " << n << " 요소 수: ";
	for (int i = 0; i < n; i++)
		cin >> array[i];

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	cout << "정렬된 배열: ";
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}
