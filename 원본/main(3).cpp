#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
//숙제 1
class CBase
{
private:
    int baseNum;
public:
    CBase() :baseNum(0){
    

    }
    CBase(int n) : baseNum(n) {
    }
protected:
    void Show()
    {

    }
};

class cDerived :public CBase
{
private:
    int drievedNum;
public:
    cDerived() :drievedNum(0){
       

    }
    cDerived(int n) : drievedNum(n) {
    }
};
*/
///////////////////////////
/*
class CBase
{
private:

public:
    CBase() {
      cout<<" 생성자1";

    }
    CBase(int n)  {

    }
    ~CBase()
    {
        cout << " 소멸자2";
    }
protected:
    void Show()
    {

    }
};

class cDerived :public CBase
{
private:

public:
    cDerived() {
        cout << " 생성자2";
    }
   
   
    ~cDerived() {
        cout << " 소멸자2";
 
    }
};*/
/*
class CBase
{
public:
    CBase() { }
    virtual void Func() { cout << "CBase Func()" << endl; } 
};

class CDerived : public CBase
{
public:
    CDerived() { }
    void Func() { cout << "CDerived Func()" << endl; }
};

int main(void)
{
    CDerived z;
    CBase* p = &z;  p->Func(); 
    return 0;
}
*/
/*
class Player
{
public:
    Player() { }
    virtual void Func() { cout << "CBase Func()" << endl; }
};

class boss : public Player
{
public:
    boss() { }
    void Func() { cout << "CDerived Func()" << endl; }
};


class moster : public Player
{
public:
    moster() { }
    void Func() { cout << "CDerived Func()" << endl; }
};

int main(void)
{
    moster z;
    boss b;
    Player* p = &z;  p->Func();
    Player* p = &b;  p->Func();

    list<Player> playerlist;
    return 0;
}
*/

class Characters {


protected:
    int x;
    int y;
    int z;

    enum class UpBodyStats {
        none,
        atteck,
        skill1,
        skill2,
        skill3
    };

    enum class lowBodyStats {
        none,
        walk,
        run,
        jump
    };
    UpBodyStats upstats = UpBodyStats::none;
    lowBodyStats lowstats = lowBodyStats::none;
    


public:
    Characters(){}
    Characters(int x, int y, int z) :x(x), y(y), z(z) {}
    ~Characters() {}
    virtual void UpBodyStats(){}
    virtual void lowBodyStats(){}

    
};





class player :public Characters {
    
public:
    player() {}
    player(int x, int y, int z) :Characters(x,y,z) {}
    ~player() {}
    void UpBodyStats();
    void lowBodyStats();


};

void player::UpBodyStats()
{
    switch (Characters::upstats)
    {
    case UpBodyStats::none:
        //일반

    case UpBodyStats::atteck:
        //공격모션

    default:
        break;
    }

}

void player::lowBodyStats()
{
    switch (Characters::lowstats)
    {
    case lowBodyStats::none:
        //일반

    case lowBodyStats::walk:
        //걷는애니메이션

    default:
        break;
    }

}



class monster :public Characters {

public:
    monster() {}
    monster(int x, int y, int z) :Characters(x, y, z) {}
    ~monster() {}
    void UpBodyStats();
    void lowBodyStats();


};

void monster::UpBodyStats()
{
    switch (Characters::upstats)
    {
    case UpBodyStats::none:
        //일반

    case UpBodyStats::atteck:
        //공격모션

    default:
        break;
    }

}

void monster::lowBodyStats()
{
    switch (Characters::lowstats)
    {
    case lowBodyStats::none:
        //일반

    case lowBodyStats::walk:
        //걷는애니메이션

    default:
        break;
    }

}



