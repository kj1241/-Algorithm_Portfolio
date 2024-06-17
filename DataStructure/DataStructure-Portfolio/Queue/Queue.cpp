#include <iostream>
using namespace std;

#define MAX_QUEUE_SIZE 10

int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int is_Empty()
{
	return front == rear;
}

int is_End()
{
	return rear == MAX_QUEUE_SIZE - 1;
}

void enqueue(int item)
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
		return -1;
	}
	front++;
	return queue[front];
}

int main()
{
	enqueue(1);
	enqueue(2);
	enqueue(3);
	cout << dequeue() << endl;
	cout << dequeue() << endl;
	return 0;
}
//
//int front = 0, rear = 0;
//int* qArray;
//int maxQueueSize;
//
//void enqueue(int value)
//{
//	if (front == (rear + 1) % maxQueueSize)
//	{
//		cout << "더 이상 큐에 값을 저장할 수 없습니다." << endl;
//		return;
//	}
//	qArray[rear] = value;
//	rear = (rear + 1) % maxQueueSize;
//}
//
//void dequeue()
//{
//	if (front == rear)
//	{
//		cout << "큐가 비어있습니다." << endl;
//		return;
//	}
//	cout << "dequeue : " << qArray[front] << endl;
//	front = (front + 1) % maxQueueSize;
//}