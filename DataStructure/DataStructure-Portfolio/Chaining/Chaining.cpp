#include <iostream>
#include <vector>
#include <cstring>

using KeyType = std::string;
using ValueType = std::string;

class Node {
public:
    KeyType Key;
    ValueType Value;
    Node* Next;

    Node(KeyType key, ValueType value) : Key(key), Value(value), Next(nullptr) {}
};

class HashTable {
public:
    HashTable(int tableSize);
    ~HashTable();

    void Set(KeyType key, ValueType value);
    ValueType Get(KeyType key) const;
    int Hash(KeyType key) const;

private:
    std::vector<Node*> table;
    int tableSize;

    void DestroyNode(Node* node);
    void DestroyList(Node* list);
};

HashTable::HashTable(int tableSize) : tableSize(tableSize), table(tableSize, nullptr) {}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; i++) {
        DestroyList(table[i]);
    }
}

void HashTable::Set(KeyType key, ValueType value) {
    int address = Hash(key);
    Node* newNode = new Node(key, value);

    if (table[address] == nullptr) {
        table[address] = newNode;
    }
    else {
        newNode->Next = table[address];
        table[address] = newNode;
        std::cout << "Collision occurred: Key(" << key << "), Address(" << address << ")" << std::endl;
    }
}

ValueType HashTable::Get(KeyType key) const {
    int address = Hash(key);
    Node* list = table[address];

    while (list != nullptr) {
        if (list->Key == key) {
            return list->Value;
        }
        list = list->Next;
    }

    return "";
}

int HashTable::Hash(KeyType key) const {
    int hashValue = 0;
    for (char ch : key) {
        hashValue = (hashValue << 3) + ch;
    }
    return hashValue % tableSize;
}

void HashTable::DestroyNode(Node* node) {
    delete node;
}

void HashTable::DestroyList(Node* list) {
    while (list != nullptr) {
        Node* temp = list;
        list = list->Next;
        DestroyNode(temp);
    }
}

int main() {
    HashTable ht(12289);

    ht.Set("MSFT", "Microsoft Corporation");
    ht.Set("JAVA", "Sun Microsystems");
    ht.Set("REDH", "Red Hat Linux");
    ht.Set("APAC", "Apache Org");
    ht.Set("ZYMZZ", "Unisys Ops Check"); // APAC¿Í Ãæµ¹
    ht.Set("IBM", "IBM Ltd.");
    ht.Set("ORCL", "Oracle Corporation");
    ht.Set("CSCO", "Cisco Systems, Inc.");
    ht.Set("GOOG", "Google Inc.");
    ht.Set("YHOO", "Yahoo! Inc.");
    ht.Set("NOVL", "Novell, Inc.");

    std::cout << std::endl;
    std::cout << "Key: MSFT, Value: " << ht.Get("MSFT") << std::endl;
    std::cout << "Key: REDH, Value: " << ht.Get("REDH") << std::endl;
    std::cout << "Key: APAC, Value: " << ht.Get("APAC") << std::endl;
    std::cout << "Key: ZYMZZ, Value: " << ht.Get("ZYMZZ") << std::endl;
    std::cout << "Key: JAVA, Value: " << ht.Get("JAVA") << std::endl;
    std::cout << "Key: IBM, Value: " << ht.Get("IBM") << std::endl;
    std::cout << "Key: ORCL, Value: " << ht.Get("ORCL") << std::endl;
    std::cout << "Key: CSCO, Value: " << ht.Get("CSCO") << std::endl;
    std::cout << "Key: GOOG, Value: " << ht.Get("GOOG") << std::endl;
    std::cout << "Key: YHOO, Value: " << ht.Get("YHOO") << std::endl;
    std::cout << "Key: NOVL, Value: " << ht.Get("NOVL") << std::endl;

    return 0;
}
