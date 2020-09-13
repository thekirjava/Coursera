#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class ValueNode : public Expression {
public:
    explicit ValueNode(int value) : value(value) {}

    int Evaluate() const override {
        return value;
    }

    std::string ToString() const override {
        return std::to_string(value);
    }

private:
    int value;
};

class SumNode : public Expression {
public:
    SumNode(ExpressionPtr left, ExpressionPtr right) : left(move(left)), right(move(right)) {}

    int Evaluate() const override {
        return left->Evaluate() + right->Evaluate();
    }

    std::string ToString() const override {
        return "(" + left->ToString() + ")+(" + right->ToString() + ")";
    }

private:
    ExpressionPtr left;
    ExpressionPtr right;
};

class ProductNode : public Expression {
public:
    ProductNode(ExpressionPtr left, ExpressionPtr right) : left(move(left)), right(move(right)) {}

    int Evaluate() const override {
        return left->Evaluate() * right->Evaluate();
    }

    std::string ToString() const override {
        return "(" + left->ToString() + ")*(" + right->ToString() + ")";
    }

private:
    ExpressionPtr left;
    ExpressionPtr right;
};

ExpressionPtr Value(int value) {
    return std::make_unique<ValueNode>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<SumNode>(std::move(left), std::move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<ProductNode>(std::move(left), std::move(right));
}

string Print(const Expression *e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}