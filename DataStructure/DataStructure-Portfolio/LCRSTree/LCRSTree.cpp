#include <iostream>

typedef char ElementType;

class LCRSNode {
public:
    ElementType Data;
    LCRSNode* LeftChild;
    LCRSNode* RightSibling;

    LCRSNode(ElementType newData);
    ~LCRSNode();
};

LCRSNode::LCRSNode(ElementType newData) : Data(newData), LeftChild(nullptr), RightSibling(nullptr) {}

LCRSNode::~LCRSNode() {}

class LCRSTree {
public:
    static LCRSNode* CreateNode(ElementType newData);
    static void DestroyNode(LCRSNode* node);
    static void DestroyTree(LCRSNode* root);
    static void AddChildNode(LCRSNode* parent, LCRSNode* child);
    static void PrintTree(LCRSNode* node, int depth);
};

LCRSNode* LCRSTree::CreateNode(ElementType newData) {
    return new LCRSNode(newData);
}

void LCRSTree::DestroyNode(LCRSNode* node) {
    delete node;
}

void LCRSTree::DestroyTree(LCRSNode* root) {
    if (root->RightSibling != nullptr)
        DestroyTree(root->RightSibling);

    if (root->LeftChild != nullptr)
        DestroyTree(root->LeftChild);

    root->LeftChild = nullptr;
    root->RightSibling = nullptr;

    DestroyNode(root);
}

void LCRSTree::AddChildNode(LCRSNode* parent, LCRSNode* child) {
    if (parent->LeftChild == nullptr) {
        parent->LeftChild = child;
    }
    else {
        LCRSNode* tempNode = parent->LeftChild;
        while (tempNode->RightSibling != nullptr)
            tempNode = tempNode->RightSibling;

        tempNode->RightSibling = child;
    }
}

void LCRSTree::PrintTree(LCRSNode* node, int depth) {
    for (int i = 0; i < depth; i++)
        std::cout << " ";

    std::cout << node->Data << std::endl;

    if (node->LeftChild != nullptr)
        PrintTree(node->LeftChild, depth + 1);

    if (node->RightSibling != nullptr)
        PrintTree(node->RightSibling, depth);
}

int main() {
    // 노드 생성
    LCRSNode* root = LCRSTree::CreateNode('A');

    LCRSNode* B = LCRSTree::CreateNode('B');
    LCRSNode* C = LCRSTree::CreateNode('C');
    LCRSNode* D = LCRSTree::CreateNode('D');
    LCRSNode* E = LCRSTree::CreateNode('E');
    LCRSNode* F = LCRSTree::CreateNode('F');
    LCRSNode* G = LCRSTree::CreateNode('G');
    LCRSNode* H = LCRSTree::CreateNode('H');
    LCRSNode* I = LCRSTree::CreateNode('I');
    LCRSNode* J = LCRSTree::CreateNode('J');
    LCRSNode* K = LCRSTree::CreateNode('K');

    // 트리에 노드 추가
    LCRSTree::AddChildNode(root, B);
    LCRSTree::AddChildNode(B, C);
    LCRSTree::AddChildNode(B, D);
    LCRSTree::AddChildNode(D, E);
    LCRSTree::AddChildNode(D, F);

    LCRSTree::AddChildNode(root, G);
    LCRSTree::AddChildNode(G, H);

    LCRSTree::AddChildNode(root, I);
    LCRSTree::AddChildNode(I, J);
    LCRSTree::AddChildNode(J, K);

    // 트리 출력
    LCRSTree::PrintTree(root, 0);

    // 트리 소멸시키기
    LCRSTree::DestroyTree(root);

    return 0;
}
