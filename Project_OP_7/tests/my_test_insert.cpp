#include "unrolled_list.h"

#include <gtest/gtest.h>

TEST(my_test_Insert, InsertEmpty) {
    unrolled_list<int> list;
    list.insert(list.begin(), 42);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 42);
}

TEST(my_test_Insert, InsertAtBegin) {
    unrolled_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.insert(list.begin(), 42);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(*list.begin(), 42);
}

TEST(my_test_Insert, InsertAtEnd) {
    unrolled_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.insert(list.end(), 42);
    EXPECT_EQ(list.size(), 4);
    auto it = list.begin();
    std::advance(it, 3);
    EXPECT_EQ(*it, 42);
}

TEST(my_test_Insert, InsertAtMiddle) {
    unrolled_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    std::advance(it, 1);
    list.insert(it, 42);
    EXPECT_EQ(list.size(), 4);
    it = list.begin();
    std::advance(it, 1);
    EXPECT_EQ(*it, 42);
}

TEST(my_test_Insert, InsertRange) {
    unrolled_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    std::vector<int> values = {40, 50, 60};
    auto it = list.begin();
    std::advance(it, 2);
    list.insert(it, values.begin(), values.end());
    EXPECT_EQ(list.size(), 6);
    it = list.begin();
    std::advance(it, 2);
    EXPECT_EQ(*it, 40);
    std::advance(it, 1);
    EXPECT_EQ(*it, 50);
    std::advance(it, 1);
    EXPECT_EQ(*it, 60);
}

TEST(my_test_Insert, InsertInitializerList) {
    unrolled_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.insert(++(list.begin()), {30, 40, 50});
    EXPECT_EQ(list.size(), 5);
    auto it = list.begin();
    std::advance(it, 1);
    std::advance(it, 1);
    std::advance(it, 1);
    EXPECT_EQ(*it, 50);
}