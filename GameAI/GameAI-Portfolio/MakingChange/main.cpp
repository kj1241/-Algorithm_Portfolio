#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void GetChange(int Price, int Pay, const vector<int>& CoinUnits, vector<int>& Change) {
    int ChangeAmount = Pay - Price;

    for (size_t i = 0; i < CoinUnits.size(); i++) {
        Change[i] = ChangeAmount / CoinUnits[i];
        ChangeAmount -= CoinUnits[i] * Change[i];
    }
}

void PrintChange(const vector<int>& CoinUnits, const vector<int>& Change) {
    for (size_t i = 0; i < CoinUnits.size(); i++) {
        cout << CoinUnits[i] << "원: " << Change[i] << "개" << endl;
    }
}

int main() {
    int UnitCount = 0;
    int Pay = 0;
    int Price = 0;

    cout << "동전의 가짓수를 입력하세요: ";
    cin >> UnitCount;

    vector<int> CoinUnits(UnitCount);
    vector<int> Change(UnitCount);

    for (int i = 0; i < UnitCount; i++) {
        cout << "[" << i << "] 번째 동전의 단위를 입력하세요: ";
        cin >> CoinUnits[i];
    }
    sort(CoinUnits.rbegin(), CoinUnits.rend());

    cout << "물건 가격을 입력하세요: ";
    cin >> Price;
    cout << "손님이 지불한 돈은 얼마입니까? : ";
    cin >> Pay;
    if (Pay < Price) {
        cout << "지불한 돈이 물건 가격보다 적습니다." << endl;
        return 1;
    }

    GetChange(Price, Pay, CoinUnits, Change);
    PrintChange(CoinUnits, Change);

    return 0;
}
