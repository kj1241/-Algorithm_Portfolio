//팩토리얼 계산
#include <iostream>
using namespace std;

int factorial(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main()
{
    int i = 5; 
    cout << factorial(i);
    return 0;
}
