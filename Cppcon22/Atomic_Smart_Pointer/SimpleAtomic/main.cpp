#include <iostream>
#include <atomic>

class AtomicInt {
private:
    std::atomic<int> value;

public:
    AtomicInt(int initialValue) : value(initialValue) {}

    // 원자적 읽기
    int load() const {
        return value.load(std::memory_order_seq_cst);
    }

    // 원자적 쓰기
    void store(int newValue) {
        value.store(newValue, std::memory_order_seq_cst);
    }

    // 원자적 비교 교환 (CAS)
    bool compare_exchange(int& expected, int desired) {
        return value.compare_exchange_strong(expected, desired, std::memory_order_seq_cst);
    }
};

int main() {
    AtomicInt atomicInt(0);

    int expected = 0;
    if (atomicInt.compare_exchange(expected, 1)) {
        std::cout << "CAS 성공: " << atomicInt.load() << std::endl;
    }
    else {
        std::cout << "CAS 실패, expected: " << expected << std::endl;
    }

    atomicInt.store(5);
    std::cout << "현재 값: " << atomicInt.load() << std::endl;

    return 0;
}
