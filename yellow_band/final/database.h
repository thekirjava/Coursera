#pragma once

#include <map>
#include <string>
#include <deque>
#include <set>
#include <vector>
#include "date.h"

using namespace std;

class Database {
public:
    void Add(const Date &date, const string &event);

    void Print(ostream &os) const;

    template<typename T>
    int RemoveIf(T predicate) {
        int ans = 0;
        for (auto p = begin(db); p != end(db); p++) {
            deque<string> buf = p->second;
            p->second.clear();
            while (!buf.empty()) {
                if (predicate(p->first, buf.front())) {
                    ans++;
                    multi_event.erase(make_pair(p->first, buf.front()));
                } else {
                    p->second.push_back(buf.front());
                }
                buf.pop_front();
            }
            if ((p != begin(db)) && (prev(p)->second.empty())) {
                db.erase(prev(p));
            }
        }
        return ans;
    }


    template<typename T>
    vector<pair<Date, string >> FindIf(T predicate) const {
        vector<pair<Date, string >> ans;
        for (auto &p: db) {
            for (int i = 0; i < p.second.size(); i++) {
                if (predicate(p.first, p.second[i])) {
                    ans.emplace_back(make_pair(p.first, p.second[i]));
                }
            }
        }
        return ans;
    }

    string Last(Date date) const;

private:
    map<Date, deque<string>> db;
    set<pair<Date, string> > multi_event;
};

template<typename F, typename S>
ostream &operator<<(ostream &os, pair<F, S> p) {
    os << p.first << " " << p.second;
    return os;
}