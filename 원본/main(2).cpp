#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


//숙제 1
/*
class MyClass{
private:
	int num1 = 0;
public:
	void Show();
};

void MyClass::Show()
{
	cout << num1 << endl;
}


int main()
{
	MyClass myClass;
	myClass.Show();

	return 0;
}
*/

/*

//인라인함수
class MyClass {
private:
	int num1 = 0;
public:
	void Show(){ cout << num1 << endl; }
};



int main()
{
	MyClass myClass;
	myClass.Show();

	return 0;
}
*/


/*
//cosnt 상수화

class MyClass {
private:
	int num1 = 0;
public:
	void Show() const;
};

void MyClass::Show() const
{
	cout << num1 << endl;
}


int main()
{
	MyClass myClass;
	myClass.Show();

	return 0;
}

*/
/*

// call by reference
void SwapByRef2(int& ref1, int& ref2)
{
	int temp = ref1;
	ref1 = ref2;
	ref2 = temp;

}

int main(void)
{
	int v1 = 10, v2 = 20;
	SwapByRef2(v1, v2);
	cout << "v1:" << v1 << endl;
	cout << "v2:" << v2 << endl;

	return 0;
}
*/

//숙제 2(함수 오버로드) plyer 제작은 끝도없음으로 간단하게...
class Player
{
private:
	//캐릭터의 상태
	int hp = 50;
	int mp = 50;
	int playerDemge = 100;
	
	//캐릭터의 위치
	int x = 0;
	int y = 0;
	int z = 0;

	//본 애니메이션에서 기준점(허리)를 기준으로 상체 애니메이션 여부
	enum class UpperBodyState {
		none,
		atteck,
		defense,
		skill1,
		skill2,
		skill3
	};

	//Skinned Mesh 뼈대에서 하체
	enum class LowerBodyState {
		none,
		walk,
		jump,
		run
	};

	UpperBodyState upBodyState;
	LowerBodyState lowBodyState;

public:
	//위에서 초기값 줬으나 혹시 모르니 생성자로 초기화
	Player()
	{
		//모델 동적할당으로 추가
		hp = 50;
		mp = 50;
		playerDemge = 100;
		x = 0;
		y = 0;
		z = 0;
		upBodyState = UpperBodyState::none;
		lowBodyState = LowerBodyState::none;
	}
	Player(int hp = 50, int mp = 50, int playerDemge=100,int x = 0, int y = 0, int z = 0)
	{
		//모델 동적할당의 추가
		hp = hp;
		mp = mp;
		playerDemge = playerDemge;
		x = x;
		y = y;
		z = z;
		upBodyState = UpperBodyState::none;
		lowBodyState = LowerBodyState::none;
	}
	~Player()
	{
		//모델동적할당 해제
	}

	//데미지를 들어온 데미지
	bool damage(int atteckDamage) 
	{
		if (upBodyState == UpperBodyState::defense) //방어자세라면
			return true;
		hp = hp - atteckDamage;// 받은데미지만큼 피감소
	}
	//애니메이션에서 공격 성공했으면
	int atteck()
	{
		if (upBodyState != UpperBodyState::atteck) //상태가 공격상태가아니라면 패스
			return 0;
		
		return playerDemge;
	}
	//스킬은 비슷함으로 패스
	bool jump(bool isJump) //점프하는 이벤트가 들어오게되면
	{
		if (lowBodyState != LowerBodyState::jump) //이단점프는 아직 만들계획이 없음으로 패스
			return false;

		upBodyState = UpperBodyState::none; //상채는 공격을 허용하지않음으로 강제 변경
		lowBodyState = LowerBodyState::jump;//하체 스테이트도 점프로 변경

		return true;

	}
	//이외에 회전 , 이동 등 추가필요

};

