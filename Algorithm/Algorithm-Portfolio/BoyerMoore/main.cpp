#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#define MAX_BUFFER 512

using namespace std;

void BuildBCT(const string& Pattern, vector<int>& BCT) {
    int PatternSize = Pattern.size();
    fill(BCT.begin(), BCT.end(), -1);
    for (int j = 0; j < PatternSize; ++j)
        BCT[Pattern[j]] = j;
}

void BuildGST(const string& Pattern, vector<int>& Suffix, vector<int>& GST) {
    int PatternSize = Pattern.size();
    int i = PatternSize;
    int j = PatternSize + 1;

    Suffix[i] = j;
    while (i > 0) {
        while (j <= PatternSize && Pattern[i - 1] != Pattern[j - 1]) {
            if (GST[j] == 0)
                GST[j] = j - i;
            j = Suffix[j];
        }
        i--;
        j--;
        Suffix[i] = j;
    }

    j = Suffix[0];
    for (i = 0; i <= PatternSize; ++i) {
        if (GST[i] == 0)
            GST[i] = j;
        if (i == j)
            j = Suffix[j];
    }
}

template<typename T>
T Max(T A, T B) {
    return (A > B) ? A : B;
}

int BoyerMoore(const string& Text, const string& Pattern) {
    int TextSize = Text.size();
    int PatternSize = Pattern.size();
    vector<int> BCT(128, -1);
    vector<int> Suffix(PatternSize + 1, 0);
    vector<int> GST(PatternSize + 1, 0);
    int i = 0, j = 0, Position = -1;

    BuildBCT(Pattern, BCT);
    BuildGST(Pattern, Suffix, GST);

    while (i <= TextSize - PatternSize) {
        j = PatternSize - 1;
        while (j >= 0 && Pattern[j] == Text[i + j])
            j--;

        if (j < 0) {
            Position = i;
            break;
        }
        else {
            i += Max(GST[j + 1], j - BCT[Text[i + j]]);
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
    cin.ignore(); 

    cout << "Enter the pattern: ";
    getline(cin, Pattern);

    ifstream file(FilePath);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << FilePath << endl;
        return 1;
    }

    while (getline(file, Text)) {
        int Position = BoyerMoore(Text, Pattern);
        Line++;

        if (Position >= 0) {
            cout << "line:" << Line << ", column:" << Position + 1 << " : " << Text << endl;
        }
    }

    file.close();
    return 0;
}
