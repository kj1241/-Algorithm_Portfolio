//피보나치 수열
#include <iostream>
using namespace std;

int Fibo(int n)
{
    if (n == 1 || n == 2)
        return 1;

    return Fibo(n - 2) + Fibo(n - 1);
}

int main()
{
    int i;
    for (i = 1; i <= 15; i++)
        cout << Fibo(i) << endl;
    return 0;
}
