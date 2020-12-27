#include <string>
#include "HashTable.h"
#include <gtest/gtest.h>

using testing::Eq;

namespace {
    class HashTableTest : public testing::Test {
    protected: HashTable a, b;
    };

    TEST_F(HashTableTest, Equal) {
        a.insert("Key", {3, 2});
        a.insert("PPP9", {4, 5});
        a.insert("PPQ8", {6, 7});
        b = a;
        ASSERT_TRUE(a == b);
        b.erase("Key");
        ASSERT_FALSE(a == b);
        ASSERT_TRUE(a != b);
        b.insert("key", {2, 1});
        ASSERT_FALSE(a == b);
    }

    TEST_F(HashTableTest, Inequality) {
        a.insert("Key", {3, 2});
        a.insert("PPP9", {6, 5});
        a.insert("PPQ8", {6, 7});
        b.insert("KIy", {3, 2});
        b.insert("PPP9", {4, 9});
        b.insert("PPQ8", {6, 7});
        a = b;
        a.erase("PPP9");
        ASSERT_TRUE(a != b);
    }

    TEST_F(HashTableTest, Empty) {
        EXPECT_TRUE(a.empty());
        a["Key"];
        EXPECT_FALSE(a.empty());
    }

    TEST_F(HashTableTest, Swap) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        b.insert("NFJKN:", {56, 2});
        b.insert("NJNJKNL", {4, 9});
        b.insert("PPQ8", {6, 6});
        a.swap(b);
        ASSERT_FALSE(a == b);
        b.swap(a);
        ASSERT_TRUE(a.contains("W{ED{W"));
    }

    TEST_F(HashTableTest, Clear) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        ASSERT_EQ(3, a.get_size());
        a.clear();
        ASSERT_EQ(0, a.get_size());
        EXPECT_ANY_THROW(a.at("UYEIE"));
        EXPECT_ANY_THROW(a.at("OFOPEWK"));
        EXPECT_ANY_THROW(a.at("W{ED{W"));
    }

    TEST_F(HashTableTest, Assignment) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        HashTable c(a);
        ASSERT_TRUE( a == c);
        c.erase("UYEIE");
        ASSERT_FALSE(a == c);
        ASSERT_TRUE(a != c);
        c.insert("key", {2, 1});
        ASSERT_FALSE(a == c);
    }

    TEST_F(HashTableTest, Contains) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        HashTable c(a);
        a.erase("UYEIE");
        ASSERT_FALSE(a == c);
        EXPECT_ANY_THROW(a.at("UYEIE"));
        ASSERT_FALSE(a.contains("UYEIE"));
    }

    TEST_F(HashTableTest, SearchByKey) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        b = a;
        ASSERT_TRUE(a == b);
        const Value check = {3, 0};
        a.erase("UYEIE");
        ASSERT_TRUE(b.at("UYEIE") == check);
        EXPECT_ANY_THROW(a.at("UYEIE"));
    }

    TEST_F(HashTableTest, SearchByKeyConst) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        const HashTable c(a);
        const Value check = {3, 0};
        ASSERT_TRUE(a == c);
        a.erase("UYEIE");
        ASSERT_TRUE(c.at("UYEIE") == check);
        EXPECT_ANY_THROW(a.at("UYEIE"));
    }

    TEST_F(HashTableTest, CheckSize) {
        Key check;
        for (int i = 0; i < 127; ++i) {
            check = std::to_string(rand());
            a.insert(check, {3, 0});
        }
        a.insert("check", {1, 0});
        ASSERT_TRUE(a.get_size() == 128);
        a.insert("check1", {1, 0});
        ASSERT_TRUE(a.get_size() == 129);
        a.erase("check1");
        ASSERT_TRUE(a.get_size() == 128);
    }

    TEST_F(HashTableTest, OperatorParentheses) {
        Value c = {0, 0};
        EXPECT_EQ(c, a["Key"]);
        c = {1, 2};
        a["Key"] = c;
        EXPECT_EQ(c, a["Key"]);
    }

    TEST_F(HashTableTest, DeletionError) {
        ASSERT_TRUE(a.erase("UYEIE") == false);
    }

    TEST_F(HashTableTest, MultipleInserts) {
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
        ASSERT_TRUE(a.get_size() == 100);
    }

    TEST_F(HashTableTest, Insert) {
        EXPECT_TRUE(a.insert("JKJKJK", {103, 2}));
        EXPECT_FALSE(a.insert("JKJKJK", {12, 2}));
        EXPECT_FALSE(a.insert("JKJKJK", {33, 4}));
        EXPECT_EQ(1, a.get_size());
        EXPECT_TRUE(a.insert("JKJKJKf", {1, 26}));
    }

    TEST_F(HashTableTest, Erase) {
        EXPECT_FALSE(a.erase("JKJKJK"));
        a["JKJKJK"] = {1, 2};
        a["JKJKJKf"] = {3, 4};
        a["JKJKJKl"] = {5, 6};
        EXPECT_TRUE(a.erase("JKJKJKf"));
        EXPECT_TRUE(a.erase("JKJKJKl"));
        EXPECT_TRUE(a.erase("JKJKJK"));
        EXPECT_EQ(0, a.get_size());
    }

    TEST_F(HashTableTest, ResizeCheck) {
        std::string str = "0"; unsigned int d = 0;
        for (int i = 0; i < 1000; ++i) {
            a.insert(str, {d, d++});
            str += '0';
            EXPECT_EQ(i + 1, a.get_size());
        }
        d = 0; str = "0";
        for (int i = 0; i < 1000; ++i, str += '0') {
            Value z = {d, d++};
            EXPECT_EQ(z, a.at(str));
        }
        for (int i = 0; i < 1000; ++i) {
            a.insert(str, {d, d++});
            str += '0';
        }
        d = 0; str = "0";
        for (int i = 0; i < 2000; ++i, str += '0') {
            Value z = {d, d++};
            EXPECT_EQ(z, a.at(str));
        }
    }
}
