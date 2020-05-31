#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Person {
public:
    void ChangeFirstName(int year, const string &first_name) {
        names[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name) {
        surnames[year] = last_name;
    }

    string GetFullName(int year) {
        auto name = names.upper_bound(year);
        auto surname = surnames.upper_bound(year);
        bool flag = false;
        if (begin(names) == name) {
            flag = true;
        } else {
            name = prev(name);
        }
        if (begin(surnames) == surname) {
            if (flag) {
                return "Incognito";
            } else {
                return name->second + " with unknown last name";
            }
        } else {
            surname = prev(surname);
            if (flag) {
                return surname->second + " with unknown first name";
            }
            return name->second + " " + surname->second;
        }
    }

private:
    map<int, string> names;
    map<int, string> surnames;
};


void FirstNameTester() {
    Person p;
    p.ChangeFirstName(1999, "Ivan");
    p.ChangeLastName(2001, "Ivanov");
    AssertEqual(p.GetFullName(1998), "Incognito", "Ivan 1998");
    AssertEqual(p.GetFullName(1999), "Ivan with unknown last name", "Ivan 1999");
    AssertEqual(p.GetFullName(2000), "Ivan with unknown last name", "Ivan 2000");
    AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Ivan 2001");
    AssertEqual(p.GetFullName(2002), "Ivan Ivanov", "Ivan 2002");

    p.ChangeFirstName(1997, "Petr");
    AssertEqual(p.GetFullName(1997), "Petr with unknown last name", "Petr 1997");
    AssertEqual(p.GetFullName(1998), "Petr with unknown last name", "Petr 1998");
    AssertEqual(p.GetFullName(1999), "Ivan with unknown last name", "Petr 1999");
    AssertEqual(p.GetFullName(2000), "Ivan with unknown last name", "Petr 2000");
    AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Petr 2001");
    AssertEqual(p.GetFullName(2002), "Ivan Ivanov", "Petr 2002");

    p.ChangeFirstName(2004, "Sidor");
    AssertEqual(p.GetFullName(1997), "Petr with unknown last name", "Sidor 1997");
    AssertEqual(p.GetFullName(1998), "Petr with unknown last name", "Sidor 1998");
    AssertEqual(p.GetFullName(1999), "Ivan with unknown last name", "Sidor 1999");
    AssertEqual(p.GetFullName(2000), "Ivan with unknown last name", "Sidor 2000");
    AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Sidor 2001");
    AssertEqual(p.GetFullName(2002), "Ivan Ivanov", "Sidor 2002");
    AssertEqual(p.GetFullName(2003), "Ivan Ivanov", "Sidor 2003");
    AssertEqual(p.GetFullName(2004), "Sidor Ivanov", "Sidor 2004");
    AssertEqual(p.GetFullName(2005), "Sidor Ivanov", "Sidor 2005");
}

void LastNameTester() {
    Person p;
    p.ChangeFirstName(2001, "Ivan");
    p.ChangeLastName(1999, "Ivanov");
    AssertEqual(p.GetFullName(1998), "Incognito", "Ivanov 1998");
    AssertEqual(p.GetFullName(1999), "Ivanov with unknown first name", "Ivanov 1999");
    AssertEqual(p.GetFullName(2000), "Ivanov with unknown first name", "Ivanov 2000");
    AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Ivanov 2001");
    AssertEqual(p.GetFullName(2002), "Ivan Ivanov", "Ivanov 2002");

    p.ChangeLastName(1997, "Petrov");
    AssertEqual(p.GetFullName(1997), "Petrov with unknown first name", "Petrov 1997");
    AssertEqual(p.GetFullName(1998), "Petrov with unknown first name", "Petrov 1998");
    AssertEqual(p.GetFullName(1999), "Ivanov with unknown first name", "Petrov 1999");
    AssertEqual(p.GetFullName(2000), "Ivanov with unknown first name", "Petrov 2000");
    AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Petrov 2001");
    AssertEqual(p.GetFullName(2002), "Ivan Ivanov", "Petrov 2002");

    p.ChangeLastName(2004, "Sidorov");
    AssertEqual(p.GetFullName(1997), "Petrov with unknown first name", "Sidorov 1997");
    AssertEqual(p.GetFullName(1998), "Petrov with unknown first name", "Sidorov 1998");
    AssertEqual(p.GetFullName(1999), "Ivanov with unknown first name", "Sidorov 1999");
    AssertEqual(p.GetFullName(2000), "Ivanov with unknown first name", "Sidorov 2000");
    AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Sidorov 2001");
    AssertEqual(p.GetFullName(2002), "Ivan Ivanov", "Sidorov 2002");
    AssertEqual(p.GetFullName(2003), "Ivan Ivanov", "Sidorov 2003");
    AssertEqual(p.GetFullName(2004), "Ivan Sidorov", "Sidorov 2004");
    AssertEqual(p.GetFullName(2005), "Ivan Sidorov", "Sidorov 2005");
}
