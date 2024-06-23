#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

namespace NQueens {

    void PrintSolution(const std::vector<int>& Columns, int NumberOfQueens);
    bool IsThreatened(const std::vector<int>& Columns, int NewRow);
    void FindSolutionForQueen(std::vector<int>& Columns, int Row,int NumberOfQueens, int& SolutionCount);

    void PrintSolution(const std::vector<int>& Columns, int NumberOfQueens)
    {
        for (int i = 0; i < NumberOfQueens; ++i)
        {
            for (int j = 0; j < NumberOfQueens; ++j)
            {
                if (Columns[i] == j)
                    std::cout << "Q";
                else
                    std::cout << ".";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    bool IsThreatened(const std::vector<int>& Columns, int NewRow)
    {
        for (int CurrentRow = 0; CurrentRow < NewRow; ++CurrentRow)
        {
            if (Columns[NewRow] == Columns[CurrentRow] ||
                std::abs(Columns[NewRow] - Columns[CurrentRow]) == std::abs(NewRow - CurrentRow))
            {
                return true;
            }
        }
        return false;
    }

    void FindSolutionForQueen(std::vector<int>& Columns, int Row,
        int NumberOfQueens, int& SolutionCount)
    {
        if (IsThreatened(Columns, Row))
            return;

        if (Row == NumberOfQueens - 1)
        {
            std::cout << "Solution #" << ++SolutionCount << " : \n";
            PrintSolution(Columns, NumberOfQueens);
        }
        else
        {
            for (int i = 0; i < NumberOfQueens; ++i)
            {
                Columns[Row + 1] = i;
                FindSolutionForQueen(Columns, Row + 1, NumberOfQueens, SolutionCount);
            }
        }
    }

} // namespace NQueens

int main()
{
    int NumberOfQueens;
    std::ifstream inputFile("NQueens.txt");
    if (!inputFile)
    {
        std::cerr << "Error opening file 'NQueens.txt'\n";
        return 1;
    }
    inputFile >> NumberOfQueens;
    int SolutionCount = 0;
    std::vector<int> Columns(NumberOfQueens);

    for (int i = 0; i < NumberOfQueens; ++i)
    {
        Columns[0] = i;
        NQueens::FindSolutionForQueen(Columns, 0, NumberOfQueens, SolutionCount);
    }
    return 0;
}
