#include <iostream>
#include <vector>

using KeyType = int;
using ValueType = int;

class Node {
public:
    KeyType Key;
    ValueType Value;

    Node() : Key(0), Value(0) {}
    Node(KeyType key, ValueType value) : Key(key), Value(value) {}
};

class HashTable {
public:
    HashTable(int tableSize);
    ~HashTable();

    void Set(KeyType key, ValueType value);
    ValueType Get(KeyType key) const;
    int Hash(KeyType key) const;

private:
    std::vector<Node> table;
    int tableSize;
};

HashTable::HashTable(int tableSize) : tableSize(tableSize), table(tableSize) {}

HashTable::~HashTable() {}

void HashTable::Set(KeyType key, ValueType value) {
    int address = Hash(key);
    table[address] = Node(key, value);
}

ValueType HashTable::Get(KeyType key) const {
    int address = Hash(key);
    return table[address].Value;
}

int HashTable::Hash(KeyType key) const {
    return key % tableSize;
}

int main() {
    HashTable ht(193);

    ht.Set(418, 32114);
    ht.Set(9, 514);
    ht.Set(27, 8917);
    ht.Set(1031, 286);

    std::cout << "Key: " << 418 << ", Value: " << ht.Get(418) << std::endl;
    std::cout << "Key: " << 9 << ", Value: " << ht.Get(9) << std::endl;
    std::cout << "Key: " << 27 << ", Value: " << ht.Get(27) << std::endl;
    std::cout << "Key: " << 1031 << ", Value: " << ht.Get(1031) << std::endl;

    return 0;
}
