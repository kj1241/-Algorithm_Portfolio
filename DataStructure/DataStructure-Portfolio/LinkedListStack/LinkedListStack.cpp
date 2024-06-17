#include <iostream>
#include <cstring>

// 노드 클래스 정의
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

// 연결 리스트 스택 클래스 정의
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

    stack.Push(new Node("첫 번째"));
    stack.Push(new Node("두 번째"));
    stack.Push(new Node("세 번째"));

    std::cout << "스택의 최상위: " << stack.Top()->Data << std::endl;
    std::cout << "스택의 크기: " << stack.GetSize() << std::endl;

    while (!stack.IsEmpty()) {
        Node* node = stack.Pop();
        std::cout << "팝: " << node->Data << std::endl;
        delete node;
    }

    std::cout << "스택이 비었는가: " << std::boolalpha << stack.IsEmpty() << std::endl;

    return 0;
}
