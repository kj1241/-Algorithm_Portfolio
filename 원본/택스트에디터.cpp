#include <Windows.h>
#include <malloc.h>
#include <stdio.h>

//자료구조를 이용한 windows용 text editor 개발

typedef char ElementType;

typedef struct tagNode
{
	ElementType		data;
	struct tagNode	*next;
	struct tagNode  *prev;
} Node;

typedef Node* PNode;

typedef struct
{
	PNode	head;
	PNode	tail;
	int lenth;
} DLL;

typedef struct
{
	Node *top;
	Node *bottom;
	Node *dume;
} DUME;



Node *DLL_create_node(WPARAM wParam);
Node *Dume_create_node();
void DLL_free(Node *node);
DUME *DUME_init();
DLL *DLL_init(DUME *D);
void DLL_push_back(DLL *lst, WPARAM wParam);
void DLL_remove_final(DLL *lst);
void TextOut_Node(DLL *lst, HDC hdc);

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
////////////////////////////////////////////윈메인////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)

{
	HWND hwnd;
	MSG  msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Nodepad";
	RegisterClass(&WndClass);
	hwnd = CreateWindow("Nodepad",
		"B277004",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//////////////////////////////////////////프로시저/////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	DLL *lst= DLL_init();
	DUME *D = DUME_init();
	Node *temp;

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut_Node(lst,hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == VK_BACK)
		{
			DLL_remove_final(lst);
		}
		else
		{
			DLL_push_back(lst, wParam);
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;
}




Node *DLL_create_node(WPARAM wParam)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode) {
		newNode->data = wParam;
		newNode->next = NULL;
		newNode->prev = NULL; // for doubly linked list
	}
	return newNode;
}



void DLL_free(Node *node)
{
	if (node) {
		free((void *)node);
	}
}

DUME *DUME_init()
{
	DUME *D = (DUME *)malloc(sizeof(DUME));
	D->top = NULL;
	D->bottom = NULL;
	D->dume->next = NULL;
	D->dume->prev = D->dume;
	return D;
}

DLL *DLL_init()
{
	DLL *lst = (DLL *)malloc(sizeof(DLL));
	lst->head = NULL;
	lst->tail = NULL;
	lst->lenth = 0;
	return lst;
}

void DLL_push_back(DUME *D,DLL *lst, WPARAM wParam)
{
	if (!D||!lst) return;
	Node *last = lst->tail;
	Node *temp = DLL_create_node(wParam);
	if (!last)
	{
		lst->head = lst->tail = temp;
		temp->prev = D;
		lst->lenth = 1;
		return;
	}
	last->next = temp;
	temp->prev = last;
	lst->tail = temp;
	lst->lenth = lst->lenth+1;
	return;
	
}

void DLL_remove_final(DLL *lst)
{
	if (!lst || !lst->head)
	{
		return;
	}
	Node *prev = lst->tail->prev;
	if (!prev)
	{
		DLL_free(lst->head);
		lst->head = NULL;
		lst->tail = NULL;
		lst->lenth = 0;
	}
	Node *temp = lst->tail;
	prev->next = NULL;
	lst->tail = prev;
	lst->lenth = lst->lenth - 1;
	DLL_free(temp);
}

void TextOut_Node(DLL *lst, HDC hdc)
{
	for (int i = 0;i < lst->lenth;i++)
	{
		TextOut(hdc, sizeof(lst->head->data)*i, 0, (LPSTR)lst->head->data, sizeof(&(lst->head->data)));
		lst->head = lst->head->next;
	}
	return;
}