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
/*
class Rational {
public:
    // Вы можете вставлять сюда различные реализации,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный

    Rational();

    Rational(int numerator, int denominator) {
    }

    int Numerator() const {
    }

    int Denominator() const {
    }
};*/

bool operator!=(Rational r1, Rational r2) {
    return ((r1.Numerator() != r2.Numerator()) || (r1.Denominator() != r2.Denominator()));
}

ostream &operator<<(ostream &os, const Rational &r) {
    os << r.Numerator() << '/' << r.Denominator();
    return os;
}

void TestEmpty() {
    Rational empty;
    AssertEqual(empty.Numerator(), 0, "Empty - 1");
    AssertEqual(empty.Denominator(), 1, "Empty - 2");
    Rational expect(0, 1);
    AssertEqual(empty, expect, "Empty-3");
}

void TestReduction() {
    Rational test(2, 4);
    Rational expect(1, 2);
    AssertEqual(test, expect, "Simple reduction");
    test = Rational(6, 15);
    expect = Rational(2, 5);
    AssertEqual(test, expect, "Simple reduction 2");
    test = Rational(-6, 15);
    expect = Rational(-2, 5);
    AssertEqual(test, expect, "Negative reduction 1");
    test = Rational(6, -15);
    expect = Rational(-2, 5);
    AssertEqual(test, expect, "Negative reduction 2");
    test = Rational(-6, -15);
    expect = Rational(2, 5);
    AssertEqual(test, expect, "Negative reduction 3");
}

void TestNegative() {
    Rational test(-2, 3);
    AssertEqual(test.Numerator(), -2, "Negative test 1");
    AssertEqual(test.Denominator(), 3, "Negative test 2");
    test = Rational(2, -3);
    AssertEqual(test.Numerator(), -2, "Negative test 3");
    AssertEqual(test.Denominator(), 3, "Negative test 4");
    test = Rational(-2, -3);
    AssertEqual(test.Numerator(), 2, "Negative test 5");
    AssertEqual(test.Denominator(), 3, "Negative test 6");
}

void TestNull() {
    Rational test(0, 5);
    Rational expect(0, 1);
    AssertEqual(test, expect, "Null test 1");
    test = Rational(0, -5);
    AssertEqual(test, expect, "Null test 2");
    test = Rational(0, 523);
    AssertEqual(test, expect, "Null test 3");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestReduction, "TestReduction");
    runner.RunTest(TestNegative, "TestNegative");
    runner.RunTest(TestNull, "TestNull");
    return 0;
}
