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
        cout << CoinUnits[i] << "��: " << Change[i] << "��" << endl;
    }
}

int main() {
    int UnitCount = 0;
    int Pay = 0;
    int Price = 0;

    cout << "������ �������� �Է��ϼ���: ";
    cin >> UnitCount;

    vector<int> CoinUnits(UnitCount);
    vector<int> Change(UnitCount);

    for (int i = 0; i < UnitCount; i++) {
        cout << "[" << i << "] ��° ������ ������ �Է��ϼ���: ";
        cin >> CoinUnits[i];
    }
    sort(CoinUnits.rbegin(), CoinUnits.rend());

    cout << "���� ������ �Է��ϼ���: ";
    cin >> Price;
    cout << "�մ��� ������ ���� ���Դϱ�? : ";
    cin >> Pay;
    if (Pay < Price) {
        cout << "������ ���� ���� ���ݺ��� �����ϴ�." << endl;
        return 1;
    }

    GetChange(Price, Pay, CoinUnits, Change);
    PrintChange(CoinUnits, Change);

    return 0;
}
