#include <iostream>
#include <cstdlib>
#include <algorithm>

struct Score {
    int number;
    double score;
};

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
    Score target;
    target.number = 0;
    target.score = 671.78;

    Score* found = static_cast<Score*>(std::bsearch(
        static_cast<void*>(&target),
        static_cast<void*>(DataSet),
        Length,
        sizeof(Score),
        CompareScore
    ));

    if (found != nullptr) {
        std::cout << "found: " << found->number << " " << found->score << std::endl;
    }
    else {
        std::cout << "Score not found." << std::endl;
    }

    return 0;
}
