/*
���� ��ũ�帮��Ʈ(ver.1 2015.11.08) mr.K
*/
#include <iostream>
using namespace std;

//template <typename T> �� �� ���� .... ���ø� ���� ������...
/*
����
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
���α׷��� �ڵ�, �ý��� �ڵ�
*/


// ���� �޼��� ��� ��� winapi�� �޼��� �ڽ� ���� ����
void Error_print() {
    cout << "error" << endl;
}

// ��� â��
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

// �����Ҵ� ����
void node_free(Node* node) {
    if (node == NULL) return;
    delete node;
}

// �־��� �����ͷ� ��尹�� ã��
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

// �־��� �����ͷ� ��� ã��
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

// �־��� �������� ���� ��带 ã��
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

// �ص尡 �ΰ��϶� ���ο� ��常���
void New_node(SLL* lst, int data) {
    if (lst == NULL) return;

    Node* temp = create_node(data);
    if (lst->head == NULL) {
        lst->head = temp;
        lst->tail = temp;
    }
}

/*
���� �ڵ�
*/

// ����(���ϸ���Ʈ , ������ ��������ġ, ������)
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

// ����(���ϸ���Ʈ, ����������)
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

// ���� ��ũ�帮��Ʈ���� �����Ͱ� ���° ��ġ�ߴ°�
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

// ������ ���� ã��
int finding_data(const SLL* lst, int data) {
    if (lst == NULL) return 0;

    return find_data(lst, data);
}

int main() {
    // ����Ʈ �ʱ�ȭ
    SLL lst;
    lst.head = NULL;
    lst.tail = NULL;

    // �׽�Ʈ �ڵ�
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

    cout << "������ 3�� ��ġ: " << data_number(&lst, 3) << endl;
    cout << "������ 5�� ��Ÿ���� Ƚ��: " << finding_data(&lst, 5) << endl;

    return 0;
}
