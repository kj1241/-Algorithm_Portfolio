#include <iostream>
using namespace std;
/*
int main()
{
	int a = 1, b = 2, c = 3;
	a = b;
	b = a;

	int temp=a;
	a = b;
	b = c;
	c = temp;

	a = a - b;
	b = b + a;
	a = b - a;

}

int sum_re(int n)
{
	if (n == 1)
		return 1;
	else
	{
		return(sum_re(n - 1) + n);
	}
}
int main()
{
	cout << sum_re(4);
}


void convert2bin(inn dec)
{

	if (dec <= 0) return;
	convert2bin(dec / 2);
	cout << dec % 2;
}

int main()
{
	int n;
	cout << "input number:";
	cin >> n;
	convert2bin(n);
	cout << "\n";
	return 0;
}
*/
/*
int factorial(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return n * factorial(n - 1);

}

int main()
{
	int i;
	cout << factorial(i);
	
}
*/
/*
int Fibo(int n)
{
	if (n == 1 || n == 2)
		return 1;

	return Fibo(n - 2) + Fibo(n - 1);
}

int main()
{
	int i;
	for (i = 1; i <= 15; i++)
		cout << Fibo(i) << endl;
}

*/
/*
typedef struct
{
	char stackArr[10];
	int topIndex;
	char name;
}stack;
typedef stack* pStack;

void init(pStack ps, char c)
{

	ps->topIndex = 0;
	ps->name = c;

}

void push(pStack ps, char ch)
{
	if (ps-> topIndex == 10)
	{
		cout << "stak" << ps->name;
		return;

	}
	ps->stackArr[ps->topIndex] = ch;
	ps->topIndex++;
}
char pop(pStack ps)
{
	if (ps->topIndex == 0)
	{
		cout << "stak" << ps->name;
		return;
	}
	ps->topIndex--;

	return ps->stackArr[ps->topIndex];
}

int main()
{
	stack s1, s2;

	init(&s1, 'A');
	init(&s2, 'B');

	push(&s1, 'd');
	push(&s1, 'a');
	push(&s1, 't');
	push(&s1, 'a');

	for (size_t i = 0; i < 4; i++)
	{
		cout << pop(&s1) << " ";
	}
}

*/
/*
#define MAX_QUEUE_SIZE 10

int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;
int is_Empty()
{
	if (front == rear)
		return 1;
	else
		return 0;
}
int is_End() {
	if (front > rear)
		return 1;
	else
		return 0;

}


void equeue(int item)
{
	if (is_End())
	{
		cout << "enqueue error" << endl;
		return;
	}
	rear++;
	queue[rear] = item;
}

int dequeue()
{
	if (is_Empty())
	{
		cout << "dequeue error" << endl;
		return;
	}
	front++;
	return queue[front];
}

int main()
{
	equeue(1);
}

*/
/*

int front = 0, rear = 0;
int* qArray;
int maxQueueSize; //큐의 크기를 입력받을 변수

void enqueue(int value) {
	if (front == (rear + 1) % maxQueueSize) {
		cout << "더 이상 큐에 값을 저장할 수 없습니다." << endl;
		return;
	}
	rear = rear % maxQueueSize;
	qArray[rear++] = value;
}

void dequeue() {
	if (front == rear) {
		cout << "큐가 비어있습니다." << endl;
		return;
	}
	front = front % maxQueueSize;
	cout << "dequeue : " << qArray[front++] << endl;
}

*/




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

LinkedList::LinkedList() {
	head = new Node;
	head->data = -1;
	tail = new Node;
	tail->data = -1;

	head->next = tail;
	tail->next = NULL;
}
LinkedList::~LinkedList() { 
	Node* now, * temp;
	for (now = head->next; now != tail; ) {
		temp = now->next;
		delete(now);
		now = temp;
	}
	delete(head);
	delete(tail);
}

void LinkedList::insertNode(int data) { 
	Node* newNode = new Node;
	newNode->data = data;
	Node* now = head;

	for (; now->next->data < data && now->next != tail; now = now->next);
	newNode->next = now->next;
	now->next = newNode;
}

void LinkedList::deletNode(int data) {

	Node* now, * temp;
	now = head->next; temp = head;
	for (; now->data != data && now != tail; temp = now, now = now->next);

	if (now != tail) {
		temp->next = now->next;
		delete(now);
	}
}


Node* LinkedList::findNode(int data) {
	Node* now = head->next;
	for (; now->data != data && now != tail; now = now->next);
	if (now != tail) return now;
	else return NULL;
}

void LinkedList::printNode() {
	Node* now;
	int i = 1;
	for (now = head->next; now != tail; now = now->next, i++)
		cout << now->data << " ";
	cout << endl;
}

int main()
{
	LinkedList  list;
	int i = 1, data = 0;
	list.insertNode(10);

	list.insertNode(20);
	list.insertNode(30);
	list.printNode();

}