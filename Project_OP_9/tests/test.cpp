#include <scheduler.h>

#include <gtest/gtest.h>

struct AddNumber {
    float add(float x) const { return x + 5.0f; }
};

TEST(TaskSchedulerTest, AddSimple) {
    TTaskScheduler scheduler;
    float a = 2.0f, b = 3.0f;
    auto id = scheduler.add([](float x, float y) { return x + y; }, a, b);
    scheduler.executeAll();
    EXPECT_FLOAT_EQ(scheduler.getResult<float>(id), 5.0f);
}

TEST(TaskSchedulerTest, AddWithFuture) {
    TTaskScheduler scheduler;
    float a = 2.0f, b = 3.0f;
    auto id1 = scheduler.add([](float x, float y) { return x + y; }, a, b);
    auto id2 = scheduler.add([](float x, float y) { return x * y; }, a, scheduler.getFutureResult<float>(id1));
    scheduler.executeAll();
    EXPECT_FLOAT_EQ(scheduler.getResult<float>(id2), 2.0f * 5.0f);
}

TEST(TaskSchedulerTest, ExecuteAllBasic) {
    TTaskScheduler scheduler;
    auto id = scheduler.add([]() { return 42; });
    scheduler.executeAll();
    EXPECT_EQ(scheduler.getResult<int>(id), 42);
}

TEST(TaskSchedulerTest, ExecuteAllChain) {
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([]() { return 7; });
    auto id2 = scheduler.add([](int x) { return x * 2; }, scheduler.getFutureResult<int>(id1));
    auto id3 = scheduler.add([](int x) { return x - 3; }, scheduler.getFutureResult<int>(id2));
    scheduler.executeAll();
    EXPECT_EQ(scheduler.getResult<int>(id3), 11);
}

TEST(TaskSchedulerTest, GetFutureResultSimple) {
    TTaskScheduler scheduler;
    auto id = scheduler.add([]() { return 10; });
    Future<int> future = scheduler.getFutureResult<int>(id);
    scheduler.executeAll();
    EXPECT_EQ(future.get(), 10);
}

TEST(TaskSchedulerTest, GetFutureResultChain) {
    TTaskScheduler scheduler;
    auto id = scheduler.add([]() { return 5; });
    auto id2 = scheduler.add([](int x) { return x * x; }, scheduler.getFutureResult<int>(id));
    Future<int> future = scheduler.getFutureResult<int>(id2);
    scheduler.executeAll();
    EXPECT_EQ(future.get(), 25);
}

TEST(TaskSchedulerTest, GetResultSimple) {
    TTaskScheduler scheduler;
    auto id = scheduler.add([]() { return 123; });
    scheduler.executeAll();
    int result = scheduler.getResult<int>(id);
    EXPECT_EQ(result, 123);
}

TEST(TaskSchedulerTest, GetResultMath) {
    TTaskScheduler scheduler;
    float a = 1.0f, b = -3.0f, c = 2.0f;
    auto id1 = scheduler.add([](float a, float c) { return a * a + c * c; }, a, c);
    auto id2 = scheduler.add([](float b, float d) { return -b + std::sqrt(d); }, b, scheduler.getFutureResult<float>(id1));
    scheduler.executeAll();
    float result = scheduler.getResult<float>(id2);
    EXPECT_NEAR(result, 3.0f + std::sqrt(5.0f), 1e-5f);
}

