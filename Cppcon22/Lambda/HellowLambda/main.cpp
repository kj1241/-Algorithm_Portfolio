
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>


//��ɾ� ���
int add(int i) //������
{
    return i + i;
}


//�Լ��� ���
int input_data(int(*f)(int)) //������
{
    return f(10);
}

int main() {

    int number = 10; //�Է� ��
    std:: cout << add(10) << "\n"; //��� -> ����� 

    auto f = [](int i) {return i + i; }; // �Է� ����
    std::cout << input_data(f) << "\n"; //��� -> ����� 
}