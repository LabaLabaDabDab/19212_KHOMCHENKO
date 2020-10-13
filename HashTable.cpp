#include "HashTable.h"

bool operator == (const Value& a, const Value& b){
    return  a.age == b.age && a.weight == b.weight;
}
bool operator != (const Value& a, const Value& b){
    return  !(a == b);
}
bool operator < (const Value& a, const Value& b) {
    if (a.age != b.age) return a.age < b.age;
    if (a.weight != b.weight) return a.weight < b.weight;
    return false;
}
bool operator <= (const Value& a, const Value& b) {
    if (a.age != b.age) return a.age < b.age;
    if (a.weight != b.weight) return a.weight < b.weight;
    return true;
}

HashTable::HashTable() {
    threshold = 0.75f;
    tableSize = DEFAULT_TABLE_SIZE;
    maxSize = (int)(tableSize * threshold);
    size = 0;
    array = new Node * [tableSize];
    for (int i = 0; i < tableSize; ++i) {
        array[i] = nullptr;
    }
}

HashTable::~HashTable(){
    clear();
    delete[] array;
}

HashTable::HashTable(const HashTable& b){
    threshold = b.threshold;
    maxSize = b.maxSize;
    tableSize = b.tableSize;
    size = 0;
    array = new Node*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        array[i] = nullptr;
    }
    Node* current;
    for (int j = 0; j < tableSize; ++j) {
        current = b.array[j];
        while (current != nullptr) {
            insert(current->key, current->val);
            current = current->next;
        }
    }
}

void HashTable::swap(HashTable& b){
    std::swap(tableSize, b.tableSize);
    std::swap(threshold, b.threshold);
    std::swap(maxSize, b.maxSize);
    std::swap(size, b.size);
    std::swap(array, b.array);
}

HashTable& HashTable::operator=(const HashTable& b){
    if (&b != this){
        threshold = b.threshold;
        maxSize = b.maxSize;
        tableSize = b.tableSize;
        size = 0;
        array = new Node*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            array[i] = nullptr;
        }
        Node* current;
        for (int j = 0; j < tableSize; ++j) {
            current = b.array[j];
            while (current != nullptr) {
                insert(current->key, current->val);
                current = current->next;
            }
        }
    }
    return *this;
}

void HashTable::clear(){
    for (int i = 0; i < tableSize; ++i) {
        while (array[i] != nullptr){
            Node *current = array[i]->next;
            delete array[i];
            array[i] = current;
        }
        array[i] = nullptr;
    }
    delete[] array;
    tableSize = DEFAULT_TABLE_SIZE;
    maxSize = (int)(tableSize * threshold);
    size = 0;
    array = new Node * [tableSize];
    for (int i = 0; i < tableSize; ++i) {
        array[i] = nullptr;
    }
}

bool HashTable::erase(const Key& k){
    int hash = hashFunction(k);
    Node* prev = nullptr;
    Node *current = array[hash];
    while (current != nullptr){
        if (current->key == k){
            if (prev == nullptr){
                array[hash] = current->next;
            }
            else
                prev->next = current->next;
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

bool HashTable::insert(const Key& k, const Value& v) {
    int hash = hashFunction(k);
    if (array[hash] == nullptr) {
        array[hash] = new Node;
        array[hash]->next = nullptr;
        array[hash]->val = v;
        array[hash]->key = k;
        size++;
    } else {
        Node *prev = nullptr;
        Node *current = array[hash];
        while (current != nullptr) {
            if (current->key == k) {
                return false;
            }
            prev = current;
            current = current->next;
        }
        prev->next = new Node;
        prev->next->next = current;
        prev->next->key = k;
        prev->next->val = v;
        size++;
    }
    if (size >= maxSize){
        resize();
    }
    return true;
}

bool HashTable::contains(const Key& k) const{
    int hash = hashFunction(k);
    Node *current = array[hash];
    while(current != nullptr){
        if (current->key == k)
            return true;
        current = current->next;
    }
    return false;
}

Value& HashTable::operator[](const Key& k){
    int hash = hashFunction(k);
    if (array[hash] == nullptr) {
        insert(k, def);
        return def;
    }
    Node *current = array[hash];
    while (current != nullptr){
        if (current->key == k)
            return current->val;
        current = current->next;
    }
    insert(k, def);
    return def;
}

Value& HashTable::at(const Key& k){
    int hash = hashFunction(k);
    if (array[hash] == nullptr)
        throw std::invalid_argument("There is no such key");
    Node *current = array[hash];
    while (current != nullptr){
        if (current->key == k)
            return current->val;
        current = current->next;
    }
    throw std::invalid_argument("There is no such key");
}

const Value& HashTable::at(const Key& k) const{
    int hash = hashFunction(k);
    if (array[hash] == nullptr)
        throw std::invalid_argument("There is no such key");
    Node *current = array[hash];
    while (current != nullptr){
        if (current->key == k)
            return current->val;
        current = current->next;
    }
    throw std::invalid_argument("There is no such key");
}

size_t HashTable::get_size() const{
    return size;
}

bool HashTable::empty() const{
    return size == 0;
}

bool operator == (const HashTable& a, const HashTable& b){
    if(a.size != b.size)
        return false;
    for (int i = 0; i < a.tableSize; ++i) {
        HashTable::Node *current_a = a.array[i];
        while (current_a != nullptr){
            bool found = false;
            HashTable::Node *current_b = b.array[i];
            while (current_b != nullptr){
                if ((current_a->val == current_b->val) && (current_a->key == current_b->key)) {
                    found = true;
                    break;
                }
                current_b = current_b->next;
            }
            if (!found)
                return false;
            current_a = current_a->next;
        }
    }
    return true;
}

bool operator != (const HashTable& a, const HashTable& b) {
    return !(a == b);
}

int HashTable::hashFunction(const Key &k) const{
    int result = 0; //unsigned
    for (auto c : k){
        result += c;
    }
    result %= tableSize;
    return  result;
}

void HashTable::print_ht() {
    std::cout << "HashTable Data" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << ": {";
        if (array[i] == nullptr) std::cout << "nullptr";
        else {
            int j = 0;
            Node *cur = array[i];
            while(cur != nullptr) {
                std::cout << j << ":(" << cur->val.age << " " << cur->val.weight << "), ";
                cur = cur->next;
                j++;
            }
        }
        std::cout << "}";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void HashTable::resize() {
    int oldTableSize = tableSize;
    tableSize *= 2;
    maxSize = (int) (tableSize * threshold);
    Node **oldTable = array;
    array = new Node*[tableSize];
    for (int i = 0; i < tableSize; i++)
        array[i] = nullptr;
    size = 0;
    for (int hash = 0; hash < oldTableSize; hash++)
        if (oldTable[hash] != nullptr) {
            Node *oldEntry;
            Node *entry = oldTable[hash];
            while (entry != nullptr) {
                insert(entry->key, entry->val);
                oldEntry = entry;
                entry = entry->next;
                delete oldEntry;
            }
        }
    delete[] oldTable;
}
