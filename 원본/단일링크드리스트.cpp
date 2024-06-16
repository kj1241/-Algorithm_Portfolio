/*
���� ��ũ�帮��Ʈ(ver.1 2015.11.08) mr.K
*/
#include <stdio.h>
#include <windows.h>

//template <typename T> �� �� ���� .... ���ø� ���� ������...
/*
����
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
���α׷��� �ڵ�, �ý��� �ڵ�
*/

void Error_print()//���� �޼��� ��� ��� winapi�� �޼��� �ڽ� ���� ����
{
	printf("error");
}

Node* crate_node(int data)//��� â��
{
	Node *NewNode = new Node;// �����Ҵ�(cpp)
	//Node  *NewNode=(Node*)malloc(sizeof(Node));
	NewNode->data = data;
	NewNode->next = NULL;
	return NewNode;
}

void node_free(Node *node)//�����Ҵ� ����
{
	if (node == NULL) return;
	free((void *)node);
}

int find_data(const SLL *lst, int data_fine)//�־��� �����ͷ� ��尹�� ã��
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

Node *Such_Node(const SLL *lst, int data_fine)//�־��� �����ͷ� ��� ã��
{
	Node *temp = lst->head;

	if (lst == NULL) return nullptr;
	if (temp == NULL)return nullptr;

	int p = find_data(lst, data_fine);
	if (p == 0 || p > 1) //���� �ý��۸޼��� ����� ���ؼ�;
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
void New_node(SLL *lst, int data)//�ص尡 �ΰ��϶� ���ο� ��常���.
{
	Node *temp = crate_node(data);

	if (lst == NULL) return;
	if (lst->head != NULL) return;

	lst->head = temp;
	return;
}
/*
���� �ڵ�
*/

void insert_data(SLL *lst, int data_fine, int data)//����(���ϸ���Ʈ , ������ ��������ġ, ������)
{
	Node *p = crate_node(data);
	Node *temp = Such_Node(lst, data_fine);
	
	if (lst == NULL) return;
	if (temp == NULL)return;
	
	if (data_fine == NULL)//case1 ������ ������ ���� ������.
	{
		New_node(lst, data);
	}	
	if (lst->head == NULL)//case2 �ص尡 ����Ű�°��� �ƹ��͵�������.
	{
		lst->head = p;
		lst->tail = p;
		return;	
	}
	if (lst->tail == temp)//case3 �������� �����Ҷ�.
	{
		temp->next = p;
		lst->tail = p;
		return;
	}
	p->next = temp->next;//case4 ������.
	temp->next = p;
	return;
}

void delete_data(SLL *lst, int data)//����(���ϸ���Ʈ, ����������)
{
	Node *temp = Such_Node(lst, data);
	Node *prve = find_Prv_Node(lst, data);

	if (lst == NULL) return;
	if (temp == NULL)return;
	if (prve == NULL)return;

	if (lst->head == NULL)//case1 �ص尪�� �ƹ��͵� ������.
	{
		Error_print();
		return;
	}
	if (lst->head == temp)//case2 ��� ���϶�.
	{
		lst->head = temp->next;
		node_free(temp);
		return;
	}
	if (lst->tail == temp)//case3 ���� ���϶�.
	{
		node_free(temp);
		lst->tail = prve;
		return;
	}
	prve->next = temp->next;//case4 ������
	node_free(temp);
	return;
}

int data_number(const SLL *lst, int data) //���� ��ũ�帮��Ʈ���� �����Ͱ� ����� ��ġ�ߴ°�.
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

int finding_data(const SLL *lst, int data)//������ ���� ã��.
{
	int p = find_data(lst, data);//�ý��� ���߱�

	if (lst == NULL) return -1;

	return p;
}






int main()
{
	//�׽�Ʈ �ڵ�. ���� ����
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
