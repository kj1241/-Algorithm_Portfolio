#include <iostream>

using namespace std;

typedef int ElementType;

class ArrayStack {
public:
    struct Node {
        ElementType Data;
    };

    ArrayStack(int Capacity) : Capacity(Capacity), Top(0) {
        Nodes = new Node[Capacity];
    }

    ~ArrayStack() {
        delete[] Nodes;
    }

    void Push(ElementType Data) {
        if (Top < Capacity) {
            Nodes[Top].Data = Data;
            Top++;
        }
        else {
            cout << "Stack overflow" << endl;
        }
    }

    ElementType Pop() {
        if (!IsEmpty()) {
            Top--;
            return Nodes[Top].Data;
        }
        else {
            cout << "Stack underflow" << endl;
            return -1; // Underflow condition
        }
    }

    ElementType TopElement() const {
        if (!IsEmpty()) {
            return Nodes[Top - 1].Data;
        }
        else {
            cout << "Stack is empty" << endl;
            return -1; // Empty stack condition
        }
    }

    int GetSize() const {
        return Top;
    }

    bool IsEmpty() const {
        return Top == 0;
    }

    int GetCapacity() const {
        return Capacity;
    }

private:
    Node* Nodes;
    int Capacity;
    int Top;
};

int main() {
    ArrayStack stack(10);

    stack.Push(3);
    stack.Push(37);
    stack.Push(11);
    stack.Push(12);

    cout << "Capacity: " << stack.GetCapacity() << ", Size: " << stack.GetSize() << ", Top: " << stack.TopElement() << "\n\n";

    for (int i = 0; i < 4; i++) {
        if (stack.IsEmpty())
            break;

        cout << "Popped: " << stack.Pop() << ", ";

        if (!stack.IsEmpty())
            cout << "Current Top: " << stack.TopElement() << endl;
        else
            cout << "Stack Is Empty." << endl;
    }

    return 0;
}
