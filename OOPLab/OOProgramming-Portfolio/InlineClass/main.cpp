#include <iostream>

using namespace std;

class MyClass {
private:
    int num1 = 0;
public:
    void Show() const;
    void Show2() const { cout << num1 << endl; }
};

void MyClass::Show() const {
    cout << num1 << endl;
}

int main() {
    MyClass myClass;
    myClass.Show();
    myClass.Show2();
    return 0;
}
