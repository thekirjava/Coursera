#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int ans = abs(finish - start);
        if (reachable_lists_.count(start) < 1) {
            return ans;
        }
        auto it = reachable_lists_.at(start).lower_bound(finish);
        if (reachable_lists_.at(start).end() != it) {
            ans = min(ans, abs(finish - *it));
        }
        if (reachable_lists_.at(start).begin() != it) {
            ans = min(ans, abs(finish - *prev(it)));
        }
        return ans;
    }

private:
    map<int, set<int>> reachable_lists_;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}