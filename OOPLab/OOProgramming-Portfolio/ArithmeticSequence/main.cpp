//��͸� �̿��ؼ� 1~n �� �������� ���ϱ�
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

