#pragma once



#include <iostream>
#include <cmath>
#include <memory>
#include <vector>



struct Support {

    virtual void execute() = 0;
    virtual bool flag_execute() const = 0;
    virtual ~Support() = default;
};



template <typename T>
struct Result_Struct {

    virtual T* getresult_ptr() = 0;
    virtual ~Result_Struct() = default;
};



template <typename T>
class Future {

private:
    std::shared_ptr<Result_Struct<T>> future_task;

public:

    Future(std::shared_ptr<Result_Struct<T>> t) : future_task(std::move(t)) {}

    T get() {

        auto current_task = std::dynamic_pointer_cast<Support>(future_task);
        if (!current_task -> flag_execute()) current_task -> execute();

        return *future_task -> getresult_ptr();
    }
};



template <typename T>
class T0_ARG : public Support, public Result_Struct<T> {

private:

    T(*func)();
    std::unique_ptr<T> result;

public:

    T0_ARG(T(*f)()) : func(f) {}

    void execute() override {
        if (!result) result = std::make_unique<T>(func());
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename ARG>
class T1_ARG : public Support, public Result_Struct<T> {
    
private:

    T(*func)(ARG);
    std::unique_ptr<T> result;

    bool flag;
    ARG value;
    std::unique_ptr<Future<ARG>> future_value;

public:

    T1_ARG(T(*f)(ARG), ARG v) : func(f), value(v), flag(false) {}
    T1_ARG(T(*f)(ARG), Future<ARG> v) : func(f), future_value(std::make_unique<Future<ARG>>(v)), flag(true) {}

    void execute() override {

        if (!result) {

            ARG argument = flag ? future_value -> get() : value;
            result = std::make_unique<T>(func(argument));
        }
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename ARG_1, typename ARG_2>
class T2_ARG : public Support, public Result_Struct<T> {

private:

    T(*func)(ARG_1, ARG_2);
    std::unique_ptr<T> result;

    bool flag_1;
    bool flag_2;
    ARG_1 value_1;
    ARG_2 value_2;
    std::unique_ptr<Future<ARG_1>> future_value_1;
    std::unique_ptr<Future<ARG_2>> future_value_2;

public:

    T2_ARG(T(*f)(ARG_1, ARG_2), ARG_1 v_1, ARG_2 v_2) : func(f), value_1(v_1), value_2(v_2), flag_1(false), flag_2(false) {}  
    T2_ARG(T(*f)(ARG_1, ARG_2), Future<ARG_1> v_1, ARG_2 v_2) 
        : func(f), future_value_1(std::make_unique<Future<ARG_1>>(v_1)), value_2(v_2), flag_1(true), flag_2(false) {}
    T2_ARG(T(*f)(ARG_1, ARG_2), ARG_1 v_1, Future<ARG_2> v_2) 
        : func(f), value_1(v_1), future_value_2(std::make_unique<Future<ARG_2>>(v_2)), flag_1(false), flag_2(true) {}
    T2_ARG(T(*f)(ARG_1, ARG_2), Future<ARG_1> v_1, Future<ARG_2> v_2) 
        : func(f), future_value_1(std::make_unique<Future<ARG_1>>(v_1)), 
        future_value_2(std::make_unique<Future<ARG_2>>(v_2)), flag_1(true), flag_2(true) {}

    void execute() override {

        if (!result) {

            ARG_1 argument_1 = flag_1 ? future_value_1 -> get() : value_1;
            ARG_2 argument_2 = flag_2 ? future_value_2 -> get() : value_2;
            result = std::make_unique<T>(func(argument_1, argument_2));
        }
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename OBJ>
class M0_ARG : public Support, public Result_Struct<T> {

private:

    T(OBJ::*method)() const;
    OBJ object;
    std::unique_ptr<T> result;

public:

    M0_ARG(T(OBJ::*m)() const, OBJ o) : method(m), object(o) {}

    void execute() override {
        if (!result) result = std::make_unique<T>((object.*method)());
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename OBJ, typename ARG>
class M1_ARG : public Support, public Result_Struct<T> {

private:

    T(OBJ::*method)(ARG) const;
    OBJ object;
    std::unique_ptr<T> result;

    bool flag;
    ARG value;
    std::unique_ptr<Future<ARG>> future_value;

public:

    M1_ARG(T(OBJ::*m)(ARG) const, OBJ o, ARG v) : method(m), object(o), value(v), flag(false) {}
    M1_ARG(T(OBJ::*m)(ARG) const, OBJ o, Future<ARG> v) 
        : method(m), object(o), future_value(std::make_unique<Future<ARG>>(v)), flag(true) {}

    void execute() override {

        if (!result) {

            ARG argument = flag ? future_value -> get() : value;
            result = std::make_unique<T>((object.*method)(argument));
        }
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename OBJ, typename ARG_1, typename ARG_2>
class M2_ARG : public Support, public Result_Struct<T> {

private:

    T(OBJ::*method)() const;
    OBJ object;
    std::unique_ptr<T> result;

    bool flag_1;
    bool flag_2;
    ARG_1 value_1;
    ARG_2 value_2;
    std::unique_ptr<Future<ARG_1>> future_value_1;
    std::unique_ptr<Future<ARG_2>> future_value_2;

public:

    M2_ARG(T(OBJ::*m)(ARG_1, ARG_2) const, OBJ o, ARG_1 v_1, ARG_2 v_2) 
        : method(m), object(o), value_1(v_1), value_2(v_2), flag_1(false), flag_2(false) {}
    M2_ARG(T(OBJ::*m)(ARG_1, ARG_2) const, OBJ o, Future<ARG_1> v_1, ARG_2 v_2) 
        : method(m), object(o), future_value_1(std::make_unique<Future<ARG_1>>(v_1)), value_2(v_2), flag_1(true), flag_2(false) {}
    M2_ARG(T(OBJ::*m)(ARG_1, ARG_2) const, OBJ o, ARG_1 v_1, Future<ARG_2> v_2) 
        : method(m), object(o), value_1(v_1), future_value_2(std::make_unique<Future<ARG_2>>(v_2)), flag_1(false), flag_2(true) {}
    M2_ARG(T(OBJ::*m)(ARG_1, ARG_2) const, OBJ o, Future<ARG_1> v_1, Future<ARG_2> v_2) 
        : method(m), object(o), future_value_1(std::make_unique<Future<ARG_1>>(v_1)),
        future_value_2(std::make_unique<Future<ARG_2>>(v_2)), flag_1(true), flag_2(true) {}

    void execute() override {

        if (!result) {

            ARG_1 argument_1 = flag_1 ? future_value_1 -> get() : value_1;
            ARG_2 argument_2 = flag_2 ? future_value_2 -> get() : value_2;
            result = std::make_unique<T>((object.*method)(argument_1, argument_2));
        }
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename F>
class L0_ARG : public Support, public Result_Struct<T> {

private:

    F func;
    std::unique_ptr<T> result;

public:

    L0_ARG(F f) : func(std::move(f)) {}

    void execute() override {
        if (!result) result = std::make_unique<T>(func());
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename F, typename ARG>
class L1_ARG : public Support, public Result_Struct<T> {

private:

    F func;
    std::unique_ptr<T> result;

    bool flag;
    ARG value;
    std::unique_ptr<Future<ARG>> future_value;

public:

    L1_ARG(F f, ARG v) : func(std::move(f)), value(v), flag(false) {}
    L1_ARG(F f, Future<ARG> v) : func(std::move(f)), future_value(std::make_unique<Future<ARG>>(v)), flag(true) {}

    void execute() override {

        if (!result) {

            ARG argument = flag ? future_value -> get() : value;
            result = std::make_unique<T>(func(argument));
        }
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



template <typename T, typename F, typename ARG_1, typename ARG_2>
class L2_ARG : public Support, public Result_Struct<T> {

private:

    F func;
    std::unique_ptr<T> result;

    bool flag_1;
    bool flag_2;
    ARG_1 value_1;
    ARG_2 value_2;
    std::unique_ptr<Future<ARG_1>> future_value_1;
    std::unique_ptr<Future<ARG_2>> future_value_2;

public:

    L2_ARG(F f, ARG_1 v_1, ARG_2 v_2) : func(std::move(f)), value_1(v_1), value_2(v_2), flag_1(false), flag_2(false) {}
    L2_ARG(F f, Future<ARG_1> v_1, ARG_2 v_2) 
        : func(std::move(f)), future_value_1(std::make_unique<Future<ARG_1>>(v_1)), value_2(v_2), flag_1(true), flag_2(false) {}
    L2_ARG(F f, ARG_1 v_1, Future<ARG_2> v_2) 
        : func(std::move(f)), value_1(v_1), future_value_2(std::make_unique<Future<ARG_2>>(v_2)), flag_1(false), flag_2(true) {}
    L2_ARG(F f, Future<ARG_1> v_1, Future<ARG_2> v_2) 
        : func(std::move(f)), future_value_1(std::make_unique<Future<ARG_1>>(v_1)),
        future_value_2(std::make_unique<Future<ARG_2>>(v_2)), flag_1(true), flag_2(true) {}

    void execute() override {

        if (!result) {

            ARG_1 argument_1 = flag_1 ? future_value_1 -> get() : value_1;
            ARG_2 argument_2 = flag_2 ? future_value_2 -> get() : value_2;
            result = std::make_unique<T>(func(argument_1, argument_2));
        }
    }

    bool flag_execute() const override { return result != nullptr; }

    T* getresult_ptr() override { return result.get(); }
};



using ID = std::shared_ptr<Support>;

class TTaskScheduler {

private:
    std::vector<ID> task_vector;

public:

// ------------------------------ передаваемые функции ---------------------------------------

    template <typename T>
    ID add(T(*func)()) {

        auto task = std::make_shared<T0_ARG<T>>(func);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename ARG>
    ID add(T(*func)(ARG), ARG arg) {

        auto task = std::make_shared<T1_ARG<T, ARG>>(func, arg);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename ARG>
    ID add(T(*func)(ARG), Future<ARG> arg) {

        auto task = std::make_shared<T1_ARG<T, ARG>>(func, arg);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename ARG_1, typename ARG_2>
    ID add(T(*func)(ARG_1, ARG_2), ARG_1 arg_1, ARG_2 arg_2) {

        auto task = std::make_shared<T2_ARG<T, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename ARG_1, typename ARG_2>
    ID add(T(*func)(ARG_1, ARG_2), Future<ARG_1> arg_1, ARG_2 arg_2) {

        auto task = std::make_shared<T2_ARG<T, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename ARG_1, typename ARG_2>
    ID add(T(*func)(ARG_1, ARG_2), ARG_1 arg_1, Future<ARG_2> arg_2) {

        auto task = std::make_shared<T2_ARG<T, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename ARG_1, typename ARG_2>
    ID add(T(*func)(ARG_1, ARG_2), Future<ARG_1> arg_1, Future<ARG_2> arg_2) {

        auto task = std::make_shared<T2_ARG<T, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

// ------------------------------ методы классов ---------------------------------------

    template <typename T, typename OBJ>
    ID add(T(OBJ::*method)() const, OBJ object) {

        auto task = std::make_shared<M0_ARG<T, OBJ>>(method, object);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename OBJ, typename ARG>
    ID add(T(OBJ::*method)(ARG) const, OBJ object, ARG arg) {

        auto task = std::make_shared<M1_ARG<T, OBJ, ARG>>(method, object, arg);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename OBJ, typename ARG>
    ID add(T(OBJ::*method)(ARG) const, OBJ object, Future<ARG> arg) {

        auto task = std::make_shared<M1_ARG<T, OBJ, ARG>>(method, object, arg);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename OBJ, typename ARG_1, typename ARG_2>
    ID add(T(OBJ::*method)(ARG_1, ARG_2) const, OBJ object, ARG_1 arg_1, ARG_2 arg_2) {

        auto task = std::make_shared<M2_ARG<T, OBJ, ARG_1, ARG_2>>(method, object, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename OBJ, typename ARG_1, typename ARG_2>
    ID add(T(OBJ::*method)(ARG_1, ARG_2) const, OBJ object, Future<ARG_1> arg_1, ARG_2 arg_2) {

        auto task = std::make_shared<M2_ARG<T, OBJ, ARG_1, ARG_2>>(method, object, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename OBJ, typename ARG_1, typename ARG_2>
    ID add(T(OBJ::*method)(ARG_1, ARG_2) const, OBJ object, ARG_1 arg_1, Future<ARG_2> arg_2) {

        auto task = std::make_shared<M2_ARG<T, OBJ, ARG_1, ARG_2>>(method, object, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename T, typename OBJ, typename ARG_1, typename ARG_2>
    ID add(T(OBJ::*method)(ARG_1, ARG_2) const, OBJ object, Future<ARG_1> arg_1, Future<ARG_2> arg_2) {

        auto task = std::make_shared<M2_ARG<T, OBJ, ARG_1, ARG_2>>(method, object, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

// ------------------------------ лямбды ---------------------------------------

    template <typename F, typename T = decltype(std::declval<F>()())>
    ID add(F func) {

        auto task = std::make_shared<L0_ARG<T, F>>(func);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename F, typename ARG, typename T = decltype(std::declval<F>()(std::declval<ARG>()))>
    ID add(F func, ARG arg) {

        auto task = std::make_shared<L1_ARG<T, F, ARG>>(func, arg);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename F, typename ARG, typename T = decltype(std::declval<F>()(std::declval<ARG>()))>
    ID add(F func, Future<ARG> arg) {

        auto task = std::make_shared<L1_ARG<T, F, ARG>>(func, arg);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename F, typename ARG_1, typename ARG_2, typename T = decltype(std::declval<F>()(std::declval<ARG_1>(), std::declval<ARG_2>()))>
    ID add(F func, ARG_1 arg_1, ARG_2 arg_2) {

        auto task = std::make_shared<L2_ARG<T, F, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename F, typename ARG_1, typename ARG_2, typename T = decltype(std::declval<F>()(std::declval<ARG_1>(), std::declval<ARG_2>()))>
    ID add(F func, Future<ARG_1> arg_1, ARG_2 arg_2) {

        auto task = std::make_shared<L2_ARG<T, F, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename F, typename ARG_1, typename ARG_2, typename T = decltype(std::declval<F>()(std::declval<ARG_1>(), std::declval<ARG_2>()))>
    ID add(F func, ARG_1 arg_1, Future<ARG_2> arg_2) {

        auto task = std::make_shared<L2_ARG<T, F, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template <typename F, typename ARG_1, typename ARG_2, typename T = decltype(std::declval<F>()(std::declval<ARG_1>(), std::declval<ARG_2>()))>
    ID add(F func, Future<ARG_1> arg_1, Future<ARG_2> arg_2) {

        auto task = std::make_shared<L2_ARG<T, F, ARG_1, ARG_2>>(func, arg_1, arg_2);
        ID base = task;

        task_vector.push_back(base);

        return base;
    }

    template<typename T>
    Future<T> getFutureResult(ID counter) {

        auto task = std::dynamic_pointer_cast<Result_Struct<T>>(counter);
        if (!task) throw std::runtime_error("Invalid task result type");

        return Future<T>(task);
    }

    template<typename T>
    T getResult(ID counter) {
        return getFutureResult<T>(counter).get();
    }

    void executeAll() {

        for (auto& i : task_vector)
            if (!i -> flag_execute()) i -> execute();
    }
};
