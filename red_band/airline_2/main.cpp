#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values){\
auto it = values.find(#field);\
if (it!=end(values)) {\
    istringstream is (it->second);\
    is >> ticket.field;\
}\
}

bool operator<(const Date &d1, const Date &d2) {
    if (d1.year != d2.year) {
        return d1.year < d2.year;
    }
    if (d1.month != d2.month) {
        return d1.month < d2.month;
    }
    return d1.day < d2.day;
}

bool operator==(const Date d1, const Date d2) {
    return (d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day);
}

ostream &operator<<(ostream &os, const Date date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}

bool operator<(const Time &t1, const Time &t2) {
    if (t1.hours != t2.hours) {
        return t1.hours < t2.hours;
    }
    return t1.minutes < t2.minutes;
}

bool operator==(const Time &t1, const Time &t2) {
    return (t1.hours == t2.hours) && (t1.minutes == t2.minutes);
}

ostream &operator<<(ostream &os, const Time &time) {
    os << time.hours << ":" << time.minutes;
    return os;
}

istream &operator>>(istream &is, Date &date) {
    date = Date{0, 0, 0};
    string s;
    is >> s;
    int i = 0;
    while (s[i] != '-') {
        date.year *= 10;
        date.year += s[i] - '0';
        i++;
    }
    i++;
    while (s[i] != '-') {
        date.month *= 10;
        date.month += s[i] - '0';
        i++;
    }
    i++;
    while (i < s.size()) {
        date.day *= 10;
        date.day += s[i] - '0';
        i++;
    }
    return is;
}

istream &operator>>(istream &is, Time &time) {
    time = Time{0, 0};
    string s;
    is >> s;
    int i = 0;
    while (s[i] != ':') {
        time.hours *= 10;
        time.hours += s[i] - '0';
        i++;
    }
    i++;
    while (i < s.size()) {
        time.minutes *= 10;
        time.minutes += s[i] - '0';
        i++;
    }
    return is;
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price",        "12550"},
            {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
