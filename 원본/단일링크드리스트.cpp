/*
단일 링크드리스트(ver.1 2015.11.08) mr.K
*/
#include <stdio.h>
#include <windows.h>

//template <typename T> 일 딴 보류 .... 템플릿 쓰고 싶은데...
/*
정의
*/
typedef struct tag_node
{
	int data;
	struct tag_node *next;
}Node, *pNode;


typedef struct
{
	pNode head;
	pNode tail;
}SLL, *pSLL;



/*
프로그래머 코드, 시스템 코드
*/

void Error_print()//에러 메세지 출력 사실 winapi로 메세지 박스 추후 구현
{
	printf("error");
}

Node* crate_node(int data)//노드 창조
{
	Node *NewNode = new Node;// 동적할당(cpp)
	//Node  *NewNode=(Node*)malloc(sizeof(Node));
	NewNode->data = data;
	NewNode->next = NULL;
	return NewNode;
}

void node_free(Node *node)//동적할당 해제
{
	if (node == NULL) return;
	free((void *)node);
}

int find_data(const SLL *lst, int data_fine)//주어진 데이터로 노드갯수 찾기
{
	int p = 0;
	Node *temp = lst->head;

	if (lst == NULL) return -1;
	if (temp == NULL)return -1;

	while (lst->head != lst->tail)
	{
		if (temp->data == data_fine)
		{
			p = p + 1;
		}
		temp = temp->next;
	}//temp==NULL
	return p;
}

Node *Such_Node(const SLL *lst, int data_fine)//주어진 데이터로 노드 찾기
{
	Node *temp = lst->head;

	if (lst == NULL) return nullptr;
	if (temp == NULL)return nullptr;

	int p = find_data(lst, data_fine);
	if (p == 0 || p > 1) //에러 시스템메세지 출력을 위해서;
	{
		Error_print();
	}//p==1;
	while (temp->data != data_fine)
	{
		temp = temp->next;
	}//temp->data==data_fine
	return temp;
}

Node *find_Prv_Node(const SLL *lst, int data)
{
	Node *temp = Such_Node(lst, data);
	Node *prev = temp;

	if (lst == NULL) return nullptr;
	if (temp == NULL)return nullptr;

	while (lst->head!= temp)
	{
		prev = temp;
		temp = temp->next;
	}
	return prev;
}
void New_node(SLL *lst, int data)//해드가 널값일때 새로운 노드만들기.
{
	Node *temp = crate_node(data);

	if (lst == NULL) return;
	if (lst->head != NULL) return;

	lst->head = temp;
	return;
}
/*
유저 코드
*/

void insert_data(SLL *lst, int data_fine, int data)//삽입(단일리스트 , 삽입전 데이터위치, 데이터)
{
	Node *p = crate_node(data);
	Node *temp = Such_Node(lst, data_fine);
	
	if (lst == NULL) return;
	if (temp == NULL)return;
	
	if (data_fine == NULL)//case1 삽입전 데이터 값이 없을때.
	{
		New_node(lst, data);
	}	
	if (lst->head == NULL)//case2 해드가 가르키는것이 아무것도없을때.
	{
		lst->head = p;
		lst->tail = p;
		return;	
	}
	if (lst->tail == temp)//case3 마지막에 삽일할때.
	{
		temp->next = p;
		lst->tail = p;
		return;
	}
	p->next = temp->next;//case4 나머지.
	temp->next = p;
	return;
}

void delete_data(SLL *lst, int data)//삭제(단일리스트, 삭제데이터)
{
	Node *temp = Such_Node(lst, data);
	Node *prve = find_Prv_Node(lst, data);

	if (lst == NULL) return;
	if (temp == NULL)return;
	if (prve == NULL)return;

	if (lst->head == NULL)//case1 해드값이 아무것도 없을때.
	{
		Error_print();
		return;
	}
	if (lst->head == temp)//case2 헤드 값일때.
	{
		lst->head = temp->next;
		node_free(temp);
		return;
	}
	if (lst->tail == temp)//case3 테일 값일때.
	{
		node_free(temp);
		lst->tail = prve;
		return;
	}
	prve->next = temp->next;//case4 나머지
	node_free(temp);
	return;
}

int data_number(const SLL *lst, int data) //단일 링크드리스트에서 데이터가 몇번쨰 위치했는가.
{
	int p = 0;
	Node *temp = Such_Node(lst, data);

	if (lst == NULL) return -1;
	if (temp == NULL)return -1;
	
	while (lst->head != temp)
	{
		p = p + 1;
		temp = temp->next;
	}
	return p;
}

int finding_data(const SLL *lst, int data)//데이터 갯수 찾기.
{
	int p = find_data(lst, data);//시스템 감추기

	if (lst == NULL) return -1;

	return p;
}






int main()
{
	//테스트 코드. 유저 위주
	SLL lst;

	insert_data(&lst, NULL, 1);
	insert_data(&lst, NULL, 2);
	insert_data(&lst, NULL, 3);
	insert_data(&lst, NULL, 4);
	insert_data(&lst, NULL, 5);
	insert_data(&lst, NULL, 6);
	insert_data(&lst, NULL, 7);
	insert_data(&lst, NULL, 8);
	insert_data(&lst, NULL, 9);

	insert_data(&lst, 3, 10);
	insert_data(&lst, 5, 3);

	delete_data(&lst, 8);

	data_number(&lst, 3);

	finding_data(&lst, 5);
}
