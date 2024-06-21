#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <future>

class Person
{
public:
    int name;
};


int add(int i) //������
{
    return i + i;
}

void LegacyEx(int(*f)(int)) //�����Ʈ
{
    std::cout << "10�� ���갪�� " << f(10) << "�Դϴ�.\n";
}

template<typename Functor>
void temp(Functor functor)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000000; ++i)
    {
        functor();
    }
    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
    double seconds = duration.count();

    std::cout << "ĸ�� ���� �ð�: " << seconds << " ��" << "\n";
}

struct X {
    void printAsync() {
        std::async([this] {
            std::cout << a + b << "\n";
            });
    }

private:
    int a = 3;
    int b = 4;
};


struct Temp
{
    bool isNumber = 0;
    int value = 10;
    int x_value = 20;
    int y_value = 30;
    int z_value = 40;
};

int value(Temp temp)
{
    if (temp.isNumber == 0)
        return temp.x_value;
    else if (temp.isNumber == 1)
        return temp.y_value;
    else
        return temp.z_value;
}

struct oneCall {
    oneCall(int& i) {
        static auto _ = [](int& j) mutable {
            ++j;
            std::cout << "call fuction" << "\n";
            return 0;
        }(i); // _ : ������ �Լ�
    }
};



int main() {

    [](const Person& lhs, const Person& rhs)
    {
        return lhs.name < rhs.name;
    };

    [](const Person& lhs, const Person& rhs) mutable
    {
        return lhs.name < rhs.name;
    };

    [](const Person& lhs, const Person& rhs) -> bool
    {
        return lhs.name < rhs.name;
    };


    LegacyEx(add); //�Լ� ������ 
    LegacyEx([](int i) { return i + i; }); // ����


    //auto *fuc = [](int i) { return i + i; }; <- ���� ����: ���� ��ü�� Ÿ�� �߷кҰ�
    auto* fuc = static_cast<int(*)(int)>([](int i) { return i + i; }); // �Ͻ�����ȯ -> �������ȯ
    std::cout << fuc << "\n";

    auto* fuc2 = +([](int i) { return i + i; }); // �ᱹ �Ͻ�����ȯ�� �̷����
    //auto * fuc2 = +([](auto i) { return i+i }); //C++14 error �ᱹ �ڵ尡 ���ϰ��� ������ �� ����.
    std::cout << fuc2 << "\n";

    int i1, j1 = 0;
    auto f = [](int i1) {return i1; }; //�ܺ� ������ ������� ����

    int i2, j2 = 0;
    auto f0 = [=]() {return i2 == j2; };

    int i3 = 1;

    auto f1 = [=]() mutable { return &i3; };
    auto f2 = [&]() mutable { return &i3; };

    std::cout << "�ּ� �� i3: " << &i3 << " / �ּ� �� f1: " << f1() << "\n";
    std::cout << "�ּ� �� i3: " << &i3 << " / �ּ� �� f2: " << f2() << "\n";

    int i4 = 1;
    int i5 = 2;

    auto f3 = [=]() mutable { i4 = 10; };
    auto f4 = [&]() mutable { i5 = 20; };

    temp(f3);
    temp(f4);

    X x;
    x.printAsync();

    static int a = 0; //���������μ� �����Ϳ����� �ö�
    auto f5 = [=]() {return a; }; // �Լ� ����� �Ͼ���� �������������� ����� ��������ϴ�.
    auto f6 = []() {return a; };

    std::vector<int> temps;
    Temp temp;

    temps.push_back(value(temp)); // �������� ����
    temps.push_back([&temp]() {
        if (temp.isNumber == 0)
            return temp.x_value;
        else if (temp.isNumber == 1)
            return temp.y_value;
        else
            return temp.z_value;
        }()); //���ٷ� ���� ���� ���� ���

    int i6 = 0;

    oneCall x1(i6);
    oneCall x2(i6);
    oneCall x3(i6);

    std::cout << i6 << "\n";
}