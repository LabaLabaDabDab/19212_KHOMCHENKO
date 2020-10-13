#include <string>
#include "HashTable.h"
#include <gtest/gtest.h>

using testing::Eq;

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
    a.insert("UYEIE", {3, 0});
    a.insert("OFOPEWK", {6, 899});
    a.insert("W{ED{W", {9, 7});
    HashTable b(a);
    ASSERT_EQ(true, a == b);
}

TEST_F(HashTableTest, test6) {
    HashTable a;
    a.insert("UYEIE", {3, 0});
    a.insert("OFOPEWK", {6, 899});
    a.insert("W{ED{W", {9, 7});
    a.erase("UYEIE");
    ASSERT_EQ(false, a.contains("UYEIE"));
}

TEST_F(HashTableTest, test7) {
    HashTable a;
    a.insert("UYEIE", {3, 0});
    a.insert("OFOPEWK", {6, 899});
    a.insert("W{ED{W", {9, 7});
    const Value check = {3, 0};
    ASSERT_EQ(true, a.at("UYEIE") == check);
}

TEST_F(HashTableTest, test8) {
    HashTable a;
    a.insert("UYEIE", {3, 0});
    a.insert("OFOPEWK", {6, 899});
    a.insert("W{ED{W", {9, 7});
    const HashTable b(a);
    const Value check = {3, 0};
    ASSERT_EQ(true, b.at("UYEIE") == check);
}


