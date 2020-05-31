#include <iostream>
#include <map>

using namespace std;

template<typename Key, typename Value>
Value &GetRefStrict( map<Key, Value> &m, Key k);

template<typename Key, typename Value>
Value &GetRefStrict( map<Key, Value> &m, Key k) {
    if (m.find(k) != m.end()) {
        return m[k];
    }
    throw std::runtime_error("runtime error");
}
