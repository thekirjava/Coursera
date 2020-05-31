#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
    SimpleVector();

    explicit SimpleVector(size_t size);

    SimpleVector(const SimpleVector &simpleVector);

    SimpleVector(SimpleVector &&simpleVector) noexcept;

    ~SimpleVector();

    SimpleVector<T> &operator=(const SimpleVector &simpleVector);
    SimpleVector<T> &operator=(SimpleVector &&simpleVector);

    T &operator[](size_t index);

    T *begin();

    T *end();

    const T *begin() const;

    const T *end() const;

    size_t Size() const;

    size_t Capacity() const;

    void PushBack(const T &value);
    void PushBack(T&& value);

private:
    T *data;
    size_t size;
    size_t capacity;
};

template<typename T>
SimpleVector<T>::SimpleVector() {
    size = 0;
    capacity = 0;
    data = nullptr;
}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) {
    this->size = size;
    capacity = size;
    data = new T[size];
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data;
}

template<typename T>
T &SimpleVector<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
T *SimpleVector<T>::begin() {
    return data;
}

template<typename T>
T *SimpleVector<T>::end() {
    return data + size;
}

template<typename T>
const T *SimpleVector<T>::begin() const {
    return data;
}

template<typename T>
const T *SimpleVector<T>::end() const {
    return data + size;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return size;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity;
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if ((capacity == 0) || (capacity == size)) {
        if (capacity == 0) {
            capacity = 1;
            data = new T[1];
        } else {
            capacity *= 2;
            T *buf = new T[capacity];
            for (int i = 0; i < size; i++) {
                buf[i] = data[i];
            }
            delete[] data;
            data = buf;
        }

    }
    data[size] = value;
    size++;
}

template<typename T>
SimpleVector<T> &SimpleVector<T>::operator=(const SimpleVector &simpleVector) {
    this->capacity = simpleVector.capacity;
    this->size = simpleVector.size;
    delete[] this->data;
    this->data = new T[this->capacity];
    copy(simpleVector.begin(), simpleVector.end(), this->data);
    return *this;
}

template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector &simpleVector):data(new T[simpleVector.capacity]),
                                                                size(simpleVector.size),
                                                                capacity(simpleVector.capacity) {
    copy(simpleVector.begin(), simpleVector.end(), this->data);
}

template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector &&simpleVector) noexcept:data(simpleVector.data), size(simpleVector.size), capacity(simpleVector.capacity) {
    simpleVector.data = nullptr;
    simpleVector.capacity = 0;
    simpleVector.size = 0;
}

template<typename T>
SimpleVector<T> &SimpleVector<T>::operator=(SimpleVector &&simpleVector) {
    delete[] data;
    data = simpleVector.data;
    simpleVector.data = nullptr;
    capacity = simpleVector.capacity;
    size = simpleVector.size;
    simpleVector.capacity = 0;
    simpleVector.size = 0;
    return *this;
}

template<typename T>
void SimpleVector<T>::PushBack(T &&value) {
    if ((capacity == 0) || (capacity == size)) {
        if (capacity == 0) {
            capacity = 1;
            data = new T[1];
        } else {
            capacity *= 2;
            T *buf = new T[capacity];
            for (int i = 0; i < size; i++) {
                buf[i] = move(data[i]);
            }
            delete[] data;
            data = buf;
        }

    }
    data[size] = move(value);
    size++;
}

