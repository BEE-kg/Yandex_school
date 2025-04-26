#include <unrolled_list.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>

TEST(my_test_delete, EraseSingleElement) {
    unrolled_list<int> list{10, 20, 30, 40, 50};

    auto it = list.erase(list.begin());

    ASSERT_THAT(list, ::testing::ElementsAre(20, 30, 40, 50));
    ASSERT_EQ(*it, 20);
}

TEST(my_test_delete, EraseMiddleElement) {
    unrolled_list<int> list{10, 20, 30, 40, 50};

    auto it = list.erase(++list.begin());

    ASSERT_THAT(list, ::testing::ElementsAre(10, 30, 40, 50));
    ASSERT_EQ(*it, 30);
}

TEST(my_test_delete, EraseOnlyElement) {
    unrolled_list<int> list{10};

    auto it = list.erase(list.begin());

    ASSERT_TRUE(list.empty());
    ASSERT_EQ(it, list.end());
}

TEST(my_test_delete, EraseRange) {
    unrolled_list<int> list{10, 20, 30, 40, 50};

    auto it = list.erase(++list.begin(), ++(++list.begin()));

    ASSERT_THAT(list, ::testing::ElementsAre(10, 30, 40, 50));
    ASSERT_EQ(*it, 40);
}

TEST(my_test_delete, ClearNonEmptyList) {
    unrolled_list<int> list{10, 20, 30, 40, 50};

    list.clear();

    ASSERT_TRUE(list.empty());
    ASSERT_EQ(list.begin(), list.end());
}

TEST(my_test_delete, ClearEmptyList) {
    unrolled_list<int> list;

    list.clear();

    ASSERT_TRUE(list.empty());
    ASSERT_EQ(list.begin(), list.end());
}
