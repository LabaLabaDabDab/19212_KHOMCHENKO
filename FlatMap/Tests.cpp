#include <string>
#include "HashTable.h"
#include <gtest/gtest.h>

using testing::Eq;

namespace {
    class HashTableTest : public testing::Test {
    protected: HashTable a, b;
    };

    TEST_F(HashTableTest, test1) {
        a.insert("Key", {3, 2});
        a.insert("PPP9", {4, 5});
        a.insert("PPQ8", {6, 7});
        b.insert("Key", {3, 2});
        b.insert("PPQ8", {6, 7});
        b.insert("PPP9", {4, 5});
        ASSERT_EQ(true, a == b);
    }

    TEST_F(HashTableTest, test2) {
        a.insert("Key", {3, 2});
        a.insert("PPP9", {6, 5});
        a.insert("PPQ8", {6, 7});
        b.insert("KIy", {3, 2});
        b.insert("PPP9", {4, 9});
        b.insert("PPQ8", {6, 7});
        ASSERT_EQ(true, a != b);
    }

    TEST_F(HashTableTest, test3) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        b.insert("NFJKN:", {56, 2});
        b.insert("NJNJKNL", {4, 9});
        b.insert("PPQ8", {6, 6});
        a.swap(b);
        ASSERT_EQ(true, a.contains("PPQ8"));
    }

    TEST_F(HashTableTest, test4) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        a.clear();
        ASSERT_EQ(true, a.empty());
    }

    TEST_F(HashTableTest, test5) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        HashTable c(a);
        ASSERT_EQ(true, a == c);
    }

    TEST_F(HashTableTest, test6) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        a.erase("UYEIE");
        ASSERT_EQ(false, a.contains("UYEIE"));
    }

    TEST_F(HashTableTest, test7) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        const Value check = {3, 0};
        ASSERT_EQ(true, a.at("UYEIE") == check);
    }

    TEST_F(HashTableTest, test8) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        const HashTable c(a);
        const Value check = {3, 0};
        ASSERT_EQ(true, c.at("UYEIE") == check);
    }

    TEST_F(HashTableTest, test9) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        b = a;
        ASSERT_EQ(true, a == b);
    }

    TEST_F(HashTableTest, test10) {
        Key check;
        for (int i = 0; i < 129; ++i) {
            check = std::to_string(rand());
            a.insert(check, {3, 0});
        }
        ASSERT_EQ(true, a.get_size() == 129);
    }

    TEST_F(HashTableTest, test11) {
        a.insert("UYEIE", {3, 0});
        a.insert("Uewfwef", {3, 0});
        b.insert("UYfdew", {2, 0});
        ASSERT_EQ(false, a == b);
    }

    TEST_F(HashTableTest, test12) {
        a.insert("UYEIE", {3, 0});
        Value check = {3, 0};
        ASSERT_EQ(true, a.operator[]("UYEIE") == check);
    }

    TEST_F(HashTableTest, test13) {
        a.insert("UYEIE", {3, 0});
        Value check = {3, 0};
        ASSERT_EQ(true, a.operator[]("UYEIE") == check);
    }

    TEST_F(HashTableTest, test14) {
        a.insert("UYEIE", {3, 0});
        Value check = {2, 0};
        ASSERT_EQ(false, a.operator[]("UYауцIE") == check);
    }

    TEST_F(HashTableTest, test15) {
        a.insert("UYEIE", {3, 0});
        a.erase("UYEIE");
        Value check = {0, 0};
        ASSERT_EQ(true, a.operator[]("UYEIE") == check);
    }

    TEST_F(HashTableTest, test16) {
        a.erase("UYEIE");
        ASSERT_EQ(true, a.erase("UYEIE") == false);
    }

    TEST_F(HashTableTest, test17) {
        Key check;
        for (int i = 0; i < 1000; ++i) {
            check = std::to_string(rand());
            a.insert(check, {3, 0});
        }
        a.clear();
        for (int i = 0; i < 100; ++i) {
            check = std::to_string(rand());
            a.insert(check, {9, 0});
        }
        ASSERT_EQ(true, a.get_size() == 100);
    }
}