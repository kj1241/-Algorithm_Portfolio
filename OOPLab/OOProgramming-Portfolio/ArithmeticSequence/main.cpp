//재귀를 이용해서 1~n 합 등차수열 구하기
#include <iostream>
using namespace std;

int sum_re(int n)
{
	if (n == 1)
		return 1;
	else
	{
		return(sum_re(n - 1) + n);
	}
}

int main()
{
	cout << sum_re(4);
	return 0;
}

