#include <string>
#include <list>
#include "test_runner.h"

using namespace std;

class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() {
        pos = l.begin();
    }

    void Left() {
        if (pos != l.begin()) {
            pos--;
        }
    }

    void Right() {
        if (pos != l.end()) {
            pos++;
        }
    }

    void Insert(char token) {
        l.insert(pos, token);
    }

    void Cut(size_t tokens = 1) {
        buffer.clear();
        if (distance(pos, end(l)) < tokens) {
            tokens = distance(pos, end(l));
        }
        auto new_pos = next(pos, tokens);
        l.splice(begin(buffer), buffer, pos, next(pos, tokens));
        pos = new_pos;
    }

    void Copy(size_t tokens = 1) {
        buffer.clear();
        if (distance(pos, end(l)) < tokens) {
            tokens = distance(pos, end(l));
        }
        buffer = list<char>(pos, next(pos, tokens));
    }

    void Paste() {
        l.insert(pos, begin(buffer), end(buffer));
    }

    string GetText() const {
        string ans;
        for (auto c:l) {
            ans += c;
        }
        return ans;
    }

private:
    list<char>::iterator pos;
    list<char> l;
    list<char> buffer;
};

void TypeText(Editor &editor, const string &text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}