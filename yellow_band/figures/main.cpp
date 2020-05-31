#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() = 0;

    virtual double Perimeter() = 0;

    virtual double Area() = 0;
};

class Rect : public Figure {
public:
    Rect(double w, double h) : width(w), height(h) {}

    string Name() override {
        return "RECT";
    }

    double Perimeter() override {
        return (width + height) * 2;
    }

    double Area() override {
        return width * height;
    }

private:
    double width;
    double height;
};

class Triangle : public Figure {
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    string Name() override {
        return "TRIANGLE";
    }

    double Perimeter() override {
        return a + b + c;
    }

    double Area() override {
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

private:
    double a;
    double b;
    double c;
};

class Circle : public Figure {
public:
    Circle(double radius) : radius(radius) {}

    string Name() override {
        return "CIRCLE";
    }

    double Perimeter() override {
        return PI * radius * 2;
    }

    double Area() override {
        return PI * radius * radius;
    }

private:
    double radius;
    const double PI = 3.14;
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
    string type;
    is >> type;
    if (type == "RECT") {
        double w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    } else if (type == "TRIANGLE") {
        double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (type == "CIRCLE") {
        double r;
        is >> r;
        return make_shared<Circle>(r);
    }
    return nullptr;
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}