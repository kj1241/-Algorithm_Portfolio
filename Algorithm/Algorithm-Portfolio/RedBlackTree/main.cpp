#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

enum RBTColor { RED, BLACK };

typedef int ElementType;

struct RBTNode 
{
    ElementType Data;
    RBTColor Color;
    RBTNode* Parent;
    RBTNode* Left;
    RBTNode* Right;
};

RBTNode* Nil = new RBTNode{ 0, BLACK, nullptr, nullptr, nullptr };

RBTNode* RBT_CreateNode(ElementType NewData)
{
    RBTNode* NewNode = new RBTNode{ NewData, BLACK, nullptr, Nil, Nil };
    return NewNode;
}

void RBT_DestroyNode(RBTNode* Node)
{
    delete Node;
}

void RBT_DestroyTree(RBTNode* Tree)
{
    if (Tree == Nil) return;

    if (Tree->Right != Nil)
        RBT_DestroyTree(Tree->Right);

    if (Tree->Left != Nil)
        RBT_DestroyTree(Tree->Left);

    Tree->Left = Nil;
    Tree->Right = Nil;

    RBT_DestroyNode(Tree);
}

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target) 
{
    if (Tree == Nil)
        return nullptr;

    if (Tree->Data > Target)
        return RBT_SearchNode(Tree->Left, Target);
    else if (Tree->Data < Target)
        return RBT_SearchNode(Tree->Right, Target);
    else
        return Tree;
}

RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
    if (Tree == Nil)
        return Nil;

    if (Tree->Left == Nil)
        return Tree;
    else
        return RBT_SearchMinNode(Tree->Left);
}

void RBT_InsertNodeHelper(RBTNode*& Tree, RBTNode* NewNode) 
{
    if (Tree == Nil) {
        Tree = NewNode;
        NewNode->Parent = nullptr;
    }
    else if (Tree->Data < NewNode->Data) {
        if (Tree->Right == Nil) {
            Tree->Right = NewNode;
            NewNode->Parent = Tree;
        }
        else {
            RBT_InsertNodeHelper(Tree->Right, NewNode);
        }
    }
    else {
        if (Tree->Left == Nil) {
            Tree->Left = NewNode;
            NewNode->Parent = Tree;
        }
        else {
            RBT_InsertNodeHelper(Tree->Left, NewNode);
        }
    }
}

void RBT_RotateRight(RBTNode*& Root, RBTNode* Parent) 
{
    RBTNode* LeftChild = Parent->Left;
    Parent->Left = LeftChild->Right;

    if (LeftChild->Right != Nil)
        LeftChild->Right->Parent = Parent;

    LeftChild->Parent = Parent->Parent;

    if (Parent->Parent == nullptr)
        Root = LeftChild;
    else if (Parent == Parent->Parent->Left)
        Parent->Parent->Left = LeftChild;
    else
        Parent->Parent->Right = LeftChild;

    LeftChild->Right = Parent;
    Parent->Parent = LeftChild;
}

void RBT_RotateLeft(RBTNode*& Root, RBTNode* Parent) 
{
    RBTNode* RightChild = Parent->Right;
    Parent->Right = RightChild->Left;

    if (RightChild->Left != Nil)
        RightChild->Left->Parent = Parent;

    RightChild->Parent = Parent->Parent;

    if (Parent->Parent == nullptr)
        Root = RightChild;
    else if (Parent == Parent->Parent->Left)
        Parent->Parent->Left = RightChild;
    else
        Parent->Parent->Right = RightChild;

    RightChild->Left = Parent;
    Parent->Parent = RightChild;
}

void RBT_RebuildAfterInsert(RBTNode*& Root, RBTNode* X) 
{
    while (X != Root && X->Parent->Color == RED) 
    {
        if (X->Parent == X->Parent->Parent->Left) 
        {
            RBTNode* Uncle = X->Parent->Parent->Right;
            if (Uncle->Color == RED) {
                X->Parent->Color = BLACK;
                Uncle->Color = BLACK;
                X->Parent->Parent->Color = RED;
                X = X->Parent->Parent;
            }
            else 
            {
                if (X == X->Parent->Right) 
                {
                    X = X->Parent;
                    RBT_RotateLeft(Root, X);
                }
                X->Parent->Color = BLACK;
                X->Parent->Parent->Color = RED;
                RBT_RotateRight(Root, X->Parent->Parent);
            }
        }
        else 
        {
            RBTNode* Uncle = X->Parent->Parent->Left;
            if (Uncle->Color == RED) {
                X->Parent->Color = BLACK;
                Uncle->Color = BLACK;
                X->Parent->Parent->Color = RED;
                X = X->Parent->Parent;
            }
            else 
            {
                if (X == X->Parent->Left) {
                    X = X->Parent;
                    RBT_RotateRight(Root, X);
                }
                X->Parent->Color = BLACK;
                X->Parent->Parent->Color = RED;
                RBT_RotateLeft(Root, X->Parent->Parent);
            }
        }
    }
    Root->Color = BLACK;
}

void RBT_InsertNode(RBTNode*& Tree, RBTNode* NewNode) 
{
    RBT_InsertNodeHelper(Tree, NewNode);
    NewNode->Color = RED;
    NewNode->Left = Nil;
    NewNode->Right = Nil;
    RBT_RebuildAfterInsert(Tree, NewNode);
}

