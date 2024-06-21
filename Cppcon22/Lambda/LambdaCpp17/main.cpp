#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>
#include <variant>
#include <array>

int add(int a, int b)
{
	return a + b;
}

float add(float a, float b)
{
	return a + b;
}

template <typename... T>
struct overload : T...
{
	using T::operator()...;
};

template <typename... T>
overload(T...)->overload<T...>;

auto add3 = overload{
	[](int a,int b) { return a + b; },
	[](float a, float b) { return a + b; }
};

template <typename... T>
struct overload2 : T...
{
	using T::operator()...;
	int dummy = 0;
};

template <typename... T>
overload2(T...)->overload2<T...>;


int main()
{
	auto f = [](auto && ... args) { // '...'  c++17 이상부터
		//(std::cout << ... << args); //output:: hellow world19C38.5
		((std::cout << args << "\n"), ...);
	};

	f("hellow world", 19, "C", 38.5);

	auto f0 = [](int i) constexpr {
		return i;
	};

	std::array<int, f0(3)> arr = {};
	std::cout << arr.size() << "\n";

	std::cout << add(3, 4) << "\n";
	std::cout << add(4.2f, 5.3f) << "\n";
	//std::cout<< add(3 , 4.5f) << "\n"; //error

	//에러
	//auto add2 = overload{
	//	[](int a,int b) { return a + b; },
	//	[](float a, float b) { return a + b; }
	//};

	//std::cout << add2(3, 4) << "\n";
	//std::cout << add2(4.2f, 5.3f) << "\n";

	std::cout << add3(3, 4) << "\n";
	std::cout << add3(4.2f, 5.3f) << "\n";

	auto add4 = overload{
		[n = 0] (int a,int b) { return a + b; },
		[n = 0](float a, float b) {return a + b; }
	};

	std::cout << add4(3, 4) << "\n";
	std::cout << add4(4.2f, 5.3f) << "\n";

	auto add5 = overload2{
		[](int a,int b) { return a + b; },
		[](float a, float b) {return a + b; }
	};

	std::cout << add5(3, 4) << "\n";
	std::cout << add5(4.2f, 5.3f) << "\n";
}