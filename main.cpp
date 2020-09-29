#include <iostream>
#include <string>
#include <cmath>
#include <search.h>
#include <cassert>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Eq;

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;

    friend bool operator == (const Value& a, const Value& b){
        return  a.age == b.age && a.weight == b.weight;
    }
    friend bool operator != (const Value& a, const Value& b){
        return  !(a == b);
    }
    friend bool operator < (const Value& a, const Value& b) {
        if (a.age != b.age) return a.age < b.age;
        if (a.weight != b.weight) return a.weight < b.weight;
        return false;
    }
    friend bool operator <= (const Value& a, const Value& b) {
        if (a.age != b.age) return a.age < b.age;
        if (a.weight != b.weight) return a.weight < b.weight;
        return true;
    }
};

struct Node{
    Node *next;
    Value val;
    Key key;
};

class HashTable {
    Value def;
    size_t size_;
    Node **array;
public:
    HashTable() {
        def = {0,0};
        size_ = 0;
        array = nullptr;
    }

    ~HashTable(){
        for (int i = 0; i < size_; ++i) {
            if (array[i])
                delete array[i];
        }
        delete[] array;
    }

    HashTable(const HashTable& b){
        def = {0,0};
        size_ = b.size_;
        array = new Node*[size_];
        for (int i = 0; i < size_; i++) {
            array[i] = nullptr;
        }
        Node* current;
        for (int j = 0; j < size_; ++j) {
            current = b.array[j];
            while (current != nullptr) {
                insert(current->key, current->val);
                current = current->next;
            }
        }
    }
    void swap(HashTable& b){
        std::swap(size_, b.size_);
        std::swap(array, b.array);
    }

    HashTable& operator=(const HashTable& b){
        if (&b != this){
            if (size_ != b.size_){
                delete [] array;
                size_ = b.size_;
                array = new Node*[size_];
            }
            for (int i = 0; i < size_; i++) {
                array[i] = b.array[i];
            }
        }
        return *this;
    }

    void clear(){
        for (int i = 0; i < size_; ++i) {
            while (array[i] != nullptr){
                Node *current = array[i]->next;
                delete array[i];
                array[i] = current;
            }
            array[i] = nullptr;
        }
        delete[] array;
        size_ = 0;
    }

