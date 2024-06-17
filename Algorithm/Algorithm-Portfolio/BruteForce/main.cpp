#include <iostream>
#include <fstream>
#include <string>
#define MAX_BUFFER 512

using namespace std;

// BruteForce 함수: 텍스트에서 패턴을 검색하는 함수
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
    string FilePath;  // 파일 경로를 저장할 변수
    string Pattern;   // 검색할 패턴을 저장할 변수
    string Text;
    int Line = 0;

    // 사용자로부터 파일 경로 입력 받기
    cout << "Enter the file path: ";
    getline(cin, FilePath);

    // 사용자로부터 검색할 패턴 입력 받기
    cout << "Enter the pattern to search: ";
    getline(cin, Pattern);

    int PatternSize = Pattern.length();
    ifstream file(FilePath);

    // 파일이 열리지 않을 경우 오류 메시지 출력
    if (!file.is_open()) {
        cout << "Cannot open file: " << FilePath << endl;
        return 1;
    }


    // 파일을 한 줄씩 읽으면서 패턴 검색
    while (getline(file, Text)) {
        int Position = BruteForce(Text, Text.length(), 0, Pattern, PatternSize);
        Line++;

        if (Position >= 0) {
            // 패턴이 발견된 경우 해당 줄과 위치를 출력
            cout << "line: " << Line << ", column: " << Position + 1 << " : " << Text << endl;
        }
    }

    // 파일 닫기
    file.close();
    return 0;
}
