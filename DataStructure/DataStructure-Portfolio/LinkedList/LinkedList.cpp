#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

class LinkedList
{
public:
	Node* head;
	Node* tail;
	LinkedList();
	~LinkedList();
	void insertNode(int data);
	void deletNode(int data);
	Node* findNode(int data);
	void printNode();
};

LinkedList::LinkedList()
{
	head = new Node;
	head->data = -1;
	tail = new Node;
	tail->data = -1;

	head->next = tail;
	tail->next = NULL;
}

LinkedList::~LinkedList()
{
	Node* now, * temp;
	for (now = head->next; now != tail; )
	{
		temp = now->next;
		delete(now);
		now = temp;
	}
	delete(head);
	delete(tail);
}

void LinkedList::insertNode(int data)
{
	Node* newNode = new Node;
	newNode->data = data;
	Node* now = head;

	for (; now->next->data < data && now->next != tail; now = now->next);
	newNode->next = now->next;
	now->next = newNode;
}

void LinkedList::deletNode(int data)
{
	Node* now, * temp;
	now = head->next;
	temp = head;
	for (; now->data != data && now != tail; temp = now, now = now->next);

	if (now != tail)
	{
		temp->next = now->next;
		delete(now);
	}
}

Node* LinkedList::findNode(int data)
{
	Node* now = head->next;
	for (; now->data != data && now != tail; now = now->next);
	if (now != tail) return now;
	else return NULL;
}

void LinkedList::printNode()
{
	Node* now;
	for (now = head->next; now != tail; now = now->next)
		cout << now->data << " ";
	cout << endl;
}

int main()
{
	LinkedList list;
	list.insertNode(10);
	list.insertNode(20);
	list.insertNode(30);
	list.printNode();
	return 0;
}