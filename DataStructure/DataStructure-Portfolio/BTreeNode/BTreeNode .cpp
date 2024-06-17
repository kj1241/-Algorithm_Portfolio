//#include <iostream>
//using namespace std;
//
//typedef int BTData;
//
//struct BTreeNode {
//	BTData data;
//	BTreeNode* left;
//	BTreeNode* right;
//};
//
//BTreeNode* MakeBTreeNode(void) {
//	BTreeNode* nd = new BTreeNode;
//	nd->left = NULL;
//	nd->right = NULL;
//	return nd;
//}
//
//void DeleteBTreeNode(BTreeNode* bt) {
//	if (bt != NULL) {
//		DeleteBTreeNode(bt->left);
//		DeleteBTreeNode(bt->right);
//		delete bt;
//	}
//}
//
//BTData GetData(BTreeNode* bt) {
//	return bt->data;
//}
//
//void SetData(BTreeNode* bt, BTData data) {
//	bt->data = data;
//}
//
//BTreeNode* GetLeftSubTree(BTreeNode* bt) {
//	return bt->left;
//}
//
//BTreeNode* GetRightSubTree(BTreeNode* bt) {
//	return bt->right;
//}
//
//void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) {
//	if (main->left != NULL)
//		DeleteBTreeNode(main->left);
//	main->left = sub;
//}
//
//void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) {
//	if (main->right != NULL)
//		DeleteBTreeNode(main->right);
//	main->right = sub;
//}
//
//void print_node(BTreeNode* n) {
//	cout << "d:" << n->data << " ";
//	if (n->left != NULL) cout << "l:" << n->left->data << " ";
//	if (n->right != NULL) cout << "r:" << n->right->data << " ";
//	cout << endl;
//}
//
//int main() {
//	BTreeNode* bt1 = MakeBTreeNode();
//	BTreeNode* bt2 = MakeBTreeNode();
//	BTreeNode* bt3 = MakeBTreeNode();
//	BTreeNode* bt4 = MakeBTreeNode();
//
//	SetData(bt1, 1);
//	SetData(bt2, 2);
//	SetData(bt3, 3);
//	SetData(bt4, 4);
//
//	MakeLeftSubTree(bt1, bt2);
//	MakeRightSubTree(bt1, bt3);
//	MakeLeftSubTree(bt2, bt4);
//
//	cout << GetData(GetLeftSubTree(bt1)) << endl;
//	cout << GetData(GetLeftSubTree(GetLeftSubTree(bt1))) << endl;
//
//	print_node(bt1);
//	print_node(bt2);
//	print_node(bt3);
//	print_node(bt4);
//
//	DeleteBTreeNode(bt1);
//	// bt2, bt3, bt4는 이미 서브트리 삭제 과정에서 삭제되므로 명시적으로 삭제할 필요가 없습니다.
//}


#include <iostream>
using namespace std;

typedef int BTData;

struct BTreeNode 
{
    BTData data;
    BTreeNode* left;
    BTreeNode* right;
};

BTreeNode* MakeBTreeNode(void) 
{
    BTreeNode* nd = new BTreeNode;
    nd->left = nullptr;
    nd->right = nullptr;
    return nd;
}

void DeleteBTreeNode(BTreeNode* bt) 
{
    if (bt != nullptr) {
        DeleteBTreeNode(bt->left);
        DeleteBTreeNode(bt->right);
        delete bt;
    }
}

BTData GetData(BTreeNode* bt) 
{
    return bt->data;
}

void SetData(BTreeNode* bt, BTData data) 
{
    bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt) 
{
    return bt->left;
}

BTreeNode* GetRightSubTree(BTreeNode* bt) 
{
    return bt->right;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) 
{
    if (main->left != nullptr)
        DeleteBTreeNode(main->left);
    main->left = sub;
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) 
{
    if (main->right != nullptr)
        DeleteBTreeNode(main->right);
    main->right = sub;
}

void print_node(BTreeNode* n) 
{
    cout << "d:" << n->data << " ";
    if (n->left != nullptr) cout << "l:" << n->left->data << " ";
    if (n->right != nullptr) cout << "r:" << n->right->data << " ";
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

    cout << GetData(GetLeftSubTree(bt1)) << endl;
    cout << GetData(GetLeftSubTree(GetLeftSubTree(bt1))) << endl;

    print_node(bt1);
    print_node(bt2);
    print_node(bt3);
    print_node(bt4);

    DeleteBTreeNode(bt1);
    // bt2, bt3, bt4는 이미 서브트리 삭제 과정에서 삭제되므로 명시적으로 삭제할 필요가 없습니다.

    return 0;
}
