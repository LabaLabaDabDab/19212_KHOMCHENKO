#ifndef UNTITLED7_HASHTABLE_H
#define UNTITLED7_HASHTABLE_H
#include <iostream>
#include <string>
#include <cmath>
#include <search.h>
#include <cassert>
typedef std::string Key;

const int DEFAULT_TABLE_SIZE = 128;

struct Value {
    unsigned age;
    unsigned weight;
    friend bool operator == (const Value& a, const Value& b);
    friend bool operator != (const Value& a, const Value& b);
};

class HashTable {
private:
    struct Node{
        Node *next;
        Value val;
        Key key;
    };
    Value def = {0,0};
    float threshold;
    int maxSize;
    int tableSize;
    int size;
    Node **array;
    void resize();
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& b);
    void swap(HashTable& b);
    HashTable& operator=(const HashTable& b);
    void clear();
    bool erase(const Key& k);
    bool insert(const Key& k, const Value& v);
    bool contains(const Key& k) const;
    Value& operator[](const Key& k);
    Value& at(const Key& k);
    const Value& at(const Key& k) const;
    size_t get_size() const;
    bool empty() const;
    friend bool operator == (const HashTable& a, const HashTable& b);
    friend bool operator != (const HashTable& a, const HashTable& b);
    int hashFunction(const Key &k) const;
};

#endif //UNTITLED7_HASHTABLE_H
