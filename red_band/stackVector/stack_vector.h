#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template<typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        size = a_size;
        capacity = N;
        if (size > capacity) {
            throw invalid_argument("invalid argument");
        }
    };

    T &operator[](size_t index) {
        return data[index];
    }

    const T &operator[](size_t index) const {
        return data[index];
    }

    auto begin() {
        return data.begin();
    }

    auto end() {
        return data.begin() + size;
    }

    auto begin() const {
        return data.cbegin() + size;
    }

    auto end() const {
        return data.cbegin() + size;
    }

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return capacity;
    }

    void PushBack(const T &value) {
        if (size<capacity) {
            data[size] = value;
            size++;
        } else {
            throw overflow_error("overflow error");
        }
    }

    T PopBack() {
        if (size > 0) {
            size--;
            return data[size];
        } else {
            throw underflow_error("underflow error");
        }
    }

private:
    array<T, N> data;
    size_t size;
    size_t capacity;
};

