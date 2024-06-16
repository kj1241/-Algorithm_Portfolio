#include<iostream>

using namespace std;
/*
//�ٷ� �����ؼ� �����ϴ� ��������
int main()
{
	int n, swap;
	int array[10];

	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> array[i];
	for(int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				swap = array[j];
				array[j] = array[j + 1];
				array[j + 1] = swap;
			}
		}

	}
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
}
*/
/*
// ���õ� ��������
void bubble_sort(int a[], int size)
{
	int tmp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (a[i] > a[j]) {
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}
*/
/*
//�ٷ� �����ؼ� �����ϴ� ��������
void select_sort(int a[], int size)  
{
	int min;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{

			min = i;
			if (a[min] > a[j])
				min = j;

		}
		if (min != i)
		{
			int temp;
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;

		}
	}
}
*/

/*
//���õȼ��� ����
void SelectionSort(int* arr, int size)
{
	int min, indexMin, temp;
	for (int i = 0; i < size - 1; i++)
	{
		indexMin = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[indexMin]) {
				indexMin = j;
			}
		}
		temp = arr[indexMin];
		arr[indexMin] = arr[i];
		arr[i] = temp;
		//cout <<i << �� �ܰ� : ��;
		//print_arr(arr, size);
	}
}
*/
/*
//�ٷ� �����ؼ� ������ ��������
//������: ������ü�� �ð��� �ɸ��µ� ������� �ð� ����. ����ȭ�� �����߾�ߵ�
void insert_sort(int* arr, int size)
{
	for (int i = 0; i < size;i++)
	{
		for (int j = i + 1; j >= 0 ; j--)
		{
			if (arr[j - 1] > arr[j]) 
				swap(arr[j - 1], arr[j]); 
			else  
				continue;  

		}
		
	}
}
*/
/*
//���õ� ��������
void InsertionSort(int* arr, int size)
{
	int j, remember;
	for (int i = 1; i < size; i++)
	{
		remember = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > remember)
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j + 1] = remember;
		//cout << i << " �ܰ� : ";
		//print_arr(arr, size);
	}
}
//continue��  break ���� continue�� �̹� i=3 �̶�� �ٷ� i=4�� ���� break �� for�� Ż�� 
*/
/*
int main()
{
	int a[] = { 15, 2, 24, 18, 7, 13, 12, 4, 21, 9 };

	
}
*/
// Quicksort()
void print_array(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int partition(int *a, int left, int right) {
	int pivot = right;
	int i = left - 1;
	int j = left;
	int tmp;

	if (left < right) {
		while (j < right) {
			if (a[j] < a[pivot]) {
				tmp = a[j]; a[j] = a[i + 1]; a[i + 1] = tmp;
				i++;
			}
			j++;
		}
		tmp = a[pivot]; a[pivot] = a[i + 1]; a[i + 1] = tmp;
	}
	pivot = i + 1;

	return pivot;
}

void quickSort(int *a, int left, int right)
{
	if (left < right)
	{
		int pivot = partition(a , left, right);
		quickSort(a, left, pivot - 1);
		quickSort(a, pivot + 1, right);
	}
}

int LinearSearch(int* arr, int size, int target)
{
	int i;
	for(i=0; i<size; i++)
		if (arr[i] == target)
		{
			return i;
		}
	return -1;
}

int binarySearch(int* a, int first, int last, int target)
{
	int mid;
	if (first > last)
		return -1;
	mid = (first + last) / 2;
	if (a[mid] == target)
		return mid;
	else if (target < a[mid])
		return binarySearch(a, first, mid - 1, target);
	else
		return binarySearch(a, mid + 1, last, target);
}

int interpolationSearch(int* a, int first, int last, int target)
{
	int mid;
	if (first > last)
		return -1;
	mid = ((double)(target - a[first]) / (a[last] - a[first]) * (last + first)) + first;
	if (a[mid] == target)
		return mid;
	else if (target < a[mid])
		return interpolationSearch(a, first, mid - 1, target);
	else
		return interpolationSearch(a, mid + 1, last, target);
}

int main()
{
	int a[10] = { 15, 2, 24, 18, 7, 13, 12, 4, 21, 9 };
	print_array(a, 10);
	quickSort(a, 0, 9);
	print_array(a, 10);
	int value=15;
	//int idx = LinearSearch(a, 10, value);
	//int idx = binarySearch(a, 0, 9, 9)+1;
	int idx = interpolationSearch(a, 0, 9, 9)+1;
	if (idx != -1)
		cout << idx << endl;

}