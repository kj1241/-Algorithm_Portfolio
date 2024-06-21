#include <iostream>
#include <coroutine>
#include <exception>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <string>
#include <windows.h>
#include <psapi.h>
#include <conio.h>
#include <ctime>


//
//long long int Fibonacci(int num)
//{
//	long long int answer = 0;
//	bool flag = false;
//	long long int a = 0, b = 1;
//
//	if (num < 1)
//		return 0;
//	if (num = 1)
//		return 1;
//
//	for (int i = 0; i < num - 1; ++i)
//	{
//		if (!flag)
//		{
//			a += b;
//			flag = true;
//		}
//		else
//		{
//			b += a;
//			flag = false;
//		}
//	}
//	return (a > b) ? answer = a : answer = b;
//}
//
//int main()
//{
//	PROCESS_MEMORY_COUNTERS_EX pmc;
//	memset(&pmc, 0, sizeof(PROCESS_MEMORY_COUNTERS_EX));
//	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);
//
//	clock_t start, end;
//	double duration;
//
//	start = std::clock();
//	{
//		std::cout << "�Ǻ���ġ ���� 50 ���: " << Fibonacci(50) << "\n";
//	}
//	end = std::clock();
//	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));
//
//	std::cout << "���� ���� ���� �ð�: " << end - start << "\n";
//	std::cout << "���� ���� �޸�: " << pmc.PrivateUsage << "\n";
//	std::cout << "���� ���� �޸�: " << pmc.WorkingSetSize << "\n";
//}


unsigned long long int Fibonacci(int num)
{
	long long int answer = 0;
	bool flag = false;
	long long int a = 0, b = 1;

	if (num < 1)
		return 0;
	if (num == 1)
		return 1;

	for (int i = 0; i < num - 1; ++i)
	{
		if (!flag)
		{
			(a += b) %= 18446744073709551615;
			flag = true;
		}
		else
		{
			(b += a) %= 18446744073709551615;
			flag = false;
		}
	}
	return (a > b) ? answer = a : answer = b;
}

int main()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	memset(&pmc, 0, sizeof(PROCESS_MEMORY_COUNTERS_EX));
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	clock_t start, end;
	double duration;

	start = std::clock();
	{
		for (int i = 0; i < 100001; ++i)
			std::cout << "�Ǻ���ġ ����" << i << " ���: " << Fibonacci(i) << "\n";
	}
	end = std::clock();
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));

	std::cout << "���� ���� ���� �ð�: " << end - start << "\n";
	std::cout << "���� ���� �޸�: " << pmc.PrivateUsage << "\n";
	std::cout << "���� ���� �޸�: " << pmc.WorkingSetSize << "\n";
}