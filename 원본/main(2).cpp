#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


//���� 1
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

//�ζ����Լ�
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
//cosnt ���ȭ

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

//���� 2(�Լ� �����ε�) plyer ������ ������������ �����ϰ�...
class Player
{
private:
	//ĳ������ ����
	int hp = 50;
	int mp = 50;
	int playerDemge = 100;
	
	//ĳ������ ��ġ
	int x = 0;
	int y = 0;
	int z = 0;

	//�� �ִϸ��̼ǿ��� ������(�㸮)�� �������� ��ü �ִϸ��̼� ����
	enum class UpperBodyState {
		none,
		atteck,
		defense,
		skill1,
		skill2,
		skill3
	};

	//Skinned Mesh ���뿡�� ��ü
	enum class LowerBodyState {
		none,
		walk,
		jump,
		run
	};

	UpperBodyState upBodyState;
	LowerBodyState lowBodyState;

public:
	//������ �ʱⰪ ������ Ȥ�� �𸣴� �����ڷ� �ʱ�ȭ
	Player()
	{
		//�� �����Ҵ����� �߰�
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
		//�� �����Ҵ��� �߰�
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
		//�𵨵����Ҵ� ����
	}

	//�������� ���� ������
	bool damage(int atteckDamage) 
	{
		if (upBodyState == UpperBodyState::defense) //����ڼ����
			return true;
		hp = hp - atteckDamage;// ������������ŭ �ǰ���
	}
	//�ִϸ��̼ǿ��� ���� ����������
	int atteck()
	{
		if (upBodyState != UpperBodyState::atteck) //���°� ���ݻ��°��ƴ϶�� �н�
			return 0;
		
		return playerDemge;
	}
	//��ų�� ��������� �н�
	bool jump(bool isJump) //�����ϴ� �̺�Ʈ�� �����ԵǸ�
	{
		if (lowBodyState != LowerBodyState::jump) //�̴������� ���� �����ȹ�� �������� �н�
			return false;

		upBodyState = UpperBodyState::none; //��ä�� ������ ��������������� ���� ����
		lowBodyState = LowerBodyState::jump;//��ü ������Ʈ�� ������ ����

		return true;

	}
	//�̿ܿ� ȸ�� , �̵� �� �߰��ʿ�

};

