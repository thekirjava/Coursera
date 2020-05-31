#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Deque {
public:
    Deque() = default;

    bool Empty() const {
        return front.empty() && back.empty();
    }

    size_t Size() const {
        return front.size() + back.size();
    }

    T &operator[](size_t index) {
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        index -= front.size();
        return back[index];
    }

    T operator[](size_t index) const {
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        index -= front.size();
        return back[index];
    }

    T &At(size_t index) {
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        index -= front.size();
        if (index < back.size()) {
            return back[index];
        }
        throw out_of_range("out_of_range");
    }

    T At(size_t index) const {
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        index -= front.size();
        if (index < back.size()) {
            return back[index];
        }
        throw out_of_range("out_of_range");
    }

    T Front() const {
        if (front.empty()) {
            return back[0];
        }
        return front[front.size() - 1];
    }

    T &Front() {
        if (front.empty()) {
            return back[0];
        }
        return front[front.size() - 1];
    }

    T Back() const {
        if (back.empty()) {
            return front[0];
        }
        return back[back.size() - 1];
    }

    T &Back() {
        if (back.empty()) {
            return front[0];
        }
        return back[back.size() - 1];
    }

    void PushFront(T x) {
        front.emplace_back(x);
    }

    void PushBack(T x) {
        back.emplace_back(x);
    }

private:
    vector<T> front;
    vector<T> back;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
