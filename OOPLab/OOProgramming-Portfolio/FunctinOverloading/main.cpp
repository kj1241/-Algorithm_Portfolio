#include <iostream>

using namespace std;

class Player {
private:
    // ĳ���� ����
    int hp;
    int mp;
    int playerDamage;

    // ĳ���� ��ġ
    int x;
    int y;
    int z;

    // ��ü ����
    enum class UpperBodyState {
        none,
        attack,
        defense,
        skill1,
        skill2,
        skill3
    } upBodyState;

    // ��ü ����
    enum class LowerBodyState {
        none,
        walk,
        jump,
        run
    } lowBodyState;

public:
    // ������
    Player() : hp(50), mp(50), playerDamage(100), x(0), y(0), z(0), upBodyState(UpperBodyState::none), lowBodyState(LowerBodyState::none) {}

    Player(int hp, int mp, int playerDamage, int x, int y, int z)
        : hp(hp), mp(mp), playerDamage(playerDamage), x(x), y(y), z(z), upBodyState(UpperBodyState::none), lowBodyState(LowerBodyState::none) {}

    // �Ҹ���
    ~Player() {}

    // ������ �޼���
    bool damage(int attackDamage) {
        if (upBodyState == UpperBodyState::defense) // ��� ���¶��
            return true;
        hp -= attackDamage; // ���� ��������ŭ hp ����
        return hp > 0; // ���� ����ִٸ� true ��ȯ
    }

    // ���� �޼���
    int attack() const {
        if (upBodyState != UpperBodyState::attack) // ���� ���°� �ƴ϶��
            return 0;
        return playerDamage;
    }

    // ���� �޼���
    bool jump() {
        if (lowBodyState == LowerBodyState::jump) // ���� ���� ����
            return false;

        upBodyState = UpperBodyState::none; // ���� �߿��� ��ü �ൿ �Ұ�
        lowBodyState = LowerBodyState::jump;
        return true;
    }

    // ȸ��, �̵� ���� �߰� �޼���� ���⿡ �߰� ����
};

int main() {
    Player player;
    player.damage(10);
    cout << "���� ������: " << player.attack() << endl;
    cout << "���� ���: " << (player.jump() ? "����" : "����") << endl;

    return 0;
}
