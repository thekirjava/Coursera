#pragma once

#include <algorithm>

using namespace std;

template<typename It>
class IteratorRange {
public:
    IteratorRange(It first, It last) : first(first), last(last) {
    }

    It begin() const {
        return first;
    }

    It end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }

private:
    It first, last;
};

template<typename Container>
auto Head(Container &c, int top) {

    if (c.size() <= top) {
        sort(begin(c), end(c), [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
            long long lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            long long rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        });
        return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
    }
    for (int i = 0; i < top; i++) {
        auto mx = max_element(next(begin(c), i), end(c), [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
            long long lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            long long rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        });
        swap(*(next(begin(c), i)), *mx);
    }
    return IteratorRange(begin(c), begin(c) + top);
}