void RBT_RebuildAfterRemove(RBTNode*& Root, RBTNode* Successor)
{
    RBTNode* Sibling = nullptr;

    while (Successor != Root && Successor->Color == BLACK) 
    {
        if (Successor == Successor->Parent->Left)
        {
            Sibling = Successor->Parent->Right;

            if (Sibling->Color == RED) {
                Sibling->Color = BLACK;
                Successor->Parent->Color = RED;
                RBT_RotateLeft(Root, Successor->Parent);
                Sibling = Successor->Parent->Right;
            }
            if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK) 
            {
                Sibling->Color = RED;
                Successor = Successor->Parent;
            }
            else 
            {
                if (Sibling->Right->Color == BLACK) 
                {
                    Sibling->Left->Color = BLACK;
                    Sibling->Color = RED;
                    RBT_RotateRight(Root, Sibling);
                    Sibling = Successor->Parent->Right;
                }
                Sibling->Color = Successor->Parent->Color;
                Successor->Parent->Color = BLACK;
                Sibling->Right->Color = BLACK;
                RBT_RotateLeft(Root, Successor->Parent);
                Successor = Root;
            }
        }
        else {
            Sibling = Successor->Parent->Left;

            if (Sibling->Color == RED)
            {
                Sibling->Color = BLACK;
                Successor->Parent->Color = RED;
                RBT_RotateRight(Root, Successor->Parent);
                Sibling = Successor->Parent->Left;
            }
            if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK)
            {
                Sibling->Color = RED;
                Successor = Successor->Parent;
            }
            else 
            {
                if (Sibling->Left->Color == BLACK)
                {
                    Sibling->Right->Color = BLACK;
                    Sibling->Color = RED;
                    RBT_RotateLeft(Root, Sibling);
                    Sibling = Successor->Parent->Left;
                }
                Sibling->Color = Successor->Parent->Color;
                Successor->Parent->Color = BLACK;
                Sibling->Left->Color = BLACK;
                RBT_RotateRight(Root, Successor->Parent);
                Successor = Root;
            }
        }
    }

    Successor->Color = BLACK;
}

RBTNode* RBT_RemoveNode(RBTNode*& Root, ElementType Data) 
{
    RBTNode* Removed = nullptr;
    RBTNode* Successor = nullptr;
    RBTNode* Target = RBT_SearchNode(Root, Data);

    if (Target == nullptr)
        return nullptr;

    if (Target->Left == Nil || Target->Right == Nil) 
    {
        Removed = Target;
    }
    else {
        Removed = RBT_SearchMinNode(Target->Right);
        Target->Data = Removed->Data;
    }

    Successor = (Removed->Left != Nil) ? Removed->Left : Removed->Right;
    Successor->Parent = Removed->Parent;

    if (Removed->Parent == nullptr) 
    {
        Root = Successor;
    }
    else if (Removed == Removed->Parent->Left)
    {
        Removed->Parent->Left = Successor;
    }
    else 
    {
        Removed->Parent->Right = Successor;
    }

    if (Removed->Color == BLACK)
        RBT_RebuildAfterRemove(Root, Successor);

    return Removed;
}



void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount) 
{
    if (Node == Nil)
        return;

    if (Node->Color == BLACK)
        BlackCount++;

    for (int i = 0; i < Depth; i++)
        cout << "  ";

    cout << Node->Data << " " << (Node->Color == RED ? "RED" : "BLACK")
        << " [" << (Node->Parent ? (Node->Parent->Left == Node ? 'L' : 'R') : 'X')
        << "," << (Node->Parent ? Node->Parent->Data : -1) << "] "
        << (Node->Left == Nil && Node->Right == Nil ? "--------- " + to_string(BlackCount) : "")
        << endl;

    RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
    RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}

int main() 
{
    RBTNode* Tree = Nil;

    while (true) 
    {
        int cmd = 0;
        int param = 0;

        cout << "Enter command number :\n";
        cout << "(1) Create a node, (2) Remove a node, (3) Search a Node\n";
        cout << "(4) Display Tree (5) quit\n";
        cout << "command number:";

        cin >> cmd;

        if (cmd < 1 || cmd > 5) 
        {
            cout << "Invalid command number.\n";
            continue;
        }
        else if (cmd == 4) 
        {
            RBT_PrintTree(Tree, 0, 0);
            cout << endl;
            continue;
        }
        else if (cmd == 5) 
        {
            break;
        }

        cout << "Enter parameter (1~200) :\n";
        cin >> param;

        if (param < 1 || param > 200) 
        {
            cout << "Invalid parameter." << param << endl;
            continue;
        }

        switch (cmd) {
        case 1:
            RBT_InsertNode(Tree, RBT_CreateNode(param));
            break;
        case 2:
        {
            RBTNode* Node = RBT_RemoveNode(Tree, param);
            if (Node == nullptr)
                cout << "Not found node to delete:" << param << endl;
            else
                RBT_DestroyNode(Node);
        }
        break;
        case 3:
        {
            RBTNode* Node = RBT_SearchNode(Tree, param);
            if (Node == nullptr)
                cout << "Not found node:" << param << endl;
            else
                cout << "Found Node: " << Node->Data << "(Color:" << (Node->Color == RED ? "RED" : "BLACK") << ")\n";
        }
        break;
        }

        cout << endl;
    }

    RBT_DestroyTree(Tree);
    delete Nil;

    return 0;
}

