#include <unrolled_list.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list>
#include <string>

TEST(my_test_UnrolledLinkedList, pushFrontSmall) {
    std::list<int> std_list;
    unrolled_list<int> unrolled_list;

    for (int i = 0; i < 10; ++i) {
        std_list.push_front(i);
        unrolled_list.push_front(i);
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushBackLarge) {
    std::list<int> std_list;
    unrolled_list<int> unrolled_list;

    for (int i = 0; i < 10000; ++i) {
        std_list.push_back(i);
        unrolled_list.push_back(i);
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushFrontMoveString) {
    std::list<std::string> std_list;
    unrolled_list<std::string> unrolled_list;

    for (int i = 0; i < 100; ++i) {
        std::string s = "Str" + std::to_string(i);
        std_list.push_front(s);
        unrolled_list.push_front(std::move(s));
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushBackMoveString) {
    std::list<std::string> std_list;
    unrolled_list<std::string> unrolled_list;

    for (int i = 0; i < 100; ++i) {
        std::string s = "Str" + std::to_string(i);
        std_list.push_back(s);
        unrolled_list.push_back(std::move(s));
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushFrontEmptyCheck) {
    unrolled_list<int> unrolled_list;
    unrolled_list.push_front(42);

    ASSERT_EQ(unrolled_list.size(), 1);
    ASSERT_EQ(*unrolled_list.begin(), 42);
}

TEST(my_test_UnrolledLinkedList, pushBackEmptyCheck) {
    unrolled_list<int> unrolled_list;
    unrolled_list.push_back(99);

    ASSERT_EQ(unrolled_list.size(), 1);
    ASSERT_EQ(*unrolled_list.begin(), 99);
}

TEST(my_test_UnrolledLinkedList, pushFrontMoveInt) {
    std::list<int> std_list;
    unrolled_list<int> unrolled_list;

    for (int i = 0; i < 100; ++i) {
        std_list.push_front(i);
        unrolled_list.push_front(std::move(i));
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushBackMoveInt) {
    std::list<int> std_list;
    unrolled_list<int> unrolled_list;

    for (int i = 0; i < 100; ++i) {
        std_list.push_back(i);
        unrolled_list.push_back(std::move(i));
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, insertMoveString) {
    std::list<std::string> std_list;
    unrolled_list<std::string> unrolled_list;

    for (int i = 0; i < 100; ++i) {
        std::string s = "Str" + std::to_string(i);
        if (i % 2 == 0) {
            std_list.push_front(s);
            unrolled_list.push_front(std::move(s));
        } else {
            std_list.push_back(s);
            unrolled_list.push_back(std::move(s));
        }
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushFrontMoveAndCheck) {
    std::list<std::string> std_list;
    unrolled_list<std::string> unrolled_list;

    for (int i = 0; i < 10; ++i) {
        std::string s = "String" + std::to_string(i);
        std_list.push_front(s);
        unrolled_list.push_front(std::move(s));
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, pushBackMoveAndCheck) {
    std::list<std::string> std_list;
    unrolled_list<std::string> unrolled_list;

    for (int i = 0; i < 10; ++i) {
        std::string s = "String" + std::to_string(i);
        std_list.push_back(s);
        unrolled_list.push_back(std::move(s));
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}

TEST(my_test_UnrolledLinkedList, insertMoveAndCheck) {
    std::list<std::string> std_list;
    unrolled_list<std::string> unrolled_list;

    for (int i = 0; i < 10; ++i) {
        std::string s = "Str" + std::to_string(i);
        if (i % 2 == 0) {
            std_list.push_front(s);
            unrolled_list.push_front(std::move(s));
        } else {
            auto std_it = std_list.begin();
            auto unrolled_it = unrolled_list.begin();
            std::advance(std_it, std_list.size() / 2);
            std::advance(unrolled_it, unrolled_list.size() / 2);
            std_list.insert(std_it, s);
            unrolled_list.insert(unrolled_it, std::move(s));
        }
    }

    ASSERT_THAT(unrolled_list, ::testing::ElementsAreArray(std_list));
}