#include <iostream>
#include <cstring>

// Node 클래스 정의
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

// LinkedQueue 클래스 정의
class LinkedQueue {
public:
    LinkedQueue();
    ~LinkedQueue();

    void Enqueue(Node* newNode);
    Node* Dequeue();
    bool IsEmpty() const;
    int GetSize() const;

private:
    Node* Front;
    Node* Rear;
    int Count;
};

LinkedQueue::LinkedQueue() : Front(nullptr), Rear(nullptr), Count(0) {}

LinkedQueue::~LinkedQueue() {
    while (!IsEmpty()) {
        Node* popped = Dequeue();
        delete popped;
    }
}

void LinkedQueue::Enqueue(Node* newNode) {
    if (Front == nullptr) {
        Front = newNode;
        Rear = newNode;
    }
    else {
        Rear->NextNode = newNode;
        Rear = newNode;
    }
    Count++;
}

Node* LinkedQueue::Dequeue() {
    if (IsEmpty()) {
        return nullptr;
    }

    Node* frontNode = Front;

    if (Front->NextNode == nullptr) {
        Front = nullptr;
        Rear = nullptr;
    }
    else {
        Front = Front->NextNode;
    }

    Count--;
    return frontNode;
}

bool LinkedQueue::IsEmpty() const {
    return Front == nullptr;
}

int LinkedQueue::GetSize() const {
    return Count;
}

int main() {
    LinkedQueue queue;

    queue.Enqueue(new Node("abc"));
    queue.Enqueue(new Node("def"));
    queue.Enqueue(new Node("efg"));
    queue.Enqueue(new Node("hij"));

    std::cout << "Queue Size: " << queue.GetSize() << std::endl;

    while (!queue.IsEmpty()) {
        Node* popped = queue.Dequeue();
        std::cout << "Dequeue: " << popped->Data << std::endl;
        delete popped;
    }

    return 0;
}
