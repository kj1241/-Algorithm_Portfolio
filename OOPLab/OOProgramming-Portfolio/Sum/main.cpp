#include <iostream>
using namespace std;

int main()
{
    int n = 100;
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += (i + 1);
    cout << sum << endl; // O(n)

    cout << (n + 1) * n / 2 << endl; // O(1)

    return 0;
}
