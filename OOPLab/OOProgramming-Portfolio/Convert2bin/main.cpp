//10진수를 2진수로 변환
#include <iostream>
using namespace std;

void convert2bin(int dec)
{
    if (dec <= 0) return;
    convert2bin(dec / 2);
    cout << dec % 2;
}

int main()
{
    int n;
    cout << "input number:";
    cin >> n;
    convert2bin(n);
    cout << "\n";
    return 0;
}
