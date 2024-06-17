#include <iostream>
using namespace std;

typedef int ElementType;

typedef struct tagCircularQueue {
    ElementType* nodes;   // ť�� ������ ���� �迭
    int producer;         // �����͸� �߰��� �ε���
    int consumer;         // �����͸� ������ �ε���
    int capacity;         // �迭�� ũ��
} CircularQueue;

// ���� ť �ʱ�ȭ �Լ�
void CQ_init(CircularQueue** q, int capacity) {
    if (!q) return;
    if (capacity <= 0) return;

    *q = (CircularQueue*)malloc(sizeof(CircularQueue));
    (*q)->nodes = (ElementType*)malloc(sizeof(ElementType) * (capacity + 1));  // �߰� ���� Ȯ��
    (*q)->producer = 0;
    (*q)->consumer = 0;
    (*q)->capacity = capacity;
}

// ���� ť ���� �Լ�
void CQ_deinit(CircularQueue* q) {
    if (!q) return;

    free(q->nodes);

    q->producer = 0;
    q->consumer = 0;
    q->capacity = 0;

    free(q);
}

// ���� ť�� ���� á���� Ȯ���ϴ� �Լ�
bool CQ_isFull(const CircularQueue* q) {
    if (!q) return false;

    if (q->consumer <= q->producer)
        return (q->producer - q->consumer == q->capacity);
    return q->producer + 1 == q->consumer;
}

// ���� ť�� ����ִ��� Ȯ���ϴ� �Լ�
bool CQ_isEmpty(const CircularQueue* q) {
    if (!q) return true;

    return q->producer == q->consumer;
}

// ���� ť�� ũ�⸦ ��ȯ�ϴ� �Լ�
int CQ_size(const CircularQueue* q) {
    if (!q) return 0;
    if (q->consumer <= q->producer) return q->producer - q->consumer;
    return (q->capacity + 1 - q->consumer + q->producer);
}

// ���� ť�� ��� ��Ҹ� ����ϴ� �Լ�
void CQ_print_all(const CircularQueue* q) {
    if (!q) return;

    int sz = CQ_size(q);
    for (int i = 0; i < sz; i++) {
        std::cout << q->nodes[(q->consumer + i) % (q->capacity + 1)] << " -> ";
    }
    std::cout << "null, �߰�: " << q->producer << ", ����: " << q->consumer << ", ������ = " << sz << std::endl;
}

// ���� ť�� ��Ҹ� �߰��ϴ� �Լ�
bool CQ_enqueue(CircularQueue* q, ElementType data) {
    if (!q) return false;

    std::cout << "������ " << data << " ... ";
    if (CQ_isFull(q)) {
        std::cout << "�����÷� ... ���� ��� ��" << std::endl;
        return false;
    }

    q->nodes[q->producer % (q->capacity + 1)] = data;
    ++q->producer %= (q->capacity + 1);
    CQ_print_all(q);
    return true;
}

// ���� ť���� ��Ҹ� �����ϴ� �Լ�
bool CQ_dequeue(CircularQueue* q, ElementType* data) {
    if (!q) return false;

    std::cout << "������      ...";
    if (CQ_isEmpty(q)) {
        std::cout << " ��� �÷ο� ... ���� ��� ��" << std::endl;
        return false;
    }

    *data = q->nodes[q->consumer % (q->capacity + 1)];
    ++q->consumer %= (q->capacity + 1);
    std::cout << " ���ŵ� " << *data << std::endl;
    return true;
}

// ���� �Լ�
int main() {
    CircularQueue* q = NULL;
    ElementType data;

    CQ_init(&q, 10);

    CQ_enqueue(q, 'a');
    CQ_enqueue(q, 'b');
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);  // "queue underflow" �߻�
    CQ_enqueue(q, 'c');
    CQ_enqueue(q, 'd');
    CQ_enqueue(q, 'e');
    CQ_enqueue(q, 'f');
    CQ_enqueue(q, 'g');
    CQ_enqueue(q, 'h');
    CQ_enqueue(q, 'i');
    CQ_enqueue(q, 'j');
    CQ_enqueue(q, 'k');
    CQ_enqueue(q, 'l');
    CQ_enqueue(q, 'm'); // "queue overflow" �߻�
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);
    CQ_enqueue(q, 'n');

    CQ_deinit(q);

    return 0;
}
