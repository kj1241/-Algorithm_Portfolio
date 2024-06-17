#include <iostream>

using namespace std;

typedef int ElementType;

class Node {
public:
    ElementType Data;  // 데이터
    Node* PrevNode;    // 이전 노드
    Node* NextNode;    // 다음 노드

    Node(ElementType NewData) : Data(NewData), PrevNode(nullptr), NextNode(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* Head;  // 헤드 노드

    DoublyLinkedList() : Head(nullptr) {}

    ~DoublyLinkedList() {
        while (Head != nullptr) {
            Node* temp = Head;
            Head = Head->NextNode;
            delete temp;
        }
    }

    // 노드 추가
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

    // 노드 삽입
    void InsertAfter(Node* Current, Node* NewNode) {
        NewNode->NextNode = Current->NextNode;
        NewNode->PrevNode = Current;

        if (Current->NextNode != nullptr) {
            Current->NextNode->PrevNode = NewNode;
        }
        Current->NextNode = NewNode;
    }

    // 노드 제거
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

    // 특정 위치의 노드 가져오기
    Node* GetNodeAt(int Location) {
        Node* Current = Head;
        while (Current != nullptr && (--Location) >= 0) {
            Current = Current->NextNode;
        }
        return Current;
    }

    // 노드 수 세기
    int GetNodeCount() {
        int Count = 0;
        Node* Current = Head;
        while (Current != nullptr) {
            Current = Current->NextNode;
            Count++;
        }
        return Count;
    }

    // 노드 출력
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
    DoublyLinkedList List;  // 리스트 생성
    Node* NewNode = nullptr;
    Node* Current = nullptr;

    // 노드 5개 추가
    for (i = 0; i < 5; i++) {
        NewNode = new Node(i);
        List.AppendNode(NewNode);
    }

    // 리스트 출력
    Count = List.GetNodeCount();
    for (i = 0; i < Count; i++) {
        Current = List.GetNodeAt(i);
        cout << "List[" << i << "] : " << Current->Data << endl;
    }

    // 리스트의 세 번째 칸 뒤에 노드 삽입
    cout << "\nInserting 3000 After [2]...\n\n";

    Current = List.GetNodeAt(2);
    NewNode = new Node(3000);
    List.InsertAfter(Current, NewNode);

    // 리스트 출력
    Count = List.GetNodeCount();
    for (i = 0; i < Count; i++) {
        Current = List.GetNodeAt(i);
        cout << "List[" << i << "] : " << Current->Data << endl;
    }

    // 모든 노드를 메모리에서 제거
    cout << "\nDestroying List...\n";

    while (List.Head != nullptr) {
        Current = List.Head;
        List.RemoveNode(Current);
    }

    return 0;
}
