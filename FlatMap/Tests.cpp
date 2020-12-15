#include "FlatMap.h"
#include <gtest/gtest.h>
using testing::Eq;

namespace {
    class FlatMapTest : public testing::Test{
    protected: FlatMap a, b;
    };
    TEST_F(FlatMapTest, Equal) {
        a.insert("Key", {3, 2});
        a.insert("PPP9", {4, 5});
        a.insert("PPQ8", {6, 7});
        b = a;
        ASSERT_EQ(true, a == b);
        b.erase("Key");
        ASSERT_EQ(false, a == b);
        ASSERT_EQ(true, a != b);
        b.insert("key", {2, 1});
        ASSERT_EQ(false, a == b);
    }

    TEST_F(FlatMapTest, Inequality) {
        a.insert("Key", {3, 2});
        a.insert("PPP9", {6, 5});
        a.insert("PPQ8", {6, 7});
        b.insert("KIy", {3, 2});
        b.insert("PPP9", {4, 9});
        b.insert("PPQ8", {6, 7});
        a = b;
        a.erase("PPP9");
        ASSERT_EQ(true, a != b);
    }

    TEST_F(FlatMapTest, Empty) {
        EXPECT_EQ(true, a.empty());
        a["Key"];
        EXPECT_EQ(false, a.empty());
    }

    TEST_F(FlatMapTest, Swap) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        b.insert("NFJKN:", {56, 2});
        b.insert("NJNJKNL", {4, 9});
        b.insert("PPQ8", {6, 6});
        a.swap(b);
        ASSERT_EQ(false, a == b);
        b.swap(a);
        ASSERT_EQ(true, a.contains("W{ED{W"));
    }

    TEST_F(FlatMapTest, Clear) {
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

    TEST_F(FlatMapTest, Assignment) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        FlatMap c(a);
        ASSERT_EQ(true, a == c);
        c.erase("UYEIE");
        ASSERT_EQ(false, a == c);
        ASSERT_EQ(true, a != c);
        c.insert("key", {2, 1});
        ASSERT_EQ(false, a == c);
    }

    TEST_F(FlatMapTest, Contains) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        FlatMap c(a);
        a.erase("UYEIE");
        a.erase("OFOPEWK");
        a.erase("W{ED{W");
        ASSERT_EQ(false, a == c);
        EXPECT_ANY_THROW(a.at("UYEIE"));
        EXPECT_ANY_THROW(a.at("W{ED{W"));
        ASSERT_EQ(false, a.contains("UYEIE"));
    }

    TEST_F(FlatMapTest, SearchByKey) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        b = a;
        ASSERT_EQ(true, a == b);
        const Value check = {3, 0};
        a.erase("UYEIE");
        a.erase("OFOPEWK");
        a.erase("W{ED{W");
        ASSERT_EQ(true, b.at("UYEIE") == check);
        EXPECT_ANY_THROW(a.at("UYEIE"));
    }

    TEST_F(FlatMapTest, SearchByKeyConst) {
        a.insert("UYEIE", {3, 0});
        a.insert("OFOPEWK", {6, 899});
        a.insert("W{ED{W", {9, 7});
        const FlatMap c(a);
        const Value check = {3, 0};
        ASSERT_EQ(true, a == c);
        a.erase("UYEIE");
        a.erase("OFOPEWK");
        a.erase("W{ED{W");
        ASSERT_EQ(true, c.at("UYEIE") == check);
        EXPECT_ANY_THROW(a.at("UYEIE"));
    }

    TEST_F(FlatMapTest, CheckSize) {
        Key check;
        for (int i = 0; i < 127; ++i) {
            check = std::to_string(rand());
            a.insert(check, {3, 0});
        }
        a.insert("check", {1, 0});
        ASSERT_EQ(true, a.get_size() == 128);
        a.insert("check1", {1, 0});
        ASSERT_EQ(true, a.get_size() == 129);
        a.erase("check1");
        ASSERT_EQ(true, a.get_size() == 128);
    }

    TEST_F(FlatMapTest, OperatorParentheses) {
        Value c = {0, 0};
        EXPECT_EQ(c, a["Key"]);
        c = {1, 2};
        a["Key"] = c;
        EXPECT_EQ(c, a["Key"]);
    }

    TEST_F(FlatMapTest, DeletionError) {
        ASSERT_EQ(true, a.erase("UYEIE") == false);
    }

    TEST_F(FlatMapTest, MultipleInserts) {
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

    TEST_F(FlatMapTest, Insert) {
        EXPECT_EQ(true, a.insert("JKJKJK", {103, 2}));
        EXPECT_EQ(false, a.insert("JKJKJK", {12, 2}));
        EXPECT_EQ(false, a.insert("JKJKJK", {33, 4}));
        EXPECT_EQ(1, a.get_size());
        EXPECT_EQ(true, a.insert("JKJKJKf", {1, 26}));
    }

    TEST_F(FlatMapTest, Erase) {
        EXPECT_EQ(false, a.erase("JKJKJK"));
        a["JKJKJK"] = {1, 2};
        a["JKJKJKf"] = {3, 4};
        a["JKJKJKl"] = {5, 6};
        EXPECT_EQ(true, a.erase("JKJKJKf"));
        EXPECT_EQ(true, a.erase("JKJKJKl"));
        EXPECT_EQ(true, a.erase("JKJKJK"));
        EXPECT_EQ(0, a.get_size());
    }

    TEST_F(FlatMapTest, ResizeCheck) {
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
