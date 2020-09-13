#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stack>

using namespace std;


struct Email {
    Email() = default;

    Email(string from, string to, string body) : from(move(from)), to(move(to)), body(move(body)) {}

    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;

    virtual void Process(unique_ptr<Email> email) = 0;

    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (nextWorker != nullptr) {
            nextWorker->Process(move(email));
        }
    }

    unique_ptr<Worker> nextWorker;
public:
    void SetNext(unique_ptr<Worker> next) {
        nextWorker = move(next);
    }
};


class Reader : public Worker {
public:
    explicit Reader(istream &input) : input(input) {}

    void Run() override {
        string from, to, body;
        while (input) {
            getline(input, from);
            getline(input, to);
            getline(input, body);
            if (input) {
                PassOn(make_unique<Email>(from, to, body));
            }
        }
    }

    void Process(unique_ptr<Email> email) override {
        throw logic_error("Unimplemented");
    }

private:
    istream &input;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email &)>;

public:
    explicit Filter(Function function) : predicate(function) {}

    void Process(unique_ptr<Email> email) override {
        if (predicate(*email)) {
            PassOn(move(email));
        }
    }

private:
    Function predicate;
};


class Copier : public Worker {
public:
    explicit Copier(string address) : address(address) {}

    void Process(unique_ptr<Email> email) override {
        if (email->to != address) {
            auto ret = make_unique<Email>(email->from, address, email->body);
            PassOn(move(email));
            PassOn(move(ret));
        } else {
            PassOn(move(email));
        }
    }

private:
    string address;
};


class Sender : public Worker {
public:
    explicit Sender(ostream &output) : output(output) {}

    void Process(unique_ptr<Email> email) override {
        output << email->from << endl << email->to << endl << email->body << endl;
        PassOn(move(email));
    }

private:
    ostream &output;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream &in) {
        builder.push(make_unique<Reader>(in));
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter) {
        builder.push(make_unique<Filter>(filter));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(string recipient) {
        builder.push(make_unique<Copier>(recipient));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder &Send(ostream &out) {
        builder.push(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        while (builder.size() > 1) {
            auto buf = move(builder.top());
            builder.pop();
            builder.top()->SetNext(move(buf));
        }
        auto buf = move(builder.top());
        builder.pop();
        return move(buf);
    }

private:
    stack<unique_ptr<Worker> > builder;
};


void TestSanity() {
    string input = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "ralph@example.com\n"
            "erich@example.com\n"
            "I do not make mistakes of that kind\n"
    );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "erich@example.com\n"
            "richard@example.com\n"
            "Are you sure you pressed the right button?\n"
    );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
