#include <unrolled_list.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list>
#include <string>
#include <vector>

TEST(my_test_PopFunctions, PopFront) {
    unrolled_list<int> list{1, 2, 3, 4, 5};
    
    list.pop_front();
    ASSERT_THAT(list, ::testing::ElementsAre(2, 3, 4, 5));

    list.pop_front();
    ASSERT_THAT(list, ::testing::ElementsAre(3, 4, 5));

    list.pop_front();
    ASSERT_THAT(list, ::testing::ElementsAre(4, 5));

    list.pop_front();
    ASSERT_THAT(list, ::testing::ElementsAre(5));

    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(my_test_PopFunctions, PopBack) {
    unrolled_list<int> list{1, 2, 3, 4, 5};
    
    list.pop_back();
    ASSERT_THAT(list, ::testing::ElementsAre(1, 2, 3, 4));

    list.pop_back();
    ASSERT_THAT(list, ::testing::ElementsAre(1, 2, 3));

    list.pop_back();
    ASSERT_THAT(list, ::testing::ElementsAre(1, 2));

    list.pop_back();
    ASSERT_THAT(list, ::testing::ElementsAre(1));

    list.pop_back();
    ASSERT_TRUE(list.empty());
}

TEST(my_test_PopFunctions, PopFrontOnEmpty) {
    unrolled_list<int> list;
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(my_test_PopFunctions, PopBackOnEmpty) {
    unrolled_list<int> list;
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

TEST(my_test_PopFunctions, PopFrontOneElement) {
    unrolled_list<int> list{42};
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(my_test_PopFunctions, PopBackOneElement) {
    unrolled_list<int> list{42};
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

TEST(my_test_PopFunctions, PopFrontAfterMultiplePushes) {
    unrolled_list<int> list;
    
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    list.pop_front();
    ASSERT_THAT(list, ::testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9));

    list.pop_front();
    ASSERT_THAT(list, ::testing::ElementsAre(2, 3, 4, 5, 6, 7, 8, 9));
}

TEST(my_test_PopFunctions, PopBackAfterMultiplePushes) {
    unrolled_list<int> list;

    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    list.pop_back();
    ASSERT_THAT(list, ::testing::ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8));

    list.pop_back();
    ASSERT_THAT(list, ::testing::ElementsAre(0, 1, 2, 3, 4, 5, 6, 7));
}

TEST(my_test_PopFunctions, MultiplePopFrontAndBack) {
    unrolled_list<int> list{1, 2, 3, 4, 5};

    list.pop_front();
    list.pop_back();
    list.pop_front();
    list.pop_back();

    ASSERT_THAT(list, ::testing::ElementsAre(3));
}

TEST(my_test_PopFunctions, SizeAfterPopFront) {
    unrolled_list<int> list{1, 2, 3, 4, 5};
    
    list.pop_front();
    ASSERT_EQ(list.size(), 4);
    
    list.pop_front();
    ASSERT_EQ(list.size(), 3);
    
    list.pop_front();
    ASSERT_EQ(list.size(), 2);
    
    list.pop_front();
    ASSERT_EQ(list.size(), 1);
    
    list.pop_front();
    ASSERT_EQ(list.size(), 0);
}

TEST(my_test_PopFunctions, SizeAfterPopBack) {
    unrolled_list<int> list{1, 2, 3, 4, 5};
    
    list.pop_back();
    ASSERT_EQ(list.size(), 4);
    
    list.pop_back();
    ASSERT_EQ(list.size(), 3);
    
    list.pop_back();
    ASSERT_EQ(list.size(), 2);
    
    list.pop_back();
    ASSERT_EQ(list.size(), 1);
    
    list.pop_back();
    ASSERT_EQ(list.size(), 0);
}
