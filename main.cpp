#include <gtest/gtest.h>
#include "HashTable.h"

int main() {
    HashTable a;
    a.insert("Key", {3, 2});
    a.insert("PPP9", {6, 5});
    a.insert("PPQ8", {6, 7});
    for (HashTable::Iterator elem = a.begin(); ; ++elem) {
        std::pair<Key, Value> pair = elem;
        std::cout << pair.first << " " << pair.second.weight << " " << pair.second.age << std::endl;
        if (elem == a.end()) break;
    }
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    return 0;
}
