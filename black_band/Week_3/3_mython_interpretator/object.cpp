#include "object.h"
#include "statement.h"

#include <sstream>
#include <string_view>

using namespace std;

namespace Runtime {

    void ClassInstance::Print(std::ostream &os) {
        const auto *str_method = class_.GetMethod("__str__");
        if (str_method) {
            str_method->body->Execute(fields_)->Print(os);
        } else {
            os << this;
        }
    }

    bool ClassInstance::HasMethod(const std::string &method, size_t argument_count) const {
        const Method *m = class_.GetMethod(method);
        if (m) {
            return m->formal_params.size() == argument_count;
        } else {
            return false;
        }
    }

    const Closure &ClassInstance::Fields() const {
        return fields_;
    }

    Closure &ClassInstance::Fields() {
        return fields_;
    }

    ClassInstance::ClassInstance(const Class &cls) : class_(cls) {
        fields_["self"] = ObjectHolder::Share(*this);
    }

    ObjectHolder ClassInstance::Call(const std::string &method, const std::vector<ObjectHolder> &actual_args) {
        if (HasMethod(method, actual_args.size())) {
            Closure method_args;
            const Method *method_ = class_.GetMethod(method);
            for (size_t i = 0; i < method_->formal_params.size(); i++) {
                method_args[method_->formal_params[i]] = actual_args[i];
            }
            for (const auto&[field, value]:fields_) {
                method_args[field] = value;
            }
            return method_->body->Execute(method_args);
        } else {
            throw runtime_error("Bad method call " + method);
        }
    }

    Class::Class(std::string name, std::vector<Method> methods, const Class *parent) : name_(move(name)),
                                                                                       parent_(parent) {
        methods_ = make_unique<unordered_map<string, Method>>();
        for (auto &method:methods) {
            (*methods_)[method.name] = move(method);
        }
    }

    const Method *Class::GetMethod(const std::string &name) const {
        const auto finder = methods_->find(name);
        if (finder != methods_->end()) {
            return &finder->second;
        } else if (parent_) {
            return parent_->GetMethod(name);
        } else {
            return nullptr;
        }
    }

    void Class::Print(ostream &os) {
        os << name_;
    }

    const std::string &Class::GetName() const {
        return name_;
    }

    void Bool::Print(std::ostream &os) {
        if (value) {
            os << "True";
        } else {
            os << "False";
        }
    }

} /* namespace Runtime */
