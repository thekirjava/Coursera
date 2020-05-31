#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template<class T>
class ObjectPool {
public:
    T *Allocate() {
        if (!deallocated.empty()) {
            T *key = deallocated.front();
            allocated.insert(key);
            deallocated.pop();
            return key;
        } else {
            T *key = new T;
            allocated.insert(key);
            return key;
        }
    }

    T *TryAllocate() {
        if (!deallocated.empty()) {
            T *key = deallocated.front();
            allocated.insert(key);
            deallocated.pop();
            return key;
        } else {
            return nullptr;
        }
    }

    void Deallocate(T *object) {
        if (allocated.count(object) != 0) {
            deallocated.push(object);
            allocated.erase(object);
        } else {
            throw invalid_argument("invalid argument");
        }
    };

    ~ObjectPool() {
        while (!allocated.empty()) {
            T *key = *begin(allocated);
            allocated.erase(key);
            delete key;
        }
        while (!deallocated.empty()) {
            T *key = deallocated.front();
            deallocated.pop();
            delete key;
        }
    }

private:
    set<T *> allocated;
    queue<T *> deallocated;
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
