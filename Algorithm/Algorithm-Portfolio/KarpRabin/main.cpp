#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#define MAX_BUFFER 512

using namespace std;

// Hash �Լ�: ���ڿ��� �ؽ� ���� ���
int Hash(const string& String, int Size) {
    int HashValue = 0;
    for (int i = 0; i < Size; ++i) {
        HashValue = String[i] + (HashValue * 2);
    }
    return HashValue;
}

// ReHash �Լ�: ���� �ؽ� ���� ����� ���ο� �ؽ� ���� ���
int ReHash(const string& String, int Start, int Size, int HashPrev, int Coefficient) {
    if (Start == 0)
        return HashPrev;

    return String[Start + Size - 1] + ((HashPrev - Coefficient * String[Start - 1]) * 2);
}

// KarpRabin �Լ�: �ؽ�Ʈ���� ������ �˻��ϴ� �Լ�
int KarpRabin(const string& Text, int TextSize, int Start, const string& Pattern, int PatternSize) {
    int Coefficient = pow(2, PatternSize - 1);
    int HashText = Hash(Text, PatternSize);
    int HashPattern = Hash(Pattern, PatternSize);

    for (int i = Start; i <= TextSize - PatternSize; ++i) {
        if (i > Start) {
            HashText = ReHash(Text, i, PatternSize, HashText, Coefficient);
        }

        if (HashPattern == HashText) {
            int j;
            for (j = 0; j < PatternSize; ++j) {
                if (Text[i + j] != Pattern[j])
                    break;
            }

            if (j >= PatternSize)
                return i;
        }
    }

    return -1;
}


int main() {

    string Text = "My name is pattern";
    string Pattern = "pattern";
    int PatternSize = Pattern.size();

    int result = KarpRabin(Text, Text.size(), 0, Pattern, Pattern.size());
    cout << result << endl;

    int h0 = Hash(Pattern, PatternSize);
    int h1 = Hash(Pattern.substr(1), PatternSize);
    int rh1 = ReHash(Pattern, 1, PatternSize, h0, static_cast<int>(pow(2, PatternSize - 1)));

    cout << "h0: " << h0 << endl;
    cout << "h1: " << h1 << endl;
    cout << "rh1: " << rh1 << endl;

    return 0;

    //string FilePath;
    //string Pattern;

    //// ����ڷκ��� ���� ��� �Է� �ޱ�
    //cout << "Enter the file path: ";
    //getline(cin, FilePath);

    //// ����ڷκ��� �˻��� ���� �Է� �ޱ�
    //cout << "Enter the pattern to search: ";
    //getline(cin, Pattern);

    //int PatternSize = Pattern.length();
    //ifstream file(FilePath);

    //// ������ ������ ���� ��� ���� �޽��� ���
    //if (!file.is_open()) {
    //    cout << "Cannot open file: " << FilePath << endl;
    //    return 1;
    //}


    //int Line = 0;

    //// ������ �� �پ� �����鼭 ���� �˻�
    //while (getline(file, Pattern)) {
    //    int Position = KarpRabin(Pattern, Pattern.length(), 0, Pattern, PatternSize);
    //    Line++;

    //    if (Position >= 0) {
    //        // ������ �߰ߵ� ��� �ش� �ٰ� ��ġ�� ���
    //        cout << "line: " << Line << ", column: " << Position + 1 << " : " << Pattern << endl;
    //    }
    //}

    //// ���� �ݱ�
    //file.close();
    //return 0;
}
