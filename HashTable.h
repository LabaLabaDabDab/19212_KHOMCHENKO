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
    friend bool operator < (const Value& a, const Value& b);
    friend bool operator <= (const Value& a, const Value& b);
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
    void print_ht();
    class Iterator{
    private:
        Node * ptr;
        int idx;
        HashTable * ht;
    public:
        Iterator(Node * ptr_, int idx_, HashTable * ht_){
            ptr = ptr_;
            idx = idx_;
            ht = ht_;
        };
        Iterator& operator++(){
            if (ptr->next == nullptr){
                for (int i = idx + 1; i < ht->tableSize; ++i) {
                    if (ht->array[i] != nullptr){
                        idx = i;
                        ptr = ht->array[i];
                        break;
                    }
                }
            }
            else ptr = ptr->next;
            return *this;
        }
        operator std::pair<Key, Value> (){
            return std::make_pair(ptr->key, ptr->val);
        }
        bool operator !=(Iterator iter){
            return ptr != iter.ptr;
        }
        bool operator ==(Iterator iter){
            return ptr == iter.ptr;
        }
    };
    Iterator begin() {
        Node * ptr = nullptr;
        int idx = 0;
        for (int i = 0; i < tableSize; ++i) {
            if (array[i] != nullptr) {
                idx = i;
                ptr = array[i];
                break;
            }
        }
        Iterator iter(ptr, idx, this);
        return iter;
    }
    Iterator end() {
        Node * ptr = nullptr;
        int idx = 0;
        for (int i = tableSize - 1; i >= 0; --i) {
            if (array[i] != nullptr) {
                idx = i;
                ptr = array[i];
                break;
            }
        }
        while(ptr->next != nullptr)
            ptr = ptr->next;
        Iterator iter(ptr, idx, this);
        return iter;
    }
};

#endif //UNTITLED7_HASHTABLE_H
