#include <iostream>
using namespace std;

typedef int ElementType;

typedef struct tagCircularQueue {
    ElementType* nodes;   // 큐의 데이터 저장 배열
    int producer;         // 데이터를 추가할 인덱스
    int consumer;         // 데이터를 제거할 인덱스
    int capacity;         // 배열의 크기
} CircularQueue;

// 원형 큐 초기화 함수
void CQ_init(CircularQueue** q, int capacity) {
    if (!q) return;
    if (capacity <= 0) return;

    *q = (CircularQueue*)malloc(sizeof(CircularQueue));
    (*q)->nodes = (ElementType*)malloc(sizeof(ElementType) * (capacity + 1));  // 추가 공간 확보
    (*q)->producer = 0;
    (*q)->consumer = 0;
    (*q)->capacity = capacity;
}

// 원형 큐 해제 함수
void CQ_deinit(CircularQueue* q) {
    if (!q) return;

    free(q->nodes);

    q->producer = 0;
    q->consumer = 0;
    q->capacity = 0;

    free(q);
}

// 원형 큐가 가득 찼는지 확인하는 함수
bool CQ_isFull(const CircularQueue* q) {
    if (!q) return false;

    if (q->consumer <= q->producer)
        return (q->producer - q->consumer == q->capacity);
    return q->producer + 1 == q->consumer;
}

// 원형 큐가 비어있는지 확인하는 함수
bool CQ_isEmpty(const CircularQueue* q) {
    if (!q) return true;

    return q->producer == q->consumer;
}

// 원형 큐의 크기를 반환하는 함수
int CQ_size(const CircularQueue* q) {
    if (!q) return 0;
    if (q->consumer <= q->producer) return q->producer - q->consumer;
    return (q->capacity + 1 - q->consumer + q->producer);
}

// 원형 큐의 모든 요소를 출력하는 함수
void CQ_print_all(const CircularQueue* q) {
    if (!q) return;

    int sz = CQ_size(q);
    for (int i = 0; i < sz; i++) {
        std::cout << q->nodes[(q->consumer + i) % (q->capacity + 1)] << " -> ";
    }
    std::cout << "null, 추가: " << q->producer << ", 제거: " << q->consumer << ", 사이즈 = " << sz << std::endl;
}

// 원형 큐에 요소를 추가하는 함수
bool CQ_enqueue(CircularQueue* q, ElementType data) {
    if (!q) return false;

    std::cout << "삽입중 " << data << " ... ";
    if (CQ_isFull(q)) {
        std::cout << "오버플로 ... 삽입 취소 중" << std::endl;
        return false;
    }

    q->nodes[q->producer % (q->capacity + 1)] = data;
    ++q->producer %= (q->capacity + 1);
    CQ_print_all(q);
    return true;
}

// 원형 큐에서 요소를 제거하는 함수
bool CQ_dequeue(CircularQueue* q, ElementType* data) {
    if (!q) return false;

    std::cout << "제거중      ...";
    if (CQ_isEmpty(q)) {
        std::cout << " 언더 플로우 ... 제거 취소 중" << std::endl;
        return false;
    }

    *data = q->nodes[q->consumer % (q->capacity + 1)];
    ++q->consumer %= (q->capacity + 1);
    std::cout << " 제거됨 " << *data << std::endl;
    return true;
}

// 메인 함수
int main() {
    CircularQueue* q = NULL;
    ElementType data;

    CQ_init(&q, 10);

    CQ_enqueue(q, 'a');
    CQ_enqueue(q, 'b');
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);  // "queue underflow" 발생
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
    CQ_enqueue(q, 'm'); // "queue overflow" 발생
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);
    (void)CQ_dequeue(q, &data);
    CQ_enqueue(q, 'n');

    CQ_deinit(q);

    return 0;
}
