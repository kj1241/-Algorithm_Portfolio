#include <iostream>
#include <cstring>

// ��� Ŭ���� ����
class Node {
public:
    Node(const char* newData);
    ~Node();

    char* Data;
    Node* NextNode;
};

Node::Node(const char* newData) {
    size_t dataLen = strlen(newData) + 1;
    Data = new char[dataLen];
    strcpy_s(Data, dataLen, newData);
    NextNode = nullptr;
}

Node::~Node() {
    delete[] Data;
}

// ���� ����Ʈ ���� Ŭ���� ����
class LinkedListStack {
public:
    LinkedListStack();
    ~LinkedListStack();

    void Push(Node* newNode);
    Node* Pop();
    Node* Top() const;
    int GetSize() const;
    bool IsEmpty() const;

private:
    Node* List;
    Node* TopNode;
};

LinkedListStack::LinkedListStack() : List(nullptr), TopNode(nullptr) {}

LinkedListStack::~LinkedListStack() {
    while (!IsEmpty()) {
        Node* popped = Pop();
        delete popped;
    }
}

void LinkedListStack::Push(Node* newNode) {
    if (List == nullptr) {
        List = newNode;
    }
    else {
        Node* oldTop = List;
        while (oldTop->NextNode != nullptr) {
            oldTop = oldTop->NextNode;
        }
        oldTop->NextNode = newNode;
    }
    TopNode = newNode;
}

Node* LinkedListStack::Pop() {
    if (List == nullptr) {
        return nullptr;
    }

    Node* topNode = TopNode;
    if (List == TopNode) {
        List = nullptr;
        TopNode = nullptr;
    }
    else {
        Node* currentTop = List;
        while (currentTop != nullptr && currentTop->NextNode != TopNode) {
            currentTop = currentTop->NextNode;
        }
        TopNode = currentTop;
        if (currentTop != nullptr) {
            currentTop->NextNode = nullptr;
        }
    }
    return topNode;
}

Node* LinkedListStack::Top() const {
    return TopNode;
}

int LinkedListStack::GetSize() const {
    int count = 0;
    Node* current = List;
    while (current != nullptr) {
        current = current->NextNode;
        count++;
    }
    return count;
}

bool LinkedListStack::IsEmpty() const {
    return List == nullptr;
}

int main() {
    LinkedListStack stack;

    stack.Push(new Node("ù ��°"));
    stack.Push(new Node("�� ��°"));
    stack.Push(new Node("�� ��°"));

    std::cout << "������ �ֻ���: " << stack.Top()->Data << std::endl;
    std::cout << "������ ũ��: " << stack.GetSize() << std::endl;

    while (!stack.IsEmpty()) {
        Node* node = stack.Pop();
        std::cout << "��: " << node->Data << std::endl;
        delete node;
    }

    std::cout << "������ ����°�: " << std::boolalpha << stack.IsEmpty() << std::endl;

    return 0;
}
