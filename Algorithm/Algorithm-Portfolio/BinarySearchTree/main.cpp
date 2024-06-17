#include <iostream>

using namespace std;

struct BSTNode {
    int Data;
    BSTNode* Left;
    BSTNode* Right;
};

BSTNode* BST_CreateNode(int NewData) {
    BSTNode* NewNode = new BSTNode();
    NewNode->Left = nullptr;
    NewNode->Right = nullptr;
    NewNode->Data = NewData;
    return NewNode;
}

void BST_DestroyNode(BSTNode* Node) {
    delete Node;
}

void BST_DestroyTree(BSTNode* Tree) {
    if (Tree == nullptr) return;

    if (Tree->Right != nullptr)
        BST_DestroyTree(Tree->Right);
    if (Tree->Left != nullptr)
        BST_DestroyTree(Tree->Left);

    Tree->Left = nullptr;
    Tree->Right = nullptr;

    BST_DestroyNode(Tree);
}

BSTNode* BST_SearchNode(BSTNode* Tree, int Target) {
    if (Tree == nullptr)
        return nullptr;

    if (Tree->Data == Target)
        return Tree;
    else if (Tree->Data > Target)
        return BST_SearchNode(Tree->Left, Target);
    else
        return BST_SearchNode(Tree->Right, Target);
}

BSTNode* BST_SearchMinNode(BSTNode* Tree) {
    if (Tree == nullptr)
        return nullptr;

    if (Tree->Left == nullptr)
        return Tree;
    else
        return BST_SearchMinNode(Tree->Left);
}

void BST_InsertNode(BSTNode* Tree, BSTNode* Child) {
    if (Tree->Data < Child->Data) {
        if (Tree->Right == nullptr)
            Tree->Right = Child;
        else
            BST_InsertNode(Tree->Right, Child);
    }
    else if (Tree->Data > Child->Data) {
        if (Tree->Left == nullptr)
            Tree->Left = Child;
        else
            BST_InsertNode(Tree->Left, Child);
    }
}

BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, int Target) {
    BSTNode* Removed = nullptr;

    if (Tree == nullptr)
        return nullptr;

    if (Tree->Data > Target)
        Removed = BST_RemoveNode(Tree->Left, Tree, Target);
    else if (Tree->Data < Target)
        Removed = BST_RemoveNode(Tree->Right, Tree, Target);
    else {
        Removed = Tree;

        if (Tree->Left == nullptr && Tree->Right == nullptr) {
            if (Parent != nullptr) {
                if (Parent->Left == Tree)
                    Parent->Left = nullptr;
                else
                    Parent->Right = nullptr;
            }
        }
        else {
            if (Tree->Left != nullptr && Tree->Right != nullptr) {
                BSTNode* MinNode = BST_SearchMinNode(Tree->Right);
                MinNode = BST_RemoveNode(Tree, nullptr, MinNode->Data);
                Tree->Data = MinNode->Data;
            }
            else {
                BSTNode* Temp = (Tree->Left != nullptr) ? Tree->Left : Tree->Right;

                if (Parent != nullptr) {
                    if (Parent->Left == Tree)
                        Parent->Left = Temp;
                    else
                        Parent->Right = Temp;
                }
            }
        }
    }
    return Removed;
}

void BST_InorderPrintTree(BSTNode* Node) {
    if (Node == nullptr)
        return;

    BST_InorderPrintTree(Node->Left);
    cout << Node->Data << " ";
    BST_InorderPrintTree(Node->Right);
}

int main() {
    BSTNode* Tree = BST_CreateNode(123);

    BST_InsertNode(Tree, BST_CreateNode(22));
    BST_InsertNode(Tree, BST_CreateNode(9918));
    BST_InsertNode(Tree, BST_CreateNode(424));
    BST_InsertNode(Tree, BST_CreateNode(17));
    BST_InsertNode(Tree, BST_CreateNode(3));
    BST_InsertNode(Tree, BST_CreateNode(98));
    BST_InsertNode(Tree, BST_CreateNode(34));
    BST_InsertNode(Tree, BST_CreateNode(760));
    BST_InsertNode(Tree, BST_CreateNode(317));
    BST_InsertNode(Tree, BST_CreateNode(1));

    BSTNode* Node = BST_SearchNode(Tree, 17);
    if (Node != nullptr)
        cout << Node->Data << endl;
    else
        cout << "해당 노드가 없습니다" << endl;

    BST_InorderPrintTree(Tree);
    cout << endl;

    cout << "98 삭제 중..." << endl;
    Node = BST_RemoveNode(Tree, nullptr, 98);
    BST_DestroyNode(Node);

    BST_InorderPrintTree(Tree);
    cout << endl;

    cout << "111 삽입 중..." << endl;
    BST_InsertNode(Tree, BST_CreateNode(111));
    BST_InorderPrintTree(Tree);
    cout << endl;

    BST_DestroyTree(Tree);

    return 0;
}
