#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
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

bool IsPalindrom(const string& str) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}

void TestPalindrom() {
    Assert(IsPalindrom(""), "Empty");
    Assert(IsPalindrom(" "), "One space");
    Assert(IsPalindrom("  "), "Two spaces");
    Assert(IsPalindrom("aba"), "Test 1");
    Assert(IsPalindrom("abaaba"), "Test2");
    Assert(IsPalindrom("a"), "Test3");
    Assert(IsPalindrom("ab ba"), "Space test");
    Assert(!IsPalindrom("abcdecba"), "False test 1");
    Assert(!IsPalindrom("abcddcb"), "Without last");
    Assert(!IsPalindrom("bcddcba"), "Without first");
    Assert(!IsPalindrom("ab aba"), "False space");
    Assert(IsPalindrom("ab a ba"), "True space");
    Assert(IsPalindrom("abc\ncba"), "New line test");
    Assert(!IsPalindrom("  aba   "), "space test 1");
    Assert(!IsPalindrom("    aba   "), "space test 2");
    Assert(IsPalindrom("   aba   "), "space test 3");
    Assert(IsPalindrom("AbA"), "Register test 1");
    Assert(IsPalindrom("ABA"), "Register test 2");
    Assert(IsPalindrom("aBa"), "Register test 3");
    Assert(!IsPalindrom("ABa"), "Register test 4");
    Assert(!IsPalindrom("aBA"), "Register test 5");
    Assert(!IsPalindrom("Aba"), "Register test 6");
    Assert(!IsPalindrom("abA"), "Register test 7");

}
int main() {
    TestRunner runner;
    runner.RunTest(TestPalindrom, "TestPalindrom");
    // добавьте сюда свои тесты
    return 0;
}
