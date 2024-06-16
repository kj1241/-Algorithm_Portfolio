#include <iostream>
#include <list>

using namespace std;

// 숙제 1
class CBase
{
private:
    int baseNum;
public:
    CBase() : baseNum(0) {
        cout << "CBase 생성자1" << endl;
    }
    CBase(int n) : baseNum(n) {
        cout << "CBase 생성자2" << endl;
    }
    virtual ~CBase() {
        cout << "CBase 소멸자" << endl;
    }
protected:
    void Show() const {
        cout << "BaseNum: " << baseNum << endl;
    }
};

class CDerived : public CBase
{
private:
    int derivedNum;
public:
    CDerived() : CBase(), derivedNum(0) {  // 명시적으로 기본 클래스의 기본 생성자 호출
        cout << "CDerived 생성자1" << endl;
    }
    CDerived(int n) : CBase(n), derivedNum(n) {  // 명시적으로 기본 클래스의 매개변수 생성자 호출
        cout << "CDerived 생성자2" << endl;
    }
    ~CDerived() {
        cout << "CDerived 소멸자" << endl;
    }
};

// 가상 함수 예제
class CBase2
{
public:
    CBase2() {
        cout << "CBase2 생성자" << endl;
    }
    virtual ~CBase2() {
        cout << "CBase2 소멸자" << endl;
    }
    virtual void Func() { cout << "CBase2 Func()" << endl; }
};

class CDerived2 : public CBase2
{
public:
    CDerived2() {
        cout << "CDerived2 생성자" << endl;
    }
    ~CDerived2() {
        cout << "CDerived2 소멸자" << endl;
    }
    void Func() override { cout << "CDerived2 Func()" << endl; }
};

int main(void)
{
    cout << "---- CDerived 객체 생성 ----" << endl;
    CDerived d(10);
    cout << "---- CDerived 객체 소멸 ----" << endl;

    cout << "---- 가상 함수 예제 ----" << endl;
    CDerived2 z;
    CBase2* p = &z;
    p->Func();

    return 0;
}
