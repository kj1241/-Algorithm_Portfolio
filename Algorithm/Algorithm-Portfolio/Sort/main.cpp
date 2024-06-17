#include <iostream>
using namespace std;

// 제시된 버블정렬
void bubble_sort(int a[], int size)
{
    int tmp;
    for (int i = 0; i < size - 1; ++i)
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

// 바로 생각해서 구현하는 선택정렬
void select_sort(int a[], int size)
{
    int min;
    for (int i = 0; i < size; ++i)
    {
        min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (a[min] > a[j])
                min = j;
        }
        if (min != i)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

// 제시된 선택 정렬
void SelectionSort(int* arr, int size)
{
    int min, indexMin, temp;
    for (int i = 0; i < size - 1; ++i)
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
    }
}

// 바로 생각해서 구현한 삽입정렬
void insert_sort(int* arr, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j - 1] > arr[j])
                swap(arr[j - 1], arr[j]);
            else
                break;
        }
    }
}

// 제시된 삽입정렬
void InsertionSort(int* arr, int size)
{
    int j, remember;
    for (int i = 1; i < size; ++i)
    {
        remember = arr[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] > remember)
                arr[j + 1] = arr[j];
            else
                break;
        }
        arr[j + 1] = remember;
    }
}

// Quicksort
void print_array(int* a, int n)
{
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
}

//void quickSort(int arr[], int left, int right) 
//{
//    int i = left, j = right;
//    int pivot = arr[(left + right) / 2];
//
//    while (i <= j) {
//        while (arr[i] < pivot)
//            i++;
//        while (arr[j] > pivot)
//            j--;
//        if (i <= j) {
//            swap(arr[i], arr[j]);
//            i++;
//            j--;
//        }
//    }
//
//    if (left < j)
//        quickSort(arr, left, j);
//    if (i < right)
//        quickSort(arr, i, right);
//}

int partition(int* a, int left, int right) {
    int pivot = a[right];
    int i = left - 1;
    int tmp;

    for (int j = left; j < right; ++j) {
        if (a[j] < pivot) {
            i++;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    tmp = a[i + 1];
    a[i + 1] = a[right];
    a[right] = tmp;

    return i + 1;
}

void quickSort(int* a, int left, int right)
{
    if (left < right)
    {
        int pivot = partition(a, left, right);
        quickSort(a, left, pivot - 1);
        quickSort(a, pivot + 1, right);
    }
}


int LinearSearch(int* arr, int size, int target)
{
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}


//int binarySearch(int arr[], int left, int right, int value) {
//    while (left <= right) {
//        int mid = left + (right - left) / 2;
//
//        if (arr[mid] == value)
//            return mid;
//        if (arr[mid] < value)
//            left = mid + 1;
//        else
//            right = mid - 1;
//    }
//    return -1;
//}

int binarySearch(int* a, int first, int last, int target)
{
    if (first > last)
        return -1;
    int mid = (first + last) / 2;
    if (a[mid] == target)
        return mid;
    else if (target < a[mid])
        return binarySearch(a, first, mid - 1, target);
    else
        return binarySearch(a, mid + 1, last, target);
}


//int interpolationSearch(int arr[], int left, int right, int value)
//{
//   while (left <= right && value >= arr[left] && value <= arr[right]) {
//        if (left == right) {
//            if (arr[left] == value)
//                return left;
//            return -1;
//        }
//
//        int pos = left + ((double)(right - left) / (arr[right] - arr[left]) * (value - arr[left]));
//
//        if (arr[pos] == value)
//            return pos;
//        if (arr[pos] < value)
//            left = pos + 1;
//        else
//            right = pos - 1;
//    }
//    return -1;
//}

int interpolationSearch(int* a, int first, int last, int target)
{
    if (first > last)
        return -1;
    int mid = first + ((double)(target - a[first]) / (a[last] - a[first]) * (last - first));
    if (a[mid] == target)
        return mid;
    else if (target < a[mid])
        return interpolationSearch(a, first, mid - 1, target);
    else
        return interpolationSearch(a, mid + 1, last, target);
}

int main()
{
    int a[] = { 15, 2, 24, 18, 7, 13, 12, 4, 21, 9 };

    // 정렬 및 탐색 함수 호출 예시
    // bubble_sort(a, 10);
    // select_sort(a, 10);
    // insert_sort(a, 10);
    // SelectionSort(a, 10);
    // InsertionSort(a, 10);

    print_array(a, 10);
    quickSort(a, 0, 9);
    print_array(a, 10);

    int value = 15;
    int idx = LinearSearch(a, 10, value);
    // int idx = binarySearch(a, 0, 9, value);
    // int idx = interpolationSearch(a, 0, 9, value);

    if (idx != -1)
        cout << "요소의 인덱스 번호 : " << idx << endl;
    else
        cout << "요소를 찾지 못함" << endl;

    return 0;
}
