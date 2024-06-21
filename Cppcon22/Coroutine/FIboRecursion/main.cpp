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


long long int Fibonacci(int num)
{
	if (num < 1)
		return 0;
	else if (num == 1)
		return 1;
	else
		return (Fibonacci(num - 1) + Fibonacci(num - 2));
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
		std::cout << Fibonacci(50) << "\n";
	}
	end = std::clock();
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));

	std::cout << "현재 로직 동작 시간: " << end - start << "\n";
	std::cout << "현재 가상 메모리: " << pmc.PrivateUsage << "\n";
	std::cout << "현재 물리 메모리: " << pmc.WorkingSetSize << "\n";
}
