#include "lexer.h"

#include <algorithm>
#include <charconv>
#include <unordered_map>

using namespace std;

namespace Parse {

    bool operator==(const Token &lhs, const Token &rhs) {
        using namespace TokenType;

        if (lhs.index() != rhs.index()) {
            return false;
        }
        if (lhs.Is<Char>()) {
            return lhs.As<Char>().value == rhs.As<Char>().value;
        } else if (lhs.Is<Number>()) {
            return lhs.As<Number>().value == rhs.As<Number>().value;
        } else if (lhs.Is<String>()) {
            return lhs.As<String>().value == rhs.As<String>().value;
        } else if (lhs.Is<Id>()) {
            return lhs.As<Id>().value == rhs.As<Id>().value;
        } else {
            return true;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Token &rhs) {
        using namespace TokenType;

#define VALUED_OUTPUT(type) \
  if (auto p = rhs.TryAs<type>()) return os << #type << '{' << p->value << '}';

        VALUED_OUTPUT(Number);
        VALUED_OUTPUT(Id);
        VALUED_OUTPUT(String);
        VALUED_OUTPUT(Char);

#undef VALUED_OUTPUT

#define UNVALUED_OUTPUT(type) \
    if (rhs.Is<type>()) return os << #type;

        UNVALUED_OUTPUT(Class);
        UNVALUED_OUTPUT(Return);
        UNVALUED_OUTPUT(If);
        UNVALUED_OUTPUT(Else);
        UNVALUED_OUTPUT(Def);
        UNVALUED_OUTPUT(Newline);
        UNVALUED_OUTPUT(Print);
        UNVALUED_OUTPUT(Indent);
        UNVALUED_OUTPUT(Dedent);
        UNVALUED_OUTPUT(And);
        UNVALUED_OUTPUT(Or);
        UNVALUED_OUTPUT(Not);
        UNVALUED_OUTPUT(Eq);
        UNVALUED_OUTPUT(NotEq);
        UNVALUED_OUTPUT(LessOrEq);
        UNVALUED_OUTPUT(GreaterOrEq);
        UNVALUED_OUTPUT(None);
        UNVALUED_OUTPUT(True);
        UNVALUED_OUTPUT(False);
        UNVALUED_OUTPUT(Eof);

#undef UNVALUED_OUTPUT

        return os << "Unknown token :(";
    }


    const Token &Lexer::CurrentToken() const {
        return token;
    }

    Token Lexer::NextToken() {
        char c = in.get();
        if (c == -1) {
            if ((!token.Is<TokenType::Newline>()) && (!token.Is<TokenType::Dedent>()) && (firstNewLine)) {
                firstNewLine = false;
                token = TokenType::Newline();
                return TokenType::Newline();
            }
            firstNewLine = false;
            if (current_indent > 0) {
                current_indent--;
                token = TokenType::Dedent();
                return TokenType::Dedent();
            }
            token = TokenType::Eof();
            return TokenType::Eof();
        }
        while ((isNewLine) && (c == '\n')) {
            c = in.get();
        }
        if (c == '\n') {
            isNewLine = true;
            token = TokenType::Newline();
            return TokenType::Newline();
        }
        if (isNewLine) {
            isNewLine = false;
            int space_counter = 0;
            while (c == ' ') {
                space_counter++;
                c = in.get();
            }
            if (current_indent * 2 < space_counter) {
                in.putback(c);
                current_indent++;
                token = TokenType::Indent();
                return TokenType::Indent();
            } else if (current_indent * 2 > space_counter) {
                in.putback(c);
                current_indent--;
                for (int i = 0; i < space_counter; i++) {
                    in.putback(' ');
                }
                isNewLine = true;
                token = TokenType::Dedent();
                return TokenType::Dedent();
            }
        }
        while (c == ' ') {
            in.get(c);
        }
        if ((c == '\'') || (c == '\"')) {
            std::string ans;
            char cur = in.get();
            while (cur != c) {
                ans += cur;
                cur = in.get();
            }
            token = TokenType::String({ans});
            return TokenType::String({ans});
        }
        if ((c >= '0') && (c <= '9')) {
            int ans = c - '0';
            c = in.get();
            while ((c >= '0') && (c <= '9')) {
                ans *= 10;
                ans += c - '0';
                c = in.get();
            }
            in.putback(c);
            token = TokenType::Number({ans});
            return TokenType::Number({ans});
        }
        string cmd;
        bool back = false;
        while (((std::isalnum(c)) || (c == '_')) && (!in.eof())) {
            cmd += c;
            c = in.get();
            back = true;
        }

        if (back) {
            in.putback(c);
        } else if (((c == '<') || (c == '>') || (c == '!') || (c == '=')) && (in.peek() == '=')) {
            cmd += c;
            c = in.get();
            cmd += c;
        }
        if (cmd.empty()) {
            token = TokenType::Char({c});
            return TokenType::Char({c});
        } else if (cmd == "class") {
            token = TokenType::Class();
            return TokenType::Class();
        } else if (cmd == "return") {
            token = TokenType::Return();
            return TokenType::Return();
        } else if (cmd == "if") {
            token = TokenType::If();
            return TokenType::If();
        } else if (cmd == "else") {
            token = TokenType::Else();
            return TokenType::Else();
        } else if (cmd == "def") {
            token = TokenType::Def();
            return TokenType::Def();
        } else if (cmd == "print") {
            token = TokenType::Print();
            return TokenType::Print();
        } else if (cmd == "and") {
            token = TokenType::And();
            return TokenType::And();
        } else if (cmd == "or") {
            token = TokenType::Or();
            return TokenType::Or();
        } else if (cmd == "not") {
            token = TokenType::Not();
            return TokenType::Not();
        } else if (cmd == "==") {
            token = TokenType::Eq();
            return TokenType::Eq();
        } else if (cmd == "!=") {
            token = TokenType::NotEq();
            return TokenType::NotEq();
        } else if (cmd == "<=") {
            token = TokenType::LessOrEq();
            return TokenType::LessOrEq();
        } else if (cmd == ">=") {
            token = TokenType::GreaterOrEq();
            return TokenType::GreaterOrEq();
        } else if (cmd == "None") {
            token = TokenType::None();
            return TokenType::None();
        } else if (cmd == "True") {
            token = TokenType::True();
            return TokenType::True();
        } else if (cmd == "False") {
            token = TokenType::False();
            return TokenType::False();
        } else {
            token = TokenType::Id({cmd});
            return TokenType::Id({cmd});
        }
    }

} /* namespace Parse */