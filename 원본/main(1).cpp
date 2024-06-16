#include <iostream>
#include <list>
using namespace std;


/*
typedef int BTData;
struct BTreeNode
{
	BTData data;
	struct BTreeNode* left;
	struct BTreeNode* right;
};
BTreeNode* MakeBTreeNode(void)
{
	BTreeNode* nd = new BTreeNode;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

void DeleteBTreeNode(BTreeNode* bt) {
	delete bt;
}

BTData GetData(BTreeNode* bt) { return bt->data; }
void SetData(BTreeNode* bt, BTData data) { bt->data = data; }
BTreeNode* GetLeftSubTree(BTreeNode* bt) { return bt->left; }
BTreeNode* GetRightSubTree(BTreeNode* bt) { return bt->right; }

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->left != NULL)
		delete main->left;
	main->left = sub;
}
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->right != NULL)
		delete main->right;
	main->right = sub;
}
void print_node(BTreeNode* n)
{
	cout << "d:" << n->data << " ";
	if (n->left != NULL) cout << "l:" << n->left->data << " ";
	if (n->right != NULL) cout << "r:" << n->right->data << " ";
	cout << endl;
}
int main()
{

	BTreeNode* bt1 = MakeBTreeNode();
	BTreeNode* bt2 = MakeBTreeNode();
	BTreeNode* bt3 = MakeBTreeNode();
	BTreeNode* bt4 = MakeBTreeNode();

	SetData(bt1, 1);
	SetData(bt2, 2);
	SetData(bt3, 3);
	SetData(bt4, 4);

	MakeLeftSubTree(bt1, bt2);
	MakeRightSubTree(bt1, bt3);
	MakeLeftSubTree(bt2, bt4);

	cout << GetData(GetLeftSubTree(bt1))<<endl;
	cout << GetData(GetLeftSubTree(GetLeftSubTree(bt1))) << endl;
	
	print_node(bt1);
	print_node(bt2);
	print_node(bt3);
	print_node(bt4);

	DeleteBTreeNode(bt1);
	DeleteBTreeNode(bt2);
	DeleteBTreeNode(bt3);
	DeleteBTreeNode(bt4);

}

*/
/*
int main()
{
	int n = 100;
	int sum=0;
	for (int i = 0; i < n; i++)
		sum += (i + 1);
	cout << sum << endl; //O(n)

	cout << (n + 1) * n / 2<<endl; // O(1)
}
*/

#define UNIT_DISTANCE 1
#define MAPSIZE 8

class Node {
public:
	int posX, posY;
	int F, G, H;	//F(Fitness) G(Goal) H(Heuristic)
	Node* parent;
	bool IsBlock;
};

Node mapData[MAPSIZE][MAPSIZE];

list<Node*> openList;
//list<Node*> closedList;
Node* Start, * End;

void InitializeNodes()
{
	for (int y = 0; y < MAPSIZE; y++) {
		for (int x = 0; x < MAPSIZE; x++) {
			mapData[y][x].posX = x;
			mapData[y][x].posY = y;
			mapData[y][x].F = mapData[y][x].G = mapData[y][x].H = 0;
			mapData[y][x].IsBlock = false;
			mapData[y][x].parent = NULL;
		}
	}
}

void AstarInsertOpenList(Node* node, Node* parent, int Gdist = 0)
{
	if (node->posX < 0 || node->posY < 0 ||
		node->posX > MAPSIZE - 1 || node->posY > MAPSIZE - 1 || node->IsBlock)
		return;
	//list<Node*>::iterator iter2 = find(closedList.begin(), closedList.end(), node);
	//if (iter2 != closedList.end())
	// return;
	list<Node*>::iterator iter1;
	for (iter1 = openList.begin(); iter1 != openList.end(); iter1++)
	{
		if (node == (*iter1)) {
			if (Gdist < node->G) { openList.erase(iter1); }
			else { return; }
			break;
		}
	}
	node->parent = parent;
	node->G = Gdist;
	node->H = UNIT_DISTANCE * (abs(End->posX - node->posX) + abs(End->posY - node->posY));
	node->F = node->G + node->H;

	list<Node*>::iterator iter;
	for (iter = openList.begin(); iter != openList.end(); iter++) {
		if (node->F <= (*iter)->F) {
			openList.insert(iter, node);
			return;
		}
	}
	openList.insert(iter, node);
}

//AstarSetObstacleBlock(4, 2);
//AstarSetStartEndPoints(&mapData[3][2], &mapData[3][6]);

void AstarSetObstacleBlock(int x, int y) {
	mapData[y][x].IsBlock = true;
}
void AstarSetStartEndPoints(Node* S, Node* E) {
	Start = S;
	End = E;
	AstarInsertOpenList(Start, NULL, 0);
}


//AstarFindRoute(); 

void AstarFindRoute() {
	Node* node;
	while (!openList.empty()) {
		list<Node*>::iterator iter = openList.begin();
		node = *iter;
		openList.erase(iter);
		node->IsBlock = true;
		//closedList.push_back(node);
		if (node == End) break;

		AstarInsertOpenList(&mapData[node->posY - 1][node->posX - 1], node, node->G + 1.4 * UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY - 1][node->posX], node, node->G + UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY - 1][node->posX + 1], node, node->G + 1.4 * UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY][node->posX - 1], node, node->G + UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY][node->posX + 1], node, node->G + UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY + 1][node->posX - 1], node, node->G + 1.4 * UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY + 1][node->posX], node, node->G + UNIT_DISTANCE);
		AstarInsertOpenList(&mapData[node->posY + 1][node->posX + 1], node, node->G + 1.4 * UNIT_DISTANCE);
	}
}

void TestPrint() {
	for (int y = 0; y < MAPSIZE; y++) {
		for (int x = 0; x < MAPSIZE; x++) {
			cout << "[" << x << "," << y << "]"; cout.width(3);	cout << mapData[y][x].F << " ";
		}
		cout << endl;
	}
}
void AstarMakePath() {
	cout << "Result : ";
	Node* node = End;
	while (node != Start) {
		cout << "[" << node->posX << "," << node->posY << "] ";
		node = node->parent;
	}
	cout << "[" << node->posX << "," << node->posY << "] ";
}

int main()
{
	cout << "A* 알고리즘" << endl << endl;

	InitializeNodes();

	AstarSetObstacleBlock(4, 2);	
	AstarSetObstacleBlock(4, 3);
	AstarSetObstacleBlock(4, 4);
	AstarSetObstacleBlock(3, 2);
	AstarSetObstacleBlock(2, 4);
	AstarSetObstacleBlock(3, 4);

	//int StartX = 2, StartY = 3;
	//int EndX = 6, EndY = 3;
	AstarSetStartEndPoints(&mapData[3][2], &mapData[3][6]);		

	cout << endl << "-----------------초기 세팅----------------" << endl << endl;
	TestPrint();
	AstarFindRoute();
	cout << endl << "-----------------전체 결과----------------" << endl << endl;
	TestPrint();
	cout << endl << "-----------------최단 경로----------------" << endl << endl;
	AstarMakePath();
	return 1;
}