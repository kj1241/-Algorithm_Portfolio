
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>
#include <variant>
#include <set>

using namespace std;
using namespace std::literals;

using ms = std::chrono::milliseconds;
using us = std::chrono::microseconds;
using ns = std::chrono::nanoseconds;

struct Time {
    std::variant<ms, ns, us> time;
    auto convert_time(const auto& convert) {
        return std::visit(convert, time);
    }
    Time(std::variant<ms, ns, us> t) :time(t) {};
};

template <typename T>
constexpr auto duration_cast = [](auto& time) {
    return std::chrono::duration_cast<T>(time);
};

template <typename... T>
struct overload : T...
{
    using T::operator()...;
};

template <typename... T>
overload(T...)->overload<T...>;


template <typename... T>
struct overload2 : T...
{
    using T::operator()...;
};


auto foo(auto ... args)
{
    std::cout << sizeof...(args) << "\n";
}

template <typename ...Args>
auto delay_invoke_foo(Args...args)
{
    std::cout << "A" << ": ";
    ((std::cout << args << " "), ...) << "\n";
    return[args...]()->decltype(auto) {
        std::cout << "B" << ": ";
        ((std::cout << args << " "), ...) << "\n";
        return foo(args...);
    };
}

class temp
{
    //auto f= []{};
    decltype([]() {}) f;
};

using pair_item = std::pair<char, double>;

struct compare
{
    bool operator()(const pair_item& lhs, const pair_item& rhs) const
    {
        return lhs.second < rhs.second;
    }
};

template<auto = [] {} >
struct foo2 { /* ... */ };

int main() {
    Time t(us(3000));
    //std::cout << t.convert(std::chrono::duration_cast<us>).count(); //¿¡·¯ 
    std::cout << t.convert_time(duration_cast<ms>).count();

    auto add = overload{
        [](int a,int b) { return a + b; },
        [](float a, float b) {return a + b; }
    };

    std::cout << add(3, 4) << "\n";
    std::cout << add(4.2f, 5.3f) << "\n";

    auto add2 = overload2{
        [](int a,int b) { return a + b; },
        [](float a, float b) {return a + b; }
    };

    std::cout << add2(3, 4) << "\n";
    std::cout << add2(4.2f, 5.3f) << "\n";

    delay_invoke_foo("hellow", 3)();

    std::vector vc = { 1,2,3,4,5,6,7,8 };
    std::erase_if(vc, [](const auto& i) {
        return i % 2;
        });

    for (auto e : vc)
    {
        std::cout << e << " ";
    }

    std::vector vc2 = { 1,2,3,4,5,6,7,8 };
    std::erase_if(vc2, []<typename T>(const T i) {
        return i % 2;
    });

    for (const auto e : vc2)
    {
        std::cout << e << " ";
    }

    std::unique_ptr<int, decltype([](int* p) { delete p; }) > pVal(new int);

    std::set < pair_item, compare > pq;
    pq.emplace('C', 30);
    pq.emplace('A', 20);
    pq.emplace('B', 10);

    for (auto e : pq)
        std::cout << e.first << "\n";


    std::set < pair_item, decltype([](auto e1, auto e2) {
        std::cout << "e1: " << e1.first;
        std::cout << " e2: " << e2.first;
        std::cout << "\n";
        return e1.second < e2.second;
        }) > pq2;

    pq2.emplace('C', 30);
    pq2.emplace('A', 20);
    pq2.emplace('B', 10);

    for (auto e : pq2)
        std::cout << e.first << "\n";

    foo2<> f1;
    foo2<> f2;

    typeid(decltype(f1)) == typeid(decltype(f2)) ? std::cout << "true" : std::cout << "false";
}
