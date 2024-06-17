#include <iostream>
using namespace std;

typedef struct
{
	char stackArr[10];
	int topIndex;
	char name;
} stack;

typedef stack* pStack;

void init(pStack ps, char c)
{
	ps->topIndex = 0;
	ps->name = c;
}

void push(pStack ps, char ch)
{
	if (ps->topIndex == 10)
	{
		cout << "stack " << ps->name << " is full" << endl;
		return;
	}
	ps->stackArr[ps->topIndex] = ch;
	ps->topIndex++;
}

char pop(pStack ps)
{
	if (ps->topIndex == 0)
	{
		cout << "stack " << ps->name << " is empty" << endl;
		return '\0';
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
	cout << endl;
	return 0;
}