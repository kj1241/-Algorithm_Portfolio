#include <iostream>
using namespace std;

// �ٷ� �����ؼ� �����ϴ� ��������
int main()
{
	int n, temp;
	int array[10];

	cout << "��� ������ �Է��Ͻÿ�(<= 10): ";
	cin >> n;

	cout << "�Էµ� " << n << " ��� ��: ";
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

	cout << "���ĵ� �迭: ";
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}
