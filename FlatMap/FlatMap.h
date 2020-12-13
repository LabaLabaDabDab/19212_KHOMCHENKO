#ifndef UNTITLED7_HASHTABLE_H
#define UNTITLED7_HASHTABLE_H
#include <string>
#include <stdexcept>
#include <iostream>

namespace Fmap{
    typedef std::string Key;
    const size_t len_kef = 2;
    class Value {
    public:
        unsigned age;
        unsigned weight;
        Value(int p = 0) {
            age = p;
            weight = 11;
        }
        friend bool operator==(const Value & a, const Value & b){
            if(a.age == b.age && a.weight == b.weight){
                return true;
            }
            return false;
        }
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

        friend bool operator==(const FlatMap & a, const FlatMap & b){
            if(a.len_now == b.len_now){
                for (size_t i = 0; i < a.len_now; ++i){
                    if(!((a.array[i] == b.array[i]) && (a.keys[i] == b.keys[i]))){
                        return false;
                    }
                }
            } else{
                return false;
            }
            return true;
        }

        friend bool operator!=(const FlatMap & a, const FlatMap & b){
            return !(a == b);
        }
    };
}
#endif //UNTITLED7_HASHTABLE_H
