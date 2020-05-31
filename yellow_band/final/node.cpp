#include "node.h"

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    return compare(date, d, cmp);
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date &d) : cmp(cmp), d(d) {}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string &e) : cmp(cmp), e(e) {}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    return compare(event, e, cmp);
}

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return true;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    if (logicalOperation == LogicalOperation::And) {
        return left->Evaluate(date, event) && right->Evaluate(date, event);
    } else {
        return left->Evaluate(date, event) || right->Evaluate(date, event);
    }
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logicalOperation, const shared_ptr<Node> &left,
                                           const shared_ptr<Node> &right) : logicalOperation(logicalOperation),
                                                                            left(left), right(right) {}
