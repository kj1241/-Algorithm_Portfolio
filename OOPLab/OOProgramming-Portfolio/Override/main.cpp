#include <iostream>
#include <list>

using namespace std;

class Player
{
public:
    Player() {}
    virtual void Func() { cout << "Player Func()" << endl; }
};

class Boss : public Player
{
public:
    Boss() {}
    void Func() override { cout << "Boss Func()" << endl; }
};

class Monster : public Player
{
public:
    Monster() {}
    void Func() override { cout << "Monster Func()" << endl; }
};

int main()
{
    Monster z;
    Boss b;
    Player* p = &z;
    p->Func();  // Should call Monster::Func
    p = &b;
    p->Func();  // Should call Boss::Func

    list<Player*> playerlist;
    playerlist.push_back(&z);
    playerlist.push_back(&b);

    for (Player* player : playerlist) {
        player->Func();
    }

    return 0;
}
