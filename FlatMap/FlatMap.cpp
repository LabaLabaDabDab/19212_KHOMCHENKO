#include "FlatMap.h"

bool operator == (const Value & a, const Value & b) {
    if (a.age == b.age && a.weight == b.weight) {
        return true;
    }
    return false;
}

bool operator != (const Value& a, const Value& b){
    return  !(a == b);
}

bool operator != (const FlatMap &a, const FlatMap &b) {
    return !(a == b);
}

bool operator == (const FlatMap &a, const FlatMap &b) {
    if (a.len_now == b.len_now) {
        for (size_t i = 0; i < a.len_now; ++i) {
            if (!((a.array[i] == b.array[i]) && (a.keys[i] == b.keys[i]))) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

FlatMap::FlatMap(){
    len = 1;
    len_now = 0;
    array = new Value[len];
    keys = new Key[len];
}

FlatMap::~FlatMap(){
    delete[] array;
    delete[] keys;
}

FlatMap::FlatMap(const FlatMap& b){
    len = b.len;
    len_now = b.len_now;
    array = new Value[len];
    keys = new Key[len];
    std::copy(b.array, b.array + len_now, array);
    std::copy(b.keys, b.keys + len_now, keys);
}

void FlatMap::swap(FlatMap& b){
    std::swap(*this, b);
}

FlatMap& FlatMap::operator=(const FlatMap& b) {
    if (&b == this) {
        return *this;
    }
    len = b.len;
    len_now = b.len_now;
    delete[] array;
    delete[] keys;
    array = new Value[len];
    keys = new Key[len];
    std::copy(b.array, b.array + len_now, array);
    std::copy(b.keys, b.keys + len_now, keys);
    return *this;
}

void FlatMap::clear(){
    len_now = 0;
}

bool FlatMap::erase(const Key& k){
    int el = bin_search_er(k);
    if(-1 == el)
        return false;
    len_now--;
    std::copy(array + el + 1, array + len_now, array + el);
    std::copy(keys + el + 1, keys + len_now, keys + el);
    return true;
}

bool FlatMap::insert(const Key& k, const Value& v) {
    if(len_now == len){
        resize();
    }
    if(len_now == 0){
        set(0, k, v);
        len_now++;
        return true;
    }
    if(k > keys[len_now - 1]){
        set(len_now, k, v);
        len_now++;
        return true;
    }
    if(k == keys[0]){
        set(0, k, v);
        return true;
    }
    if(k == keys[len_now - 1]){
        set(len_now - 1, k, v);
        return true;
    }
    size_t el = bin_search(k);
    for(size_t i = len_now; i > el; i--){
        array[i] = array[i - 1];
        keys[i] = keys[i - 1];
    }
    set(el, k, v);
    len_now++;
    return true;
}

bool FlatMap::contains(const Key& k) const{
    if(-1 == bin_search_er(k)){
        return false;
    }
    return true;
}

Value& FlatMap::operator[](const Key& k){
    int el = bin_search_er(k);
    if(-1 != el){
        return array[el];
    }
    Value * v = new Value();
    insert(k, *v);
    return *v;
}

Value& FlatMap::at(const Key& k){
    if(len_now == 0){
        throw std::invalid_argument ("container is empty");
    }
    int el = bin_search_er(k);
    if(-1 == el){
        throw std::invalid_argument ("element not found");
    }
    return array[el];
}

const Value& FlatMap::at(const Key& k) const{
    if(len_now == 0){
        throw std::invalid_argument ("container is empty");
    }
    int el = bin_search_er(k);
    if(-1 == el){
        throw std::invalid_argument ("element not found");
    }
    return array[el];
}

size_t FlatMap::get_size() const{
    return len_now;
}

void FlatMap::set(long long i, const Key& k, const Value& v){
    array[i] = v;
    keys[i] = k;
}

bool FlatMap::empty() const{
    return len_now == 0;
}

size_t FlatMap::bin_search(const Key k) const{
    if(len_now == 0){
        return 0;
    }
    if(k == keys[0])
        return 0;
    if(k == keys[len_now - 1])
        return len_now - 1;
    size_t l = 0,r = len_now - 1;
    while(l < r){
        size_t tec = l + ((r - l) / 2);
        if(k == keys[tec]){
            return tec;
        }
        else if(k > keys[tec]){
            l = tec + 1;
        }
        else{
            r = tec;
        }
    }
    return l;
}

int FlatMap::bin_search_er(const Key k) const{
    size_t el = bin_search(k);
    if(keys[el] == k){
        return el;
    }
    return -1;
}

void FlatMap::print(){
    for (size_t i = 0; i < len_now; ++i){
        std::cout << i << " - " << keys[i] << " - " << array[i].age << std::endl;
    }
    std::cout << std::endl;
}

void FlatMap::resize() {
    size_t new_len = len * 2;
    Value * new_array = new Value[new_len];
    Key * keys2 = new Key[new_len];
    std::copy(array, array + len_now, new_array);
    std::copy(keys, keys + len_now, keys2);
    delete[] array;
    delete[] keys;
    array = new_array;
    keys = keys2;
    len = new_len;
}