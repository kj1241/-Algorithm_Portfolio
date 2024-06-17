/*
단일 링크드리스트(ver.1 2015.11.08) mr.K
*/
#include <iostream>
using namespace std;

//template <typename T> 일 딴 보류 .... 템플릿 쓰고 싶은데...
/*
정의
*/
typedef struct tag_node {
    int data;
    struct tag_node* next;
} Node, * pNode;

typedef struct {
    pNode head;
    pNode tail;
} SLL, * pSLL;

/*
프로그래머 코드, 시스템 코드
*/


// 에러 메세지 출력 사실 winapi로 메세지 박스 추후 구현
void Error_print() {
    cout << "error" << endl;
}

// 노드 창조
Node* create_node(int data) {
    Node* newNode = new Node;
    if (newNode == NULL) {
        Error_print();
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 동적할당 해제
void node_free(Node* node) {
    if (node == NULL) return;
    delete node;
}

// 주어진 데이터로 노드갯수 찾기
int find_data(const SLL* lst, int data_fine) {
    if (lst == NULL) return 0;

    int count = 0;
    Node* temp = lst->head;

    while (temp != NULL) {
        if (temp->data == data_fine) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

// 주어진 데이터로 노드 찾기
Node* Such_Node(const SLL* lst, int data_fine) {
    if (lst == NULL) return NULL;

    Node* temp = lst->head;

    while (temp != NULL) {
        if (temp->data == data_fine) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// 주어진 데이터의 이전 노드를 찾기
Node* find_Prv_Node(const SLL* lst, int data) {
    if (lst == NULL || lst->head == NULL) return NULL;

    Node* temp = lst->head;
    Node* prev = NULL;

    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    return prev;
}

// 해드가 널값일때 새로운 노드만들기
void New_node(SLL* lst, int data) {
    if (lst == NULL) return;

    Node* temp = create_node(data);
    if (lst->head == NULL) {
        lst->head = temp;
        lst->tail = temp;
    }
}

/*
유저 코드
*/

// 삽입(단일리스트 , 삽입전 데이터위치, 데이터)
void insert_data(SLL* lst, int data_fine, int data) {
    if (lst == NULL) return;

    Node* p = create_node(data);
    if (lst->head == NULL) {
        lst->head = p;
        lst->tail = p;
        return;
    }

    Node* temp = Such_Node(lst, data_fine);

    if (temp == NULL) {
        Error_print();
        return;
    }

    if (lst->tail == temp) {
        temp->next = p;
        lst->tail = p;
    }
    else {
        p->next = temp->next;
        temp->next = p;
    }
}

// 삭제(단일리스트, 삭제데이터)
void delete_data(SLL* lst, int data) {
    if (lst == NULL || lst->head == NULL) return;

    Node* temp = Such_Node(lst, data);
    if (temp == NULL) {
        Error_print();
        return;
    }

    Node* prev = find_Prv_Node(lst, data);

    if (lst->head == temp) {
        lst->head = temp->next;
        if (lst->head == NULL) {
            lst->tail = NULL;
        }
    }
    else if (lst->tail == temp) {
        lst->tail = prev;
        if (prev != NULL) {
            prev->next = NULL;
        }
    }
    else if (prev != NULL) {
        prev->next = temp->next;
    }

    node_free(temp);
}

// 단일 링크드리스트에서 데이터가 몇번째 위치했는가
int data_number(const SLL* lst, int data) {
    if (lst == NULL) return -1;

    int position = 0;
    Node* temp = lst->head;

    while (temp != NULL) {
        if (temp->data == data) {
            return position;
        }
        position++;
        temp = temp->next;
    }
    return -1;
}

// 데이터 갯수 찾기
int finding_data(const SLL* lst, int data) {
    if (lst == NULL) return 0;

    return find_data(lst, data);
}

int main() {
    // 리스트 초기화
    SLL lst;
    lst.head = NULL;
    lst.tail = NULL;

    // 테스트 코드
    insert_data(&lst, 0, 1);
    insert_data(&lst, 1, 2);
    insert_data(&lst, 2, 3);
    insert_data(&lst, 3, 4);
    insert_data(&lst, 4, 5);
    insert_data(&lst, 5, 6);
    insert_data(&lst, 6, 7);
    insert_data(&lst, 7, 8);
    insert_data(&lst, 8, 9);

    insert_data(&lst, 3, 10);
    insert_data(&lst, 5, 3);

    delete_data(&lst, 8);

    cout << "데이터 3의 위치: " << data_number(&lst, 3) << endl;
    cout << "데이터 5가 나타나는 횟수: " << finding_data(&lst, 5) << endl;

    return 0;
}
