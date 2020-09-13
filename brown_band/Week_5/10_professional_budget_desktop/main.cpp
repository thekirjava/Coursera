#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <unordered_map>
#include<queue>

using namespace std;

class Date {
public:
    explicit Date(const string &s) {
        year = stoi(s.substr(0, 4));
        month = stoi(s.substr(5, 2));
        day = stoi(s.substr(8, 2));
    }

    bool operator<(const Date &d) const {
        if (year != d.year) {
            return year < d.year;
        }
        if (month != d.month) {
            return month < d.month;
        }
        return day < d.day;
    }

    bool operator==(const Date &d) const {
        return (d.day == day) && (d.month == month) && (d.year == year);
    }

    time_t AsTimestamp() const {
        tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = day;
        t.tm_mon = month - 1;
        t.tm_year = year - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

    const static int DAY_AS_SECONDS = 86400;
private:
    int day;
    int month;
    int year;

};

class Budget {
public:

    double ComputeIncome(const Date &from, const Date &to) {
        if (from.AsTimestamp() > to.AsTimestamp()) { return 0; }
        double ans = 0;
        auto from_time = from.AsTimestamp();
        auto to_time = to.AsTimestamp();
        for (auto i = from_time; i <= to_time; i += Date::DAY_AS_SECONDS) {
            ans += earned[i];
            ans -= spended[i];
        }
        return ans;
    }

    void Earn(const Date &from, const Date &to, double value) {
        if (from.AsTimestamp() > to.AsTimestamp()) { return; }
        value /= ((to.AsTimestamp() - from.AsTimestamp()) / Date::DAY_AS_SECONDS) + 1;
        auto from_time = from.AsTimestamp();
        auto to_time = to.AsTimestamp();
        for (auto i = from_time; i <= to_time; i += Date::DAY_AS_SECONDS) {
            earned[i] += value;
        }
    }

    void PayTax(const Date &from, const Date &to, double value = 13) {
        if (from.AsTimestamp() > to.AsTimestamp()) { return; }
        auto from_time = from.AsTimestamp();
        auto to_time = to.AsTimestamp();
        value /= 100;
        for (auto i = from_time; i <= to_time; i += Date::DAY_AS_SECONDS) {
            earned[i] *= 1 - value;
        }
    }

    void Spend(const Date &from, const Date &to, double value) {
        if (from.AsTimestamp() > to.AsTimestamp()) { return; }
        value /= ((to.AsTimestamp() - from.AsTimestamp()) / Date::DAY_AS_SECONDS) + 1;
        auto from_time = from.AsTimestamp();
        auto to_time = to.AsTimestamp();
        for (auto i = from_time; i <= to_time; i += Date::DAY_AS_SECONDS) {
            spended[i] += value;
        }
    }

private:
    map<time_t, double> earned;
    map<time_t, double> spended;
};

int main() {
    Budget budget;
    int Q;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> Q;
    cout.precision(25);
    queue<double> ans;
    for (int i = 0; i < Q; i++) {
        string cmd, from, to;
        cin >> cmd >> from >> to;
        if (cmd == "ComputeIncome") {
            ans.push(budget.ComputeIncome(Date(from), Date(to)));
        }
        if (cmd == "Earn") {
            double value;
            cin >> value;
            budget.Earn(Date(from), Date(to), value);
        }
        if (cmd == "PayTax") {
            double value;
            cin >> value;
            budget.PayTax(Date(from), Date(to), value);
        }
        if (cmd == "Spend") {
            double value;
            cin >> value;
            budget.Spend(Date(from), Date(to), value);
        }
    }
    while (!ans.empty()) {
        cout << ans.front() << '\n';
        ans.pop();
    }
    return 0;
}
