#include "statement.h"
#include "object.h"

#include <iostream>
#include <sstream>
#include <utility>

using namespace std;

namespace Ast {

    using Runtime::Closure;

    ObjectHolder Assignment::Execute(Closure &closure) {
        const auto &new_value = right_value->Execute(closure);
        closure[var_name] = new_value;
        return new_value;
    }

    Assignment::Assignment(std::string var, std::unique_ptr<Statement> rv) {
        var_name = move(var);
        right_value = move(rv);
    }

    VariableValue::VariableValue(std::string var_name) {
        dotted_ids.push_back(move(var_name));
    }

    VariableValue::VariableValue(std::vector<std::string> dotted_ids) : dotted_ids(move(dotted_ids)) {
    }

    ObjectHolder VariableValue::Execute(Closure &closure) {
        return ExecuteChain(closure, 0);
    }

    ObjectHolder VariableValue::ExecuteChain(Closure &closure, size_t index) {
        if (closure.find(dotted_ids[index]) == closure.end())
            throw runtime_error("No such variable!");

        if (index + 1 == dotted_ids.size()) {
            return closure[dotted_ids[index]];
        } else {
            return ExecuteChain(
                    closure[dotted_ids[index]].TryAs<Runtime::ClassInstance>()->Fields(), index + 1
            );
        }
    }

    unique_ptr<Print> Print::Variable(std::string var) {
        return make_unique<Print>(
                make_unique<VariableValue>(move(var))
        );
    }

    Print::Print(unique_ptr<Statement> argument) {
        args.push_back(move(argument));
    }

    Print::Print(vector<unique_ptr<Statement>> args) : args(move(args)) {
    }

    ObjectHolder Print::Execute(Closure &closure) {
        if (output) {
            bool first_ = true;
            for (auto &statement : args) {
                if (first_) {
                    ObjectHolder object = statement->Execute(closure);
                    if (object) {
                        object->Print(*output);
                    } else {
                        *output << "None";
                    }
                    first_ = false;
                } else {
                    *output << ' ';
                    ObjectHolder object = statement->Execute(closure);
                    if (object) {
                        object->Print(*output);
                    } else {
                        *output << "None";
                    }
                }
            }
            *output << '\n';
        }

        return Runtime::ObjectHolder::None();
    }

    ostream *Print::output = &cout;

    void Print::SetOutputStream(ostream &output_stream) {
        output = &output_stream;
    }

    MethodCall::MethodCall(
            std::unique_ptr<Statement> object, std::string method, std::vector<std::unique_ptr<Statement>> args
    ) : object(move(object)), method(move(method)), args(move(args)) {
    }

    ObjectHolder MethodCall::Execute(Closure &closure) {
        std::vector<ObjectHolder> actual_args;
        for (const auto &arg : args) {
            actual_args.push_back(arg->Execute(closure));
        }

        auto *class_instance = object->Execute(closure).TryAs<Runtime::ClassInstance>();

        if (class_instance) {
            if (class_instance->HasMethod(method, actual_args.size())) {
                return class_instance->Call(method, actual_args);
            }
        }

        throw runtime_error("Bad Method call: " + method);
    }

    optional<ObjectHolder> BinaryOperation::executeClass(Runtime::ClassInstance *lhs, const Runtime::ObjectHolder &rhs,
                                                         const std::string &operation) {
        if (lhs->HasMethod(operation, 1)) {
            return lhs->Call(operation, {rhs});
        }
        return nullopt;
    }

    ObjectHolder Stringify::Execute(Closure &closure) {
        ostringstream out;
        argument->Execute(closure)->Print(out);
        return ObjectHolder::Own(Runtime::String(out.str()));
    }

