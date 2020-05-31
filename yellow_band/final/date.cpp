//
// Created by JUSTONEIDEA on 09.05.2020.
//

#include "date.h"

Date::Date(const int &year, const int &month, const int &day) : year(year), month(month), day(day) {}

ostream &operator<<(ostream &os, const Date &d) {
    if (d.year < 1000) {
        os << 0;
    }
    if (d.year < 100) {
        os << 0;
    }
    if (d.year < 10) {
        os << 0;
    }
    os << d.year << "-";
    if (d.month < 10) {
        os << 0;
    }
    os << d.month << "-";
    if (d.day < 10) {
        os << 0;
    }
    os << d.day;
    return os;
}

bool Date::operator<(const Date &d) const {
    if (this->year != d.year) {
        return this->year < d.year;
    }
    if (this->month != d.month) {
        return this->month < d.month;
    }
    return this->day < d.day;
}

bool Date::operator<=(const Date &d) const {
    if (this->year != d.year) {
        return this->year < d.year;
    }
    if (this->month != d.month) {
        return this->month < d.month;
    }
    return this->day <= d.day;
}

bool Date::operator>(const Date &d) const {
    if (this->year != d.year) {
        return this->year > d.year;
    }
    if (this->month != d.month) {
        return this->month > d.month;
    }
    return this->day > d.day;
}

bool Date::operator>=(const Date &d) const {
    if (this->year != d.year) {
        return this->year > d.year;
    }
    if (this->month != d.month) {
        return this->month > d.month;
    }
    return this->day >= d.day;
}

bool Date::operator==(const Date &d) const {
    return (this->year == d.year) && (this->month == d.month) && (this->day == d.day);
}

bool Date::operator!=(const Date &d) const {
    return (this->year != d.year) || (this->month != d.month) || (this->day != d.day);
}

Date ParseDate(istream &is) {
    string s;
    is >> s;
    int year = 0, month = 0, day = 0;
    int i = 0;
    while (s[i] != '-') {
        year *= 10;
        year += s[i] - '0';
        i++;
    }
    i++;
    while (s[i] != '-') {
        month *= 10;
        month += s[i] - '0';
        i++;
    }
    i++;
    while (i < s.size()) {
        day *= 10;
        day += s[i] - '0';
        i++;
    }
    return Date(year, month, day);
}
