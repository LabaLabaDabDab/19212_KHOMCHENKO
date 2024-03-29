#ifndef UNTITLED7_HASHTABLE_H
#define UNTITLED7_HASHTABLE_H
#include <iostream>
#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
    friend bool operator == (const Value& a, const Value& b);
    friend bool operator != (const Value& a, const Value& b);
};


class HashTable {
private:
    struct Node {
        Node *next;
        Value val;
        Key key;
        Node(const Value val, const Key key, Node * next = nullptr) : val(val), key(key) {
            this->next = next;
        }
    };
    const int DEFAULT_TABLE_SIZE = 128;
    Value def = {0, 0};
    constexpr static float kThreshold = 0.75f;
    size_t maxSize;
    size_t tableSize;
    size_t size;
    HashTable::Node **array;
    void resize();
    int hashFunction(const Key &k) const;
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable &b);
    void swap(HashTable &b);
    HashTable &operator=(const HashTable &b);
    void clear();
    bool erase(const Key &k);
    bool insert(const Key &k, const Value &v);
    bool contains(const Key &k) const;
    Value &operator[](const Key &k);
    Value &at(const Key &k);
    const Value &at(const Key &k) const;
    size_t get_size() const;
    bool empty() const;
    friend bool operator==(const HashTable &a, const HashTable &b);
    friend bool operator!=(const HashTable &a, const HashTable &b);
};



#endif //UNTITLED7_HASHTABLE_H
