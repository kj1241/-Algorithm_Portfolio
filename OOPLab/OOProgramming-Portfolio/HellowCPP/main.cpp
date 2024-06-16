#include <iostream>
using namespace std;


int main()
{
	int a = 1, b = 2, c = 3;
	a = b;
	b = a;
	
	cout << "a:" << a << " b:" << b << " c:" << c << endl;

	int temp = a;
	a = b;
	b = c;
	c = temp;

	cout <<"a:" << a << " b:" << b << " c:" << c << endl;

	a = a - b;
	b = b + a;
	a = b - a;

	cout <<"a:" << a << " b:" << b << " c:" << c << endl;

	return 0;
}