    ObjectHolder Add::Execute(Closure &closure) {
        ObjectHolder leftHolder = lhs_->Execute(closure);
        ObjectHolder rightHolder = rhs_->Execute(closure);
        if ((leftHolder.TryAs<Runtime::Number>()) && (rightHolder.TryAs<Runtime::Number>())) {
            return ObjectHolder::Own(Runtime::Number(leftHolder.TryAs<Runtime::Number>()->GetValue() +
                                                     rightHolder.TryAs<Runtime::Number>()->GetValue()));
        }
        if ((leftHolder.TryAs<Runtime::String>()) && (rightHolder.TryAs<Runtime::String>())) {
            return ObjectHolder::Own(Runtime::String(leftHolder.TryAs<Runtime::String>()->GetValue() +
                                                     rightHolder.TryAs<Runtime::String>()->GetValue()));
        }
        if (leftHolder.TryAs<Runtime::ClassInstance>()) {
            const auto result = executeClass(leftHolder.TryAs<Runtime::ClassInstance>(), rightHolder, "__add__");
            if (result.has_value()) {
                return result.value();
            }
        }
        throw runtime_error("Bad addition");
    }

    ObjectHolder Sub::Execute(Closure &closure) {
        ObjectHolder leftHolder = lhs_->Execute(closure);
        ObjectHolder rightHolder = rhs_->Execute(closure);
        if ((leftHolder.TryAs<Runtime::Number>()) && (rightHolder.TryAs<Runtime::Number>())) {
            return ObjectHolder::Own(Runtime::Number(leftHolder.TryAs<Runtime::Number>()->GetValue() -
                                                     rightHolder.TryAs<Runtime::Number>()->GetValue()));
        }
        if (leftHolder.TryAs<Runtime::ClassInstance>()) {
            const auto result = executeClass(leftHolder.TryAs<Runtime::ClassInstance>(), rightHolder, "__sub__");
            if (result.has_value()) {
                return result.value();
            }
        }
        throw runtime_error("Bad subtraction");
    }

    ObjectHolder Mult::Execute(Runtime::Closure &closure) {
        ObjectHolder leftHolder = lhs_->Execute(closure);
        ObjectHolder rightHolder = rhs_->Execute(closure);
        if ((leftHolder.TryAs<Runtime::Number>()) && (rightHolder.TryAs<Runtime::Number>())) {
            return ObjectHolder::Own(Runtime::Number(leftHolder.TryAs<Runtime::Number>()->GetValue() *
                                                     rightHolder.TryAs<Runtime::Number>()->GetValue()));
        }
        if (leftHolder.TryAs<Runtime::ClassInstance>()) {
            const auto result = executeClass(leftHolder.TryAs<Runtime::ClassInstance>(), rightHolder, "__mul__");
            if (result.has_value()) {
                return result.value();
            }
        }
        throw runtime_error("Bad multiplication");
    }

    ObjectHolder Div::Execute(Runtime::Closure &closure) {
        ObjectHolder leftHolder = lhs_->Execute(closure);
        ObjectHolder rightHolder = rhs_->Execute(closure);
        if ((leftHolder.TryAs<Runtime::Number>()) && (rightHolder.TryAs<Runtime::Number>())) {
            if (rightHolder.TryAs<Runtime::Number>()->GetValue()==0) {
                throw runtime_error("Zero division");
            }
            return ObjectHolder::Own(Runtime::Number(leftHolder.TryAs<Runtime::Number>()->GetValue() /
                                                     rightHolder.TryAs<Runtime::Number>()->GetValue()));
        }
        if (leftHolder.TryAs<Runtime::ClassInstance>()) {
            const auto result = executeClass(leftHolder.TryAs<Runtime::ClassInstance>(), rightHolder, "__div__");
            if (result.has_value()) {
                return result.value();
            }
        }
        throw runtime_error("Bad division");
    }

    ObjectHolder Compound::Execute(Closure &closure) {
        for (auto& statement : statements) {
            if (dynamic_cast<Return*>(statement.get()))
                return statement->Execute(closure);

            if (
                    dynamic_cast<IfElse*>(statement.get()) ||
                    dynamic_cast<MethodCall*>(statement.get())
                    ) {
                ObjectHolder result = statement->Execute(closure);
                if (result) {
                    return result;
                }
            } else {
                statement->Execute(closure);
            }
        }

        return Runtime::ObjectHolder::None();
    }

    ObjectHolder Return::Execute(Closure &closure) {
        return statement->Execute(closure);
    }

    ClassDefinition::ClassDefinition(ObjectHolder class_):cls(move(class_)), class_name(cls.TryAs<Runtime::Class>()->GetName()) {
    }

