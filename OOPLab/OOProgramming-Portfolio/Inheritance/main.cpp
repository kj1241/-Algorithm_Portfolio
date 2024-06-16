#include <iostream>
using namespace std;

class Characters
{
public:
    enum class UpBodyStats
    {
        none,
        attack,
        skill1,
        skill2,
        skill3
    };

    enum class LowBodyStats
    {
        none,
        walk,
        run,
        jump
    };

protected:
    int x{ 0 };
    int y{ 0 };
    int z{ 0 };

    UpBodyStats upstats = UpBodyStats::none;
    LowBodyStats lowstats = LowBodyStats::none;

public:
    Characters() {}
    Characters(int x, int y, int z) : x(x), y(y), z(z) {}
    virtual ~Characters() {}

    virtual void UpdateUpBodyStats() = 0;
    virtual void UpdateLowBodyStats() = 0;

    void SetUpBodyStats(UpBodyStats stats) { upstats = stats; }
    void SetLowBodyStats(LowBodyStats stats) { lowstats = stats; }
};

class PlayerCharacter : public Characters
{
public:
    PlayerCharacter() {}
    PlayerCharacter(int x, int y, int z) : Characters(x, y, z) {}
    ~PlayerCharacter() override {}

    void UpdateUpBodyStats() override;
    void UpdateLowBodyStats() override;
};

void PlayerCharacter::UpdateUpBodyStats()
{
    switch (upstats)
    {
    case UpBodyStats::none:
        cout << "Player UpBodyStats: None" << endl;
        break;
    case UpBodyStats::attack:
        cout << "Player UpBodyStats: Attack" << endl;
        break;
    case UpBodyStats::skill1:
        cout << "Player UpBodyStats: Skill1" << endl;
        break;
    case UpBodyStats::skill2:
        cout << "Player UpBodyStats: Skill2" << endl;
        break;
    case UpBodyStats::skill3:
        cout << "Player UpBodyStats: Skill3" << endl;
        break;
    }
}

void PlayerCharacter::UpdateLowBodyStats()
{
    switch (lowstats)
    {
    case LowBodyStats::none:
        cout << "Player LowBodyStats: None" << endl;
        break;
    case LowBodyStats::walk:
        cout << "Player LowBodyStats: Walk" << endl;
        break;
    case LowBodyStats::run:
        cout << "Player LowBodyStats: Run" << endl;
        break;
    case LowBodyStats::jump:
        cout << "Player LowBodyStats: Jump" << endl;
        break;
    }
}

class MonsterCharacter : public Characters
{
public:
    MonsterCharacter() {}
    MonsterCharacter(int x, int y, int z) : Characters(x, y, z) {}
    ~MonsterCharacter() override {}

    void UpdateUpBodyStats() override;
    void UpdateLowBodyStats() override;
};

void MonsterCharacter::UpdateUpBodyStats()
{
    switch (upstats)
    {
    case UpBodyStats::none:
        cout << "Monster UpBodyStats: None" << endl;
        break;
    case UpBodyStats::attack:
        cout << "Monster UpBodyStats: Attack" << endl;
        break;
    case UpBodyStats::skill1:
        cout << "Monster UpBodyStats: Skill1" << endl;
        break;
    case UpBodyStats::skill2:
        cout << "Monster UpBodyStats: Skill2" << endl;
        break;
    case UpBodyStats::skill3:
        cout << "Monster UpBodyStats: Skill3" << endl;
        break;
    }
}

void MonsterCharacter::UpdateLowBodyStats()
{
    switch (lowstats)
    {
    case LowBodyStats::none:
        cout << "Monster LowBodyStats: None" << endl;
        break;
    case LowBodyStats::walk:
        cout << "Monster LowBodyStats: Walk" << endl;
        break;
    case LowBodyStats::run:
        cout << "Monster LowBodyStats: Run" << endl;
        break;
    case LowBodyStats::jump:
        cout << "Monster LowBodyStats: Jump" << endl;
        break;
    }
}

int main()
{
    // PlayerCharacter 객체 생성
    PlayerCharacter player(10, 20, 30);
    player.SetUpBodyStats(Characters::UpBodyStats::attack);
    player.SetLowBodyStats(Characters::LowBodyStats::run);

    // MonsterCharacter 객체 생성
    MonsterCharacter monster(40, 50, 60);
    monster.SetUpBodyStats(Characters::UpBodyStats::skill1);
    monster.SetLowBodyStats(Characters::LowBodyStats::walk);

    // 상태 업데이트
    cout << "플레이어 상태 업데이트:" << endl;
    player.UpdateUpBodyStats();
    player.UpdateLowBodyStats();

    cout << "몬스터 상태 업데이트:" << endl;
    monster.UpdateUpBodyStats();
    monster.UpdateLowBodyStats();

    return 0;
}
