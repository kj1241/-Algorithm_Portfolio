#include <iostream>
#include <windows.h>

template<typename T>
class ConcurrentStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    // Stack head
    Node* head;

public:
    ConcurrentStack() : head(nullptr) {}

    ~ConcurrentStack() {
        while (head) {
            Node* node = static_cast<Node*>(InterlockedExchangePointer(reinterpret_cast<PVOID*>(&head), head->next));
            delete node;
        }
    }

    // Push method
    void push(T value) {
        Node* newNode = new Node(value);
        Node* oldHead;
        do {
            oldHead = head;
            newNode->next = oldHead;
        } while (InterlockedCompareExchangePointer(reinterpret_cast<PVOID*>(&head), newNode, oldHead) != oldHead);
    }

    // Pop method
    bool pop(T& result) {
        Node* oldHead;
        Node* newHead;
        do {
            oldHead = head;
            if (oldHead == nullptr) {
                return false;
            }
            newHead = oldHead->next;
        } while (InterlockedCompareExchangePointer(reinterpret_cast<PVOID*>(&head), newHead, oldHead) != oldHead);

        result = oldHead->data;
        delete oldHead;
        return true;
    }

    // Check if stack is empty
    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    ConcurrentStack<int> stack;

    // Pushing values
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // Popping values
    int value;
    while (stack.pop(value)) {
        std::cout << "Popped: " << value << std::endl;
    }

    return 0;
}
