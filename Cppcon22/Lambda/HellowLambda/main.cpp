
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>


//명령어 언어
int add(int i) //구현부
{
    return i + i;
}


//함수형 언어
int input_data(int(*f)(int)) //데이터
{
    return f(10);
}

int main() {

    int number = 10; //입력 값
    std:: cout << add(10) << "\n"; //계산 -> 결과값 

    auto f = [](int i) {return i + i; }; // 입력 람다
    std::cout << input_data(f) << "\n"; //계산 -> 결과값 
}