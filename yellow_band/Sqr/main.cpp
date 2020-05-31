#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename T>
T Sqr(T x);

template<typename T>
vector<T> Sqr(const vector<T> &v);

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value> &m);

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second> &p);

template<typename T>
T Sqr(T x) {
    return x * x;
}

template<typename T>
vector<T> Sqr(const vector<T> &v) {
    vector<T> ans;
    for (const auto &i:v) {
        ans.emplace_back(Sqr(i));
    }
    return ans;
}

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value> &m) {
    map<Key, Value> ans;
    for (const auto &p:m) {
        ans[p.first] = Sqr(p.second);
    }
    return ans;
}

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second> &p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}
