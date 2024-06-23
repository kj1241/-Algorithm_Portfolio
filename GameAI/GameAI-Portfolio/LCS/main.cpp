#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct LCSTable {
    vector<vector<int>> Data;
};

int LCS(const string& X, const string& Y, int i, int j, LCSTable& Table) {
    for (int m = 0; m <= i; m++)
        Table.Data[m][0] = 0;

    for (int n = 0; n <= j; n++)
        Table.Data[0][n] = 0;

    for (int m = 1; m <= i; m++) {
        for (int n = 1; n <= j; n++) {
            if (X[m - 1] == Y[n - 1])
                Table.Data[m][n] = Table.Data[m - 1][n - 1] + 1;
            else
                Table.Data[m][n] = max(Table.Data[m][n - 1], Table.Data[m - 1][n]);
        }
    }

    return Table.Data[i][j];
}

void LCS_TraceBack(const string& X, const string& Y, int m, int n, LCSTable& Table, string& LCS) {
    if (m == 0 || n == 0)
        return;

    if (Table.Data[m][n] > Table.Data[m][n - 1] && Table.Data[m][n] > Table.Data[m - 1][n] && Table.Data[m][n] > Table.Data[m - 1][n - 1]) {
        LCS = X[m - 1] + LCS;
        LCS_TraceBack(X, Y, m - 1, n - 1, Table, LCS);
    }
    else if (Table.Data[m][n] > Table.Data[m - 1][n] && Table.Data[m][n] == Table.Data[m][n - 1]) {
        LCS_TraceBack(X, Y, m, n - 1, Table, LCS);
    }
    else {
        LCS_TraceBack(X, Y, m - 1, n, Table, LCS);
    }
}

void LCS_PrintTable(LCSTable& Table, const string& X, const string& Y, int LEN_X, int LEN_Y) {
    cout << "   ";
    for (int i = 0; i < LEN_Y + 1; i++)
        cout << Y[i] << " ";
    cout << endl;

    for (int i = 0; i < LEN_X + 1; i++) {
        if (i == 0)
            cout << "  ";
        else
            cout << X[i - 1] << " ";

        for (int j = 0; j < LEN_Y + 1; j++)
            cout << Table.Data[i][j] << " ";
        cout << endl;
    }
}

int main() {
    string X = "GOOD MORNING.";
    string Y = "GUTEN MORGEN.";
    string Result;

    int LEN_X = X.length();
    int LEN_Y = Y.length();

    LCSTable Table;
    Table.Data.resize(LEN_X + 1, vector<int>(LEN_Y + 1, 0));
    int Length = LCS(X, Y, LEN_X, LEN_Y, Table);
    LCS_PrintTable(Table, X, Y, LEN_X, LEN_Y);
    LCS_TraceBack(X, Y, LEN_X, LEN_Y, Table, Result);
    cout << "\nLCS: \"" << Result << "\" (Length: " << Length << ")\n";
    return 0;
}