    bool erase(const Key& k){
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
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    bool insert(const Key& k, const Value& v){
        int hash = hashFunction(k);
        if (hash >= size_){
            int sizeOld = size_;
            size_ = hash + 1;
            Node **tmp = new Node*[size_];
            for (int i = 0; i < sizeOld; ++i) {
                tmp[i] = array[i];
            }
            for (int j = sizeOld; j < size_; ++j) {
                tmp[j] = nullptr;
            }
            delete[] array;
            array = tmp;
            array[hash] = new Node;
            array[hash]->next = nullptr;
            array[hash]->val = v;
            array[hash]->key = k;
        }
        else{
            if (array[hash] == nullptr) {
                array[hash] = new Node;
                array[hash]->next = nullptr;
                array[hash]->val = v;
                array[hash]->key = k;
            }
            else {
                Node *prev = nullptr;
                Node *current = array[hash];
                while (current != nullptr) {
                    if (current->key == k) {
                        return false;
                    }
                    if (v < current->val) {
                        break;
                    }
                    if (current->next != nullptr) {
                        if (v <= current->val && current->next->val < v) {
                            if (k == current->next->key) return false;
                            prev = current;
                            current = current->next;
                            break;
                        }
                    }
                    prev = current;
                    current = current->next;
                }
                if (prev == nullptr) {
                    array[hash] = new Node;
                    array[hash]->next = current;
                    array[hash]->key = k;
                    array[hash]->val = v;
                }
                else {
                    prev->next = new Node;
                    prev->next->next = current;
                    prev->next->key = k;
                    prev->next->val = v;
                }
            }
        }
        return true;
    }

    bool contains(const Key& k) const{
        int hash = hashFunction(k);
        Node *current = array[hash];
        while(current != nullptr){
            if (current->key == k)
                return true;
            current = current->next;
        }
        return false;
    }

    Value& operator[](const Key& k){
        int hash = hashFunction(k);
        if (hash >= size_ || array[hash] == nullptr) {
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

    Value& at(const Key& k){
        int hash = hashFunction(k);
        if (hash >= size_ || array[hash] == nullptr)
            throw std::invalid_argument("There is no such key");
        Node *current = array[hash];
        while (current != nullptr){
            if (current->key == k)
                return current->val;
            current = current->next;
        }
        throw std::invalid_argument("There is no such key");
    }

    const Value& at(const Key& k) const{
        int hash = hashFunction(k);
        if (hash >= size_ || array[hash] == nullptr)
            throw std::invalid_argument("There is no such key");
        Node *current = array[hash];
        while (current != nullptr){
            if (current->key == k)
                return current->val;
            current = current->next;
        }
        throw std::invalid_argument("There is no such key");
    }

    size_t size() const{
        return size_;
    }

    bool empty() const{
        return size_ == 0;
    }

    friend bool operator == (const HashTable& a, const HashTable& b){
        if(a.size_ != b.size_)
            return false;
        for (int i = 0; i < a.size_; ++i) {
            Node *current_a = a.array[i];
            Node *current_b = b.array[i];
            while (current_a != nullptr && current_b != nullptr){
                if ((current_a->val != current_b->val) || (current_a->key != current_b->key)) {
                    return false;
                }
                current_a = current_a->next;
                current_b = current_b->next;
            }
            if (current_a != nullptr || current_b != nullptr)
                return false;
        }
        return true;
    }

    friend bool operator != (const HashTable& a, const HashTable& b) {
        return !(a == b);
    }

    int hashFunction(const Key &k) const{
        int result = 0;
        for (auto c : k){
            result += c;
        }
        result %= 97;
        return  result;
    }

    void print_ht() {
        std::cout << "HashTable Data" << std::endl;
        for (int i = 0; i < size_; i++) {
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
};

namespace {
    class HashTableTest : public testing::Test {
    };
}

TEST_F(HashTableTest, test1) {
    HashTable a;
    a.insert("Key", {3, 2});
    a.insert("PPP9", {4, 5});
    a.insert("PPQ8", {6, 7});
    HashTable b;
    b.insert("Key", {3, 2});
    b.insert("PPQ8", {6, 7});
    b.insert("PPP9", {4, 5});
    ASSERT_EQ(true, a == b);
}

TEST_F(HashTableTest, test2) {
    HashTable a;
    a.insert("Key", {3, 2});
    a.insert("PPP9", {6, 5});
    a.insert("PPQ8", {6, 7});
    HashTable b;
    b.insert("KIy", {3, 2});
    b.insert("PPP9", {4, 9});
    b.insert("PPQ8", {6, 7});
    ASSERT_EQ(true, a != b);
}

TEST_F(HashTableTest, test3) {
    HashTable a;
    a.insert("UYEIE", {3, 0});
    a.insert("OFOPEWK", {6, 899});
    a.insert("W{ED{W", {9, 7});
    HashTable b;
    b.insert("NFJKN:", {56, 2});
    b.insert("NJNJKNL", {4, 9});
    b.insert("PPQ8", {6, 6});
    a.swap(b);
    ASSERT_EQ(true, a.contains("PPQ8"));
}

TEST_F(HashTableTest, test4) {
    HashTable a;
    a.insert("UYEIE", {3, 0});
    a.insert("OFOPEWK", {6, 899});
    a.insert("W{ED{W", {9, 7});
    a.clear();
    ASSERT_EQ(true, a.empty());
}

TEST_F(HashTableTest, test5) {
    HashTable a;
    ASSERT_EQ(true, a.size() == 0);
}

int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    return 0;
}
