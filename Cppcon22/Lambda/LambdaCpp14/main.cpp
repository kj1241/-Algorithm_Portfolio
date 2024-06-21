#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <algorithm>


std::map<int, std::string> Arrow{
	{0, "Up"},
	{1, "Down"},
	{2, "Left"},
	{3, "Right"}
};

int main()
{
	std::for_each(Arrow.begin(), Arrow.end(), [](const auto& item) {
		std::cout << item.first << ": " << item.second << "\n";
		});


	std::vector<std::string> vs;
	const std::string lastfix = "X";
	for (int i = 0; i < 10000; ++i)
		vs.push_back("temp" + std::to_string(i));
	vs.push_back("tempX");

	auto startTime = std::chrono::high_resolution_clock::now();
	auto result = std::find_if(vs.begin(), vs.end(), [&lastfix](const std::string s) {
		return s == "temp" + lastfix;
		});
	auto endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
	double seconds = duration.count();

	std::cout << "클로져 함수 실행 시간: " << seconds << " 초" << "\n";

	if (result != vs.end())
		std::cout << lastfix << "\n";


	std::vector<std::string> vs2;
	const std::string lastfix2 = "X";
	for (int i = 0; i < 10000; ++i)
		vs2.push_back("temp" + std::to_string(i));
	vs2.push_back("tempX");

	auto startTime2 = std::chrono::high_resolution_clock::now();
	auto result2 = std::find_if(vs2.begin(), vs2.end(), [str = "temp" + lastfix2](const std::string s) {
		return s == str;
	});
	auto endTime2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duration2 = std::chrono::duration_cast<std::chrono::duration<double>>(endTime2 - startTime2);
	double seconds2 = duration2.count();

	std::cout << "매개변수 초기화 실행 시간: " << seconds2 << " 초" << "\n";

	if (result2 != vs2.end())
		std::cout << lastfix2 << "\n";
}


