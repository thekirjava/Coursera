#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (deallocated_pool.empty()) {
            deallocated_pool.push(new T);
        }
        allocated_pool.insert(deallocated_pool.front());
        T* buf = deallocated_pool.front();
        deallocated_pool.pop();
        return buf;
    }
    T* TryAllocate() {
        if (deallocated_pool.empty()) {
            return nullptr;
        }
        allocated_pool.insert(deallocated_pool.front());
        T* buf = deallocated_pool.front();
        deallocated_pool.pop();
        return buf;
    }

    void Deallocate(T* object) {
        auto it  =allocated_pool.find(object);
        if (it == end(allocated_pool)) {
            throw invalid_argument("invalid_argument");
        }
        deallocated_pool.push(*it);
        allocated_pool.erase(it);
    }

    ~ObjectPool() {
        while (!deallocated_pool.empty()) {
            delete deallocated_pool.front();
            deallocated_pool.pop();
        }
        for (auto ptr:allocated_pool) {
            delete ptr;
        }
        allocated_pool.clear();
    }

private:
    set <T*> allocated_pool;
    queue <T*> deallocated_pool;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
