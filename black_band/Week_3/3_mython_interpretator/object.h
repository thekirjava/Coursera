#pragma once

#include "object_holder.h"

#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Ast {
    class Statement;
}

class TestRunner;

namespace Runtime {

    class Object {
    public:
        virtual ~Object() = default;

        virtual void Print(std::ostream &os) = 0;

        virtual bool IsTrue() const = 0;
    };

    template<typename T>
    class ValueObject : public Object {
    public:
        ValueObject(T v) : value(v) {
        }

        void Print(std::ostream &os) override {
            os << value;
        }

        const T &GetValue() const {
            return value;
        }

        bool IsTrue() const override {
            return false;
        }

    protected:
        T value;
    };

    class String : public ValueObject<std::string> {
        using ValueObject<std::string>::ValueObject;

    public:
        bool IsTrue() const override {
            return !value.empty();
        }
    };

    class Number : public ValueObject<int> {
    public:
        using ValueObject<int>::ValueObject;

    public:
        bool IsTrue() const override {
            return value != 0;
        }
    };


    class Bool : public ValueObject<bool> {
    public:
        using ValueObject<bool>::ValueObject;

        void Print(std::ostream &os) override;

        bool IsTrue() const override {
            return value;
        }
    };

    struct Method {
        std::string name;
        std::vector<std::string> formal_params;
        std::unique_ptr<Ast::Statement> body;
    };

    class Class : public Object {
    public:
        explicit Class(std::string name, std::vector<Method> methods, const Class *parent);

        const Method *GetMethod(const std::string &name) const;

        const std::string &GetName() const;

        void Print(std::ostream &os) override;

        bool IsTrue() const override {
            return true;
        }

    private:
        const std::string name_;
        std::unique_ptr<std::unordered_map<std::string, Method> > methods_;
        const Class *parent_ = nullptr;
    };

    class ClassInstance : public Object {
    public:
        explicit ClassInstance(const Class &cls);

        void Print(std::ostream &os) override;

        ObjectHolder Call(const std::string &method, const std::vector<ObjectHolder> &actual_args);

        bool HasMethod(const std::string &method, size_t argument_count) const;

        Closure &Fields();

        const Closure &Fields() const;

        bool IsTrue() const override {
            return true;
        }

        std::string GetClassName() const {
            return class_.GetName();
        }

    private:
        const Class &class_;
        Closure fields_;
    };

    void RunObjectsTests(TestRunner &test_runner);

}