    ObjectHolder ClassDefinition::Execute(Runtime::Closure &closure) {
        closure[class_name] = cls;
        return ObjectHolder::None();
    }

    FieldAssignment::FieldAssignment(
            VariableValue object, std::string field_name, std::unique_ptr<Statement> rv
    )
            : object(std::move(object)), field_name(std::move(field_name)), right_value(std::move(rv)) {
    }

    ObjectHolder FieldAssignment::Execute(Runtime::Closure &closure) {
        ObjectHolder& field = object.Execute(closure).TryAs<Runtime::ClassInstance>()->Fields()[field_name];
        field = right_value->Execute(closure);
        return field;
    }


    IfElse::IfElse(
            std::unique_ptr<Statement> condition,
            std::unique_ptr<Statement> if_body,
            std::unique_ptr<Statement> else_body
    ):condition_(move(condition)), if_body(move(if_body)), else_body(move(else_body)) {
    }

    ObjectHolder IfElse::Execute(Runtime::Closure &closure) {
        ObjectHolder condition = condition_->Execute(closure);
        if (condition) {
            if (condition.Get()->IsTrue()) {
                if (if_body) {
                    return if_body->Execute(closure);
                }
            } else {
                if (else_body) {
                    return else_body->Execute(closure);
                }
            }
        } else {
            if (else_body) {
                return else_body->Execute(closure);
            }
        }
        return ObjectHolder::None();
    }

    ObjectHolder Or::Execute(Runtime::Closure &closure) {
        ObjectHolder leftHolder = lhs_->Execute(closure);
        ObjectHolder rightHolder = rhs_->Execute(closure);
        if (!leftHolder) {
            leftHolder = ObjectHolder::Own(Runtime::Bool(false));
        }
        if (!rightHolder) {
            rightHolder = ObjectHolder::Own(Runtime::Bool(false));
        }
        return ObjectHolder::Own(Runtime::Bool(leftHolder->IsTrue() || rightHolder->IsTrue()));
    }

    ObjectHolder And::Execute(Runtime::Closure &closure) {
        ObjectHolder leftHolder = lhs_->Execute(closure);
        ObjectHolder rightHolder = rhs_->Execute(closure);
        if (!leftHolder) {
            leftHolder = ObjectHolder::Own(Runtime::Bool(false));
        }
        if (!rightHolder) {
            rightHolder = ObjectHolder::Own(Runtime::Bool(false));
        }
        return ObjectHolder::Own(Runtime::Bool(leftHolder->IsTrue() && rightHolder->IsTrue()));
    }

    ObjectHolder Not::Execute(Runtime::Closure &closure) {
        ObjectHolder argumentHolder = argument->Execute(closure);
        if (!argumentHolder) {
            argumentHolder = ObjectHolder::Own(Runtime::Bool(false));
        }
        return ObjectHolder::Own(Runtime::Bool(!argumentHolder->IsTrue()));
    }

    Comparison::Comparison(
            Comparator cmp, unique_ptr<Statement> lhs, unique_ptr<Statement> rhs
    ):comparator(move(cmp)), left(move(lhs)), right(move(rhs)) {
    }

    ObjectHolder Comparison::Execute(Runtime::Closure &closure) {
        return ObjectHolder::Own(Runtime::Bool(comparator(left->Execute(closure), right->Execute(closure))));
    }

    NewInstance::NewInstance(
            const Runtime::Class &class_, std::vector<std::unique_ptr<Statement>> args
    )
            : class_(class_), args(std::move(args)) {
    }

    NewInstance::NewInstance(const Runtime::Class &class_) : NewInstance(class_, {}) {
    }

    ObjectHolder NewInstance::Execute(Runtime::Closure &closure) {
        auto* new_instance = new Runtime::ClassInstance(class_);
        if (new_instance->HasMethod("__init__", args.size())) {
            vector<ObjectHolder> actual_args;
            for(const auto& statement:args) {
                actual_args.push_back(statement->Execute(closure));
            }
            new_instance->Call("__init__", actual_args);
        }
        return ObjectHolder::Share(*new_instance);
    }


} /* namespace Ast */
