#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#define MAX_BUFFER 512

using namespace std;

// Hash 함수: 문자열의 해시 값을 계산
int Hash(const string& String, int Size) {
    int HashValue = 0;
    for (int i = 0; i < Size; ++i) {
        HashValue = String[i] + (HashValue * 2);
    }
    return HashValue;
}

// ReHash 함수: 기존 해시 값을 사용해 새로운 해시 값을 계산
int ReHash(const string& String, int Start, int Size, int HashPrev, int Coefficient) {
    if (Start == 0)
        return HashPrev;

    return String[Start + Size - 1] + ((HashPrev - Coefficient * String[Start - 1]) * 2);
}

// KarpRabin 함수: 텍스트에서 패턴을 검색하는 함수
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

    //// 사용자로부터 파일 경로 입력 받기
    //cout << "Enter the file path: ";
    //getline(cin, FilePath);

    //// 사용자로부터 검색할 패턴 입력 받기
    //cout << "Enter the pattern to search: ";
    //getline(cin, Pattern);

    //int PatternSize = Pattern.length();
    //ifstream file(FilePath);

    //// 파일이 열리지 않을 경우 오류 메시지 출력
    //if (!file.is_open()) {
    //    cout << "Cannot open file: " << FilePath << endl;
    //    return 1;
    //}


    //int Line = 0;

    //// 파일을 한 줄씩 읽으면서 패턴 검색
    //while (getline(file, Pattern)) {
    //    int Position = KarpRabin(Pattern, Pattern.length(), 0, Pattern, PatternSize);
    //    Line++;

    //    if (Position >= 0) {
    //        // 패턴이 발견된 경우 해당 줄과 위치를 출력
    //        cout << "line: " << Line << ", column: " << Position + 1 << " : " << Pattern << endl;
    //    }
    //}

    //// 파일 닫기
    //file.close();
    //return 0;
}
