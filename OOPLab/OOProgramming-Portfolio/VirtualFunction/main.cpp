#include <iostream>
#include <list>

using namespace std;

// ���� 1
class CBase
{
private:
    int baseNum;
public:
    CBase() : baseNum(0) {
        cout << "CBase ������1" << endl;
    }
    CBase(int n) : baseNum(n) {
        cout << "CBase ������2" << endl;
    }
    virtual ~CBase() {
        cout << "CBase �Ҹ���" << endl;
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
    CDerived() : CBase(), derivedNum(0) {  // ��������� �⺻ Ŭ������ �⺻ ������ ȣ��
        cout << "CDerived ������1" << endl;
    }
    CDerived(int n) : CBase(n), derivedNum(n) {  // ��������� �⺻ Ŭ������ �Ű����� ������ ȣ��
        cout << "CDerived ������2" << endl;
    }
    ~CDerived() {
        cout << "CDerived �Ҹ���" << endl;
    }
};

// ���� �Լ� ����
class CBase2
{
public:
    CBase2() {
        cout << "CBase2 ������" << endl;
    }
    virtual ~CBase2() {
        cout << "CBase2 �Ҹ���" << endl;
    }
    virtual void Func() { cout << "CBase2 Func()" << endl; }
};

class CDerived2 : public CBase2
{
public:
    CDerived2() {
        cout << "CDerived2 ������" << endl;
    }
    ~CDerived2() {
        cout << "CDerived2 �Ҹ���" << endl;
    }
    void Func() override { cout << "CDerived2 Func()" << endl; }
};

int main(void)
{
    cout << "---- CDerived ��ü ���� ----" << endl;
    CDerived d(10);
    cout << "---- CDerived ��ü �Ҹ� ----" << endl;

    cout << "---- ���� �Լ� ���� ----" << endl;
    CDerived2 z;
    CBase2* p = &z;
    p->Func();

    return 0;
}
