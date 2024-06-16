#include <iostream>

using namespace std;

class Player {
private:
    // 캐릭터 상태
    int hp;
    int mp;
    int playerDamage;

    // 캐릭터 위치
    int x;
    int y;
    int z;

    // 상체 상태
    enum class UpperBodyState {
        none,
        attack,
        defense,
        skill1,
        skill2,
        skill3
    } upBodyState;

    // 하체 상태
    enum class LowerBodyState {
        none,
        walk,
        jump,
        run
    } lowBodyState;

public:
    // 생성자
    Player() : hp(50), mp(50), playerDamage(100), x(0), y(0), z(0), upBodyState(UpperBodyState::none), lowBodyState(LowerBodyState::none) {}

    Player(int hp, int mp, int playerDamage, int x, int y, int z)
        : hp(hp), mp(mp), playerDamage(playerDamage), x(x), y(y), z(z), upBodyState(UpperBodyState::none), lowBodyState(LowerBodyState::none) {}

    // 소멸자
    ~Player() {}

    // 데미지 메서드
    bool damage(int attackDamage) {
        if (upBodyState == UpperBodyState::defense) // 방어 상태라면
            return true;
        hp -= attackDamage; // 공격 데미지만큼 hp 감소
        return hp > 0; // 아직 살아있다면 true 반환
    }

    // 공격 메서드
    int attack() const {
        if (upBodyState != UpperBodyState::attack) // 공격 상태가 아니라면
            return 0;
        return playerDamage;
    }

    // 점프 메서드
    bool jump() {
        if (lowBodyState == LowerBodyState::jump) // 더블 점프 방지
            return false;

        upBodyState = UpperBodyState::none; // 점프 중에는 상체 행동 불가
        lowBodyState = LowerBodyState::jump;
        return true;
    }

    // 회전, 이동 등의 추가 메서드는 여기에 추가 가능
};

int main() {
    Player player;
    player.damage(10);
    cout << "공격 데미지: " << player.attack() << endl;
    cout << "점프 결과: " << (player.jump() ? "성공" : "실패") << endl;

    return 0;
}
