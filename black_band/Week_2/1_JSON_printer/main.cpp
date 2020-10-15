#include "test_runner.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <string>


void PrintJsonInt(std::ostream &out, int64_t value) {
    out << value;
}

void PrintJsonString(std::ostream &out, std::string_view str) {
    out << '\"';
    for (const auto c:str) {
        if ((c == '\\') || (c == '\"')) {
            out << '\\';
        }
        out << c;
    }
    out << '\"';
}

void PrintJsonBool(std::ostream &out, bool value) {
    out << std::boolalpha << value;
}

void PrintNull(std::ostream &out) {
    out << "null";
}

template<typename Owner>
class JSONObject;

template<typename Owner>
class JSONArray {
public:
    JSONArray(std::ostream &out, Owner &parent) : out(out), parent(parent) {
        out << "[";
    }

    JSONArray &Number(int64_t value) {
        PrintDeliminator();
        PrintJsonInt(out, value);
        return *this;
    }

    JSONArray &String(std::string_view value) {
        PrintDeliminator();
        PrintJsonString(out, value);
        return *this;
    }

    JSONArray &Boolean(bool value) {
        PrintDeliminator();
        PrintJsonBool(out, value);
        return *this;
    }

    JSONArray &Null() {
        PrintDeliminator();
        PrintNull(out);
        return *this;
    }

    auto BeginArray() {
        PrintDeliminator();
        return JSONArray<JSONArray<Owner>>(out, *this);
    }

    auto BeginObject() {
        PrintDeliminator();
        return JSONObject<JSONArray<Owner>>(out, *this);
    }

    Owner &EndArray() {
        closed = true;
        out << "]";
        return parent;
    }

    ~JSONArray() {
        if (!closed) {
            closed = true;
            out << "]";
        }
    }

private:
    void PrintDeliminator() {
        if (first_comma) {
            out << ",";
        } else {
            first_comma = true;
        }
    }

    std::ostream &out;
    Owner &parent;
    bool closed = false;
    bool first_comma = false;
};

template<typename Owner>
class JSONKeyValue {
public:
    JSONKeyValue(std::ostream &out, Owner &parent) : out(out), parent(parent) {}

    Owner &Number(int64_t value) {
        closed = true;
        PrintJsonInt(out, value);
        return parent;
    }

    Owner &String(std::string_view value) {
        closed = true;
        PrintJsonString(out, value);
        return parent;
    }

    Owner &Boolean(bool value) {
        closed = true;
        PrintJsonBool(out, value);
        return parent;
    }

    Owner &Null() {
        closed = true;
        PrintNull(out);
        return parent;
    }

    auto BeginArray() {
        closed = true;
        return JSONArray(out, parent);
    }

    auto BeginObject() {
        closed = true;
        return JSONObject(out, parent);
    }

    ~JSONKeyValue() {
        if (!closed) {
            closed = true;
            PrintNull(out);
        }
    }

private:
    std::ostream &out;
    Owner &parent;
    bool closed = false;
};

template<typename Owner>
class JSONObject {
public:
    JSONObject(std::ostream &out, Owner &parent) : out(out), parent(parent) {
        out << "{";
    }

    auto Key(std::string_view key) {
        PrintDeliminator();
        PrintJsonString(out, key);
        out << ":";
        return JSONKeyValue<JSONObject<Owner>>(out, *this);
    }

    Owner &EndObject() {
        closed = true;
        out << "}";
        return parent;
    }

    ~JSONObject() {
        if (!closed) {
            closed = true;
            out << "}";
        }
    }

private:
    void PrintDeliminator() {
        if (first_comma) {
            out << ",";
        } else {
            first_comma = true;
        }
    }

    std::ostream &out;
    Owner &parent;
    bool closed = false;
    bool first_comma = false;
};


class EmptyContext {
public:
    EmptyContext() = default;
};

using ArrayContext = JSONArray<EmptyContext>;  // Замените это объявление на определение типа ArrayContext
ArrayContext PrintJsonArray(std::ostream &out) {
    EmptyContext emptyContext;
    return JSONArray<EmptyContext> (out, emptyContext);
}

using ObjectContext = JSONObject<EmptyContext>;  // Замените это объявление на определение типа ObjectContext
ObjectContext PrintJsonObject(std::ostream &out) {
    EmptyContext emptyContext;
    return JSONObject<EmptyContext> (out, emptyContext);
}

void TestArray() {
    std::ostringstream output;

    {
        auto json = PrintJsonArray(output);
        json
                .Number(5)
                .Number(6)
                .BeginArray()
                .Number(7)
                .EndArray()
                .Number(8)
                .String("bingo!");
    }

    ASSERT_EQUAL(output.str(), R"([5,6,[7],8,"bingo!"])");
}

void TestObject() {
    std::ostringstream output;

    {
        auto json = PrintJsonObject(output);
        json
                .Key("id1").Number(1234)
                .Key("id2").Boolean(false)
                .Key("").Null()
                .Key("\"").String("\\");
    }

    ASSERT_EQUAL(output.str(), R"({"id1":1234,"id2":false,"":null,"\"":"\\"})");
}

void TestAutoClose() {
    std::ostringstream output;

    {
        auto json = PrintJsonArray(output);
        json.BeginArray().BeginObject();
    }

    ASSERT_EQUAL(output.str(), R"([[{}]])");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestArray);
    RUN_TEST(tr, TestObject);
    RUN_TEST(tr, TestAutoClose);

    return 0;
}
