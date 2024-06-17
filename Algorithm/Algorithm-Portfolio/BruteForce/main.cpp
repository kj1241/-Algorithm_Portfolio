#include <iostream>
#include <fstream>
#include <string>
#define MAX_BUFFER 512

using namespace std;

// BruteForce �Լ�: �ؽ�Ʈ���� ������ �˻��ϴ� �Լ�
int BruteForce(const string& Text, int TextSize, int Start, const string& Pattern, int PatternSize) {
    for (int i = Start; i <= TextSize - PatternSize; ++i) {
        int j;
        for (j = 0; j < PatternSize; ++j) {
            if (Text[i + j] != Pattern[j])
                break;
        }
        if (j >= PatternSize)
            return i;
    }
    return -1;
}

int main() {
    string FilePath;  // ���� ��θ� ������ ����
    string Pattern;   // �˻��� ������ ������ ����
    string Text;
    int Line = 0;

    // ����ڷκ��� ���� ��� �Է� �ޱ�
    cout << "Enter the file path: ";
    getline(cin, FilePath);

    // ����ڷκ��� �˻��� ���� �Է� �ޱ�
    cout << "Enter the pattern to search: ";
    getline(cin, Pattern);

    int PatternSize = Pattern.length();
    ifstream file(FilePath);

    // ������ ������ ���� ��� ���� �޽��� ���
    if (!file.is_open()) {
        cout << "Cannot open file: " << FilePath << endl;
        return 1;
    }


    // ������ �� �پ� �����鼭 ���� �˻�
    while (getline(file, Text)) {
        int Position = BruteForce(Text, Text.length(), 0, Pattern, PatternSize);
        Line++;

        if (Position >= 0) {
            // ������ �߰ߵ� ��� �ش� �ٰ� ��ġ�� ���
            cout << "line: " << Line << ", column: " << Position + 1 << " : " << Text << endl;
        }
    }

    // ���� �ݱ�
    file.close();
    return 0;
}
