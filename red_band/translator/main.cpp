#include "test_runner.h"
#include <string>
#include <vector>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        s[string(source)] = "";
        t[string(target)] = "";
        auto it_1 = s.find(string(source));
        auto it_2 = t.find(string(target));
        s[string(source)] = it_2->first;
        t[string(target)] = it_1->first;
    }

    string_view TranslateForward(string_view source) const {
        if (s.count(string(source)) == 0) {
            return "";
        }
        return s.at(string(source));
    }

    string_view TranslateBackward(string_view target) const {
        if (t.count(string(target)) == 0) {
            return "";
        }
        return t.at(string(target));
    }

private:
    map<string, string_view> s;
    map<string, string_view> t;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));
    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
    translator.Add(string("stol"), string("lots"));
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
