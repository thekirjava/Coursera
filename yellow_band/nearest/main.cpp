#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
        const set<int> &numbers,
        int border) {
    if (numbers.empty()) {
        return end(numbers);
    }
    auto it = numbers.upper_bound(border);
    if ((it == end(numbers)) || (abs(*it - border) >= abs(*prev(it) - border))) {
        it--;
    }
    return it;
}
