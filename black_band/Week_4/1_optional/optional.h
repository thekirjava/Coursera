#pragma once

#include <memory>

// Исключение этого типа должно генерироваться при обращении к "пустому" Optional в функции Value
struct BadOptionalAccess {
};

template<typename T>
class Optional {
private:
    // alignas нужен для правильного выравнивания блока памяти
    alignas(T) unsigned char data[sizeof(T)];
    bool defined = false;

public:
    Optional() = default;

    Optional(const T &elem) {
        new(data) T{elem};
        defined = true;
    }

    Optional(T &&elem) {
        new(data) T{std::move(elem)};
        defined = true;
    }

    Optional(const Optional &other) {
        if (other.defined) {
            new(data) T(other.Value());
        }
        defined = other.defined;
    }

    Optional(Optional &&other) {
        if (other.defined) {
            new(data) T(std::move(other.Value()));
        }
        defined = other.defined;
    }

    Optional &operator=(const T &elem) {
        if (defined) {
            *reinterpret_cast<T *>(data) = elem;
        } else {
            new(data) T{elem};
            defined = true;
        }
        return *this;
    }

    Optional &operator=(T &&elem) {
        if (defined) {
            *reinterpret_cast<T *>(data) = std::move(elem);
        } else {
            new(data) T{std::move(elem)};
            defined = true;
        }
        return *this;
    }

    Optional &operator=(const Optional &other) {
        if (defined) {
            if (other.defined) {
                *reinterpret_cast<T *>(data) = other.Value();
            } else {
                reinterpret_cast<T *>(data)->~T();
            }
        } else if (other.defined) {
            new(data) T(std::move(other.Value()));
        }
        defined = other.defined;
        return *this;
    }

    Optional &operator=(Optional &&other) {
        if (defined) {
            if (other.defined) {
                *reinterpret_cast<T *>(data) = std::move(other.Value());
            } else {
                reinterpret_cast<T *>(data)->~T();
            }
        } else if (other.defined) {
            new(data) T(std::move(std::move(other.Value())));
        }
        defined = other.defined;
        return *this;
    }

    bool HasValue() const {
        return defined;
    }

    // Эти операторы не должны делать никаких проверок на пустоту.
    // Проверки остаются на совести программиста.
    T &operator*() {
        return *Get();
    }

    const T &operator*() const {
        return *Get();
    }

    T *operator->() {
        return Get();
    }

    const T *operator->() const {
        return Get();
    }

    // Генерирует исключение BadOptionalAccess, если объекта нет
    T &Value() {
        if (defined) {
            return *Get();
        } else {
            throw BadOptionalAccess{};
        }
    }

    const T &Value() const {
        if (defined) {
            return *Get();
        } else {
            throw BadOptionalAccess{};
        }
    }

    void Reset() {
        if (defined) {
            reinterpret_cast<T *>(data)->~T();
        }
        defined = false;
    }

    ~Optional() {
        Reset();

    }

private:
    T *Get() {
        return reinterpret_cast<T *>(data);
    }

    const T *Get() const {
        return reinterpret_cast<const T *>(data);
    }
};
