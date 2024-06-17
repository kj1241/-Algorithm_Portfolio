#include <iostream>
#include <cstdlib>
#include <algorithm>

struct Score {
    int number;
    double score;
};

Score* BinarySearch(Score ScoreList[], int Size, double Target) {
    int Left = 0;
    int Right = Size - 1;

    while (Left <= Right) {
        int Mid = (Left + Right) / 2;

        if (Target == ScoreList[Mid].score)
            return &(ScoreList[Mid]);
        else if (Target > ScoreList[Mid].score)
            Left = Mid + 1;
        else
            Right = Mid - 1;
    }

    return nullptr;
}

int CompareScore(const void* _elem1, const void* _elem2) {
    const Score* elem1 = static_cast<const Score*>(_elem1);
    const Score* elem2 = static_cast<const Score*>(_elem2);

    if (elem1->score > elem2->score)
        return 1;
    else if (elem1->score < elem2->score)
        return -1;
    else
        return 0;
}

int main() {
    Score DataSet[] = {
        {1, 600.5},
        {2, 671.78},
        {3, 500.0},
        {4, 800.3}
        // �ʿ信 ���� �� ���� �����͸� �߰��ϼ���
    };

    int Length = sizeof(DataSet) / sizeof(DataSet[0]);

    // ������ ������������ ����
    std::qsort(static_cast<void*>(DataSet), Length, sizeof(Score), CompareScore);

    // 671.78 ���� ���� �л� ã��
    Score* found = BinarySearch(DataSet, Length, 671.78);

    if (found != nullptr) {
        std::cout << "found: " << found->number << " " << found->score << std::endl;
    }
    else {
        std::cout << "Score not found." << std::endl;
    }

    return 0;
}
