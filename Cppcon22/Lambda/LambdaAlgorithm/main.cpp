#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>

struct Person
{
    std::string name;
    int timeOfJoin;
};

std::vector<Person> people(50000);

static bool compare(Person lhs, Person rhs) {
    return lhs.name < rhs.name;
}

int main()
{
    for (int i = 0; i < 50000; ++i)
    {
        people[i].name = "Kim" + std::to_string(10000 - i);
        people[i].timeOfJoin = i;
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    std::sort(people.begin(), people.end(), [](const Person& lhs, const Person& rhs) {return lhs.name < rhs.name; }); //이름순 비교
    //std::sort(people.begin(), people.end(), compare);
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
    double seconds = duration.count();

    for (auto p : people)
        std::cout << p.name << " " << p.timeOfJoin << "\n";

    std::cout << "람다 알고리즘 실행 시간: " << seconds << " 초" << "\n";
}
