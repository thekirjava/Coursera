#pragma once

#include <string>
#include <memory>
#include "date.h"

using namespace std;
enum Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum LogicalOperation {
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date &date, const string &event) const = 0;

protected:
    template<typename T>
    bool compare(const T &left, const T &right, Comparison cmp) const {
        switch (cmp) {
            case Less:
                return left < right;
            case LessOrEqual:
                return left <= right;
            case Greater:
                return left > right;
            case GreaterOrEqual:
                return left >= right;
            case Equal:
                return left == right;
            case NotEqual:
                return left != right;
        }
    }
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date &d);

    bool Evaluate(const Date &date, const string &event) const override;

private:
    Comparison cmp;
    Date d;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const string &e);

    bool Evaluate(const Date &date, const string &event) const override;

private:
    Comparison cmp;
    string e;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation logicalOperation, const shared_ptr<Node> &left,
                         const shared_ptr<Node> &right);

    bool Evaluate(const Date &date, const string &event) const override;

private:
    LogicalOperation logicalOperation;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date &date, const string &event) const override;
};