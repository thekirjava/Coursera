#pragma once

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Date {
public:
    Date(const int &year, const int &month, const int &day);

    friend ostream &operator<<(ostream &os, const Date &d);
    bool operator<(const Date &d) const;
    bool operator<=(const Date &d) const;
    bool operator>(const Date &d) const;
    bool operator>=(const Date &d) const;
    bool operator==(const Date &d) const;
    bool operator!=(const Date &d) const;
private:
    const int year;
    const int month;
    const int day;
};

Date ParseDate(istream &is);