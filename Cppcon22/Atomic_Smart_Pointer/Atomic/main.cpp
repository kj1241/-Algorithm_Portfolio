////GCC ����
//#include <iostream>
//
//class AtomicInt {
//private:
//    volatile int value;
//
//public:
//    AtomicInt(int initialValue) : value(initialValue) {}
//
//    // ������ �б�
//    int load() const {
//        return __sync_val_compare_and_swap(const_cast<int*>(&value), 0, 0);
//    }
//
//    // ������ ����
//    void store(int newValue) {
//        __sync_lock_test_and_set(&value, newValue);
//    }
//
//    // ������ �� ��ȯ (CAS)
//    bool compare_exchange(int& expected, int desired) {
//        int oldValue = __sync_val_compare_and_swap(&value, expected, desired);
//        if (oldValue == expected) {
//            return true;
//        }
//        else {
//            expected = oldValue;
//            return false;
//        }
//    }
//};
//
//int main() {
//    AtomicInt atomicInt(0);
//
//    int expected = 0;
//    if (atomicInt.compare_exchange(expected, 1)) {
//        std::cout << "CAS ����: " << atomicInt.load() << std::endl;
//    }
//    else {
//        std::cout << "CAS ����, expected: " << expected << std::endl;
//    }
//
//    atomicInt.store(5);
//    std::cout << "���� ��: " << atomicInt.load() << std::endl;
//
//    return 0;
//}


#include <iostream>
#include <windows.h>

class AtomicInt {
private:
    volatile LONG value;

public:
    AtomicInt(int initialValue) : value(initialValue) {}

    // ������ �б�
    int load() const {
        return InterlockedCompareExchange(const_cast<LONG*>(&value), 0, 0);
    }

    // ������ ����
    void store(int newValue) {
        InterlockedExchange(&value, newValue);
    }

    // ������ �� ��ȯ (CAS)
    bool compare_exchange(int& expected, int desired) {
        LONG expectedLong = expected;
        LONG oldValue = InterlockedCompareExchange(&value, desired, expectedLong);
        if (oldValue == expectedLong) {
            return true;
        }
        else {
            expected = oldValue;
            return false;
        }
    }
};

int main() {
    AtomicInt atomicInt(0);

    int expected = 0;
    if (atomicInt.compare_exchange(expected, 1)) {
        std::cout << "CAS ����: " << atomicInt.load() << std::endl;
    }
    else {
        std::cout << "CAS ����, expected: " << expected << std::endl;
    }

    atomicInt.store(5);
    std::cout << "���� ��: " << atomicInt.load() << std::endl;

    return 0;
}