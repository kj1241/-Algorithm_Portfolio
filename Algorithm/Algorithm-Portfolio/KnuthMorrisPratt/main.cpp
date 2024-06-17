#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define MAX_BUFFER 512

using namespace std;

void Preprocess(const string& Pattern, vector<int>& Border) {
    int i = 0;
    int j = -1;
    int PatternSize = Pattern.size();

    Border[0] = -1;

    while (i < PatternSize) {
        while (j > -1 && Pattern[i] != Pattern[j])
            j = Border[j];

        i++;
        j++;

        Border[i] = j;
    }
}

int KnuthMorrisPratt(const string& Text, const string& Pattern) {
    int TextSize = Text.size();
    int PatternSize = Pattern.size();
    int i = 0;
    int j = 0;
    int Position = -1;

    vector<int> Border(PatternSize + 1);
    Preprocess(Pattern, Border);

    while (i < TextSize) {
        while (j >= 0 && Text[i] != Pattern[j])
            j = Border[j];

        i++;
        j++;

        if (j == PatternSize) {
            Position = i - j;
            break;
        }
    }

    return Position;
}

int main() {
    string FilePath;
    string Pattern;
    string Text;
    int Line = 0;

    cout << "Enter the file path: ";
    cin >> FilePath;
    cin.ignore();  // ignore leftover newline from previous input

    cout << "Enter the pattern: ";
    getline(cin, Pattern);  // allows for spaces in the pattern

    ifstream file(FilePath);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << FilePath << endl;
        return 1;
    }


    while (getline(file, Text)) {
        int Position = KnuthMorrisPratt(Text, Pattern);
        Line++;

        if (Position >= 0) {
            cout << "line:" << Line << ", column:" << Position + 1 << " : " << Text << endl;
        }
    }

    file.close();
    return 0;
}
