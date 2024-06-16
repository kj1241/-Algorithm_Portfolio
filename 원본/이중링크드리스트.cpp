/*
2015.11.15 ��ũ�帮��Ʈ_����(ver.1) MR.K
*/
#include <stdio.h>
#include <Windows.h>

/*
����.
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
����.
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
	Node *p = lst->head; //���� ��� 
	Node *temp;//����� ���� ������ ����.

	if (lst == NULL) return;//����Ʈ�� ������ �߸����������� ����.

	while (&p)//��尡 �����ϸ� ���� ����
	{
		temp = p->next;
		free(p);
		p = temp;
	}
	free(lst);//p���� ���̴��� , ���Ϲ��� �������Ŀ��� �����Ҵ��� DLL ����.
}

int DLL_size(const DLL *lst)
{
	int p = 0;
	Node *temp = lst->head;

	if (lst == NULL) return;//����Ʈ�� ������ �߸����������� ����.

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

void DLL_append(DLL *lst, ElementType data)//�Ǹ����� �߰�
{
	if (lst == NULL) return;

	Node *p = DLL_cratenode(data);
	p->prev = lst->tail;
	lst->tail->next = p;
	lst->tail = p;
}

void DLL_insert_before(DLL *lst, int pos, ElementType data)//ã�� ��ġ �տ� ����.
{
	Node *p = DLL_cratenode(data);//������.
	Node *temp = DLL_count(lst, pos);//ã�� ���.

	if (!lst) return;
	if (!temp) return;

	if (pos == 0)
	{
		lst->head = p;//case1 ��尡 �ƹ��͵������� ��忡 ����.
		lst->tail = p;
		return;
	}
	if (temp == lst->head)//case2 ��尡 �տ� �ϳ�������.
	{
		p->next = temp;
		temp->prev = p;
		lst->head = p;
	}
	p->prev = temp->prev;//case 3 �׿ܿ�
	temp->prev->next = p;
	temp->prev = p;
	p->next = temp;
	return;
}

void DLL_insert_after(DLL *lst, int pos, ElementType data)//ã�� ��ġ �ڿ� ����.
{
	Node *p = DLL_cratenode(data);
	Node *temp = DLL_count(lst, pos);//ã�� ���.

	if (!lst) return;
	if (!temp) return;

	if (pos == 0)
	{
		lst->head = p;//case1 ��尡 �ƹ��͵������� ��忡 ����.
		lst->tail = p;
		return;
	}
	if (temp->next == NULL)//cas2 �ش��ϴ� ��尡 �ǳ��϶�.
	{
		temp->next = p;
		p->prev = temp;
		lst->tail = p;
		return;
	}
	p->next = temp->next; //case3 �׿ܿ�.
	temp->next->prev = p;
	p->prev = temp;
	temp->next = p; 
	return;
}

void DLL_remove(DLL *lst, int pos)
{
	Node *temp = DLL_count(lst, pos);//ã�����

	if (!lst) return;
	if (!temp) return;//����ó�� ã����尡 ������ �ΰ��� ��ȯ�ϱ⶧���� ����

	if (temp->next == NULL)//case1 ã����尡 �������ϋ�
	{
		temp->prev->next = NULL;
		lst->tail = temp->prev;
		free(temp);
		return;
	}
	if (temp->prev == NULL)//case2 ã�� ��尡 ó���϶�
	{
		temp->next->prev = NULL;
		lst->head = temp->next;
		free(temp);
		return;
	}
	temp->prev->next = temp->next;//case3 �׿ܿ�.
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