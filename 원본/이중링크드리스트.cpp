/*
2015.11.15 링크드리스트_이중(ver.1) MR.K
*/
#include <stdio.h>
#include <Windows.h>

/*
정의.
*/
typedef int ElementType;
typedef struct tagNode
{
	ElementType data;
	struct tagNode* next;
	struct tagNode* prev;
}Node;

typedef struct tagDLL
{
	Node* head;
	Node* tail;
}DLL;

/*
숙제.
*/

Node* DLL_cratenode(ElementType data)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = data;
	p->next = p->prev = NULL;
	return p;
}

void DLL_free(Node *p)
{
	free(p);
}

DLL *DLL_init()
{
	DLL *p = (DLL*)malloc(sizeof(DLL));
	p->head = p->tail = NULL;
	return p;
}

void DLL_deinit(DLL *lst)
{
	Node *p = lst->head; //지울 노드 
	Node *temp;//지우는 시점 다음을 저장.

	if (lst == NULL) return;//리스트가 없으면 잘못들어왔음으로 종료.

	while (&p)//노드가 존재하면 전부 실행
	{
		temp = p->next;
		free(p);
		p = temp;
	}
	free(lst);//p값이 널이더라도 , 와일문을 실행한후에도 동적할당한 DLL 해제.
}

int DLL_size(const DLL *lst)
{
	int p = 0;
	Node *temp = lst->head;

	if (lst == NULL) return;//리스트가 없으면 잘못들어왔음으로 종료.

	while (lst->head)
	{
		p = p + 1;
		temp = temp->next;
	}

	return p;
}

Node* DLL_count(DLL*lst, int pos)
{
	int i = 0;
	Node *temp = lst->head;

	if (pos > DLL_size(lst)) return;

	while (i != pos)
	{
		i = i + 1;
		temp = temp->next;
	}
	return temp;

}

void DLL_append(DLL *lst, ElementType data)//맨마직막 추가
{
	if (lst == NULL) return;

	Node *p = DLL_cratenode(data);
	p->prev = lst->tail;
	lst->tail->next = p;
	lst->tail = p;
}

void DLL_insert_before(DLL *lst, int pos, ElementType data)//찾는 위치 앞에 삽입.
{
	Node *p = DLL_cratenode(data);//만든노드.
	Node *temp = DLL_count(lst, pos);//찾는 노드.

	if (!lst) return;
	if (!temp) return;

	if (pos == 0)
	{
		lst->head = p;//case1 노드가 아무것도없을때 헤드에 연결.
		lst->tail = p;
		return;
	}
	if (temp == lst->head)//case2 노드가 앞에 하나있을때.
	{
		p->next = temp;
		temp->prev = p;
		lst->head = p;
	}
	p->prev = temp->prev;//case 3 그외에
	temp->prev->next = p;
	temp->prev = p;
	p->next = temp;
	return;
}

void DLL_insert_after(DLL *lst, int pos, ElementType data)//찾는 위치 뒤에 삽입.
{
	Node *p = DLL_cratenode(data);
	Node *temp = DLL_count(lst, pos);//찾는 노드.

	if (!lst) return;
	if (!temp) return;

	if (pos == 0)
	{
		lst->head = p;//case1 노드가 아무것도없을때 헤드에 연결.
		lst->tail = p;
		return;
	}
	if (temp->next == NULL)//cas2 해당하는 노드가 맨끝일때.
	{
		temp->next = p;
		p->prev = temp;
		lst->tail = p;
		return;
	}
	p->next = temp->next; //case3 그외에.
	temp->next->prev = p;
	p->prev = temp;
	temp->next = p; 
	return;
}

void DLL_remove(DLL *lst, int pos)
{
	Node *temp = DLL_count(lst, pos);//찾은노드

	if (!lst) return;
	if (!temp) return;//오류처리 찾은노드가 없으면 널값을 반환하기때문에 리턴

	if (temp->next == NULL)//case1 찾은노드가 마지막일떄
	{
		temp->prev->next = NULL;
		lst->tail = temp->prev;
		free(temp);
		return;
	}
	if (temp->prev == NULL)//case2 찾은 노드가 처음일때
	{
		temp->next->prev = NULL;
		lst->head = temp->next;
		free(temp);
		return;
	}
	temp->prev->next = temp->next;//case3 그외에.
	temp->next->prev = temp->prev;
	free(temp);
	return;
}

int main()
{
	DLL *lst = DLL_init();
	DLL_insert_after(&lst, 0, 1);
	DLL_insert_after(&lst, 1, 2);
	DLL_insert_after(&lst, 2, 3);
	DLL_insert_after(&lst, NULL, 1);
	DLL_insert_after(&lst, 1, 1);
	DLL_insert_before(&lst, 2, 5);
	DLL_remove(&lst, 2);
	DLL_deinit(&lst);
}