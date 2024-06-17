#include <iostream>

using namespace std;

typedef int ElementType;

class Node {
public:
    ElementType Data;  // ������
    Node* PrevNode;    // ���� ���
    Node* NextNode;    // ���� ���

    Node(ElementType NewData) : Data(NewData), PrevNode(nullptr), NextNode(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* Head;  // ��� ���

    DoublyLinkedList() : Head(nullptr) {}

    ~DoublyLinkedList() {
        while (Head != nullptr) {
            Node* temp = Head;
            Head = Head->NextNode;
            delete temp;
        }
    }

    // ��� �߰�
    void AppendNode(Node* NewNode) {
        if (Head == nullptr) {
            Head = NewNode;
        }
        else {
            Node* Tail = Head;
            while (Tail->NextNode != nullptr) {
                Tail = Tail->NextNode;
            }
            Tail->NextNode = NewNode;
            NewNode->PrevNode = Tail;
        }
    }

    // ��� ����
    void InsertAfter(Node* Current, Node* NewNode) {
        NewNode->NextNode = Current->NextNode;
        NewNode->PrevNode = Current;

        if (Current->NextNode != nullptr) {
            Current->NextNode->PrevNode = NewNode;
        }
        Current->NextNode = NewNode;
    }

    // ��� ����
    void RemoveNode(Node* Remove) {
        if (Head == Remove) {
            Head = Remove->NextNode;
            if (Head != nullptr) {
                Head->PrevNode = nullptr;
            }
        }
        else {
            if (Remove->PrevNode != nullptr) {
                Remove->PrevNode->NextNode = Remove->NextNode;
            }
            if (Remove->NextNode != nullptr) {
                Remove->NextNode->PrevNode = Remove->PrevNode;
            }
        }
        delete Remove;
    }

    // Ư�� ��ġ�� ��� ��������
    Node* GetNodeAt(int Location) {
        Node* Current = Head;
        while (Current != nullptr && (--Location) >= 0) {
            Current = Current->NextNode;
        }
        return Current;
    }

    // ��� �� ����
    int GetNodeCount() {
        int Count = 0;
        Node* Current = Head;
        while (Current != nullptr) {
            Current = Current->NextNode;
            Count++;
        }
        return Count;
    }

    // ��� ���
    void PrintNode(Node* _Node) {
        if (_Node->PrevNode == nullptr) {
            cout << "Prev: NULL";
        }
        else {
            cout << "Prev: " << _Node->PrevNode->Data;
        }

        cout << " Current: " << _Node->Data << " ";

        if (_Node->NextNode == nullptr) {
            cout << "Next: NULL" << endl;
        }
        else {
            cout << "Next: " << _Node->NextNode->Data << endl;
        }
    }
};

int main() {
    int i = 0;
    int Count = 0;
    DoublyLinkedList List;  // ����Ʈ ����
    Node* NewNode = nullptr;
    Node* Current = nullptr;

    // ��� 5�� �߰�
    for (i = 0; i < 5; i++) {
        NewNode = new Node(i);
        List.AppendNode(NewNode);
    }

    // ����Ʈ ���
    Count = List.GetNodeCount();
    for (i = 0; i < Count; i++) {
        Current = List.GetNodeAt(i);
        cout << "List[" << i << "] : " << Current->Data << endl;
    }

    // ����Ʈ�� �� ��° ĭ �ڿ� ��� ����
    cout << "\nInserting 3000 After [2]...\n\n";

    Current = List.GetNodeAt(2);
    NewNode = new Node(3000);
    List.InsertAfter(Current, NewNode);

    // ����Ʈ ���
    Count = List.GetNodeCount();
    for (i = 0; i < Count; i++) {
        Current = List.GetNodeAt(i);
        cout << "List[" << i << "] : " << Current->Data << endl;
    }

    // ��� ��带 �޸𸮿��� ����
    cout << "\nDestroying List...\n";

    while (List.Head != nullptr) {
        Current = List.Head;
        List.RemoveNode(Current);
    }

    return 0;
}
