#include <iostream>
using namespace std;

int arr[100][100] = { 0, };

int main()
{
    int n;
    cout << "시작 수를 입력하세요 n: ";
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

    return 0;
}
