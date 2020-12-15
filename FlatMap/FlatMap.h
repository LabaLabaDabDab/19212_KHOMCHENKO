#ifndef UNTITLED7_HASHTABLE_H
#define UNTITLED7_HASHTABLE_H
#include <string>
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

typedef std::string Key;

struct  Value {
    unsigned age;
    unsigned weight;
    friend bool operator == (const Value& a, const Value& b);
    friend bool operator != (const Value& a, const Value& b);
};

class FlatMap {
private:
    size_t len;
    size_t len_now;
    Value *array;
    Key *keys;

    size_t bin_search(const Key k) const;

    int bin_search_er(const Key k) const;

    void set(long long i, const Key &k, const Value &v);

    void resize();
public:
    FlatMap();

    ~FlatMap();

    FlatMap(const FlatMap &b);

    void swap(FlatMap &b);

    FlatMap &operator=(const FlatMap &b);

    void clear();

    void print();

    bool erase(const Key &k);

    bool insert(const Key &k, const Value &v);

    bool contains(const Key &k) const;

    Value &operator[](const Key &k);

    Value &at(const Key &k);

    const Value &at(const Key &k) const;

    size_t get_size() const;

    bool empty() const;

    friend bool operator == (const FlatMap &a, const FlatMap &b);

    friend bool operator != (const FlatMap &a, const FlatMap &b);
};

#endif //UNTITLED7_HASHTABLE_H
