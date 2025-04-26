#include <unrolled_list.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>

TEST(my_test_ElementAccess, Front) {
    unrolled_list<int> list{10, 20, 30};

    ASSERT_EQ(list.front(), 10);

    list.front() = 100;
    ASSERT_EQ(list.front(), 100);
}

TEST(my_test_ElementAccess, FrontConst) {
    const unrolled_list<int> list{10, 20, 30};

    ASSERT_EQ(list.front(), 10);
}

TEST(my_test_ElementAccess, FrontThrowsOnEmpty) {
    unrolled_list<int> list;

    ASSERT_THROW(list.front(), std::out_of_range);
}

TEST(my_test_ElementAccess, Back) {
    unrolled_list<int> list{10, 20, 30};

    ASSERT_EQ(list.back(), 30);

    list.back() = 300;
    ASSERT_EQ(list.back(), 300);
}

TEST(my_test_ElementAccess, BackConst) {
    const unrolled_list<int> list{10, 20, 30};

    ASSERT_EQ(list.back(), 30);
}

TEST(my_test_ElementAccess, BackThrowsOnEmpty) {
    unrolled_list<int> list;

    ASSERT_THROW(list.back(), std::out_of_range);
}

TEST(my_test_ElementAccess, AtValidIndex) {
    unrolled_list<int> list{10, 20, 30, 40, 50};

    ASSERT_EQ(list.at(0), 10);
    ASSERT_EQ(list.at(1), 20);
    ASSERT_EQ(list.at(2), 30);
    ASSERT_EQ(list.at(3), 40);
    ASSERT_EQ(list.at(4), 50);

    list.at(2) = 300;
    ASSERT_EQ(list.at(2), 300);
}

TEST(my_test_ElementAccess, AtConstValidIndex) {
    const unrolled_list<int> list{10, 20, 30, 40, 50};

    ASSERT_EQ(list.at(0), 10);
    ASSERT_EQ(list.at(1), 20);
    ASSERT_EQ(list.at(2), 30);
    ASSERT_EQ(list.at(3), 40);
    ASSERT_EQ(list.at(4), 50);
}

TEST(my_test_ElementAccess, AtThrowsOnOutOfBounds) {
    unrolled_list<int> list{10, 20, 30};

    ASSERT_THROW(list.at(3), std::out_of_range);
    ASSERT_THROW(list.at(10), std::out_of_range);
    ASSERT_THROW(list.at(-1), std::out_of_range);
}

TEST(my_test_ElementAccess, AtThrowsOnEmpty) {
    unrolled_list<int> list;

    ASSERT_THROW(list.at(0), std::out_of_range);
}

TEST(my_test_ElementAccess, FrontAndBackAfterModifications) {
    unrolled_list<int> list{1, 2, 3};

    list.front() = 10;
    list.back() = 30;

    ASSERT_EQ(list.front(), 10);
    ASSERT_EQ(list.back(), 30);
}

TEST(my_test_ElementAccess, AtAfterModifications) {
    unrolled_list<int> list{1, 2, 3, 4, 5};

    list.at(0) = 10;
    list.at(4) = 50;

    ASSERT_EQ(list.at(0), 10);
    ASSERT_EQ(list.at(4), 50);
}