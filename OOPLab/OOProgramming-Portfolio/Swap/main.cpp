#include <iostream>

using namespace std;

void SwapByRef2(int& ref1, int& ref2) {
    int temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}

int main() {
    int v1 = 10, v2 = 20;
    SwapByRef2(v1, v2);
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    return 0;
}
