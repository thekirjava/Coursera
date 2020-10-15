#pragma once

#include <iostream>
#include <cstdint>
#include <variant>
#include <string>
#include <vector>
#include <optional>
#include <list>
#include <memory>

namespace Svg {
    struct Point {
        Point() : x(0.0), y(0.0) {}

        Point(double x, double y) : x(x), y(y) {}

        friend std::ostream &operator<<(std::ostream &out, Point p) {
            out << p.x << ',' << p.y;
            return out;
        }

        double x, y;
    };

    struct Rgb {
        Rgb() : red(0), green(0), blue(0) {}

        Rgb(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {}

        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    class Color {
    public:
        Color() : color("none") {}

        Color(const std::string &color) : color(color) {}

        Color(const char *color) : color(color) {}

        Color(const Rgb &colorRgb) {
            color = "rgb(" + std::to_string(colorRgb.red) + "," + std::to_string(colorRgb.green) + "," +
                    std::to_string(colorRgb.blue) + ")";
        }

        Color &operator=(const std::string &other) {
            color = other;
            return *this;
        }

        Color &operator=(const Rgb &other) {
            color = "rgb(" + std::to_string(other.red) + "," + std::to_string(other.blue) + "," +
                    std::to_string(other.green) + ")";
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &out, const Color &c) {
            out << c.color;
            return out;
        }

    private:
        std::string color;
    };

    const Color NoneColor = Color();

    class Figure {
    public:
        Figure() = default;

        Figure(const Figure &other) = default;

        Figure(Figure &&other) noexcept = default;

        Figure &operator=(const Figure &other) = default;

        Figure &operator=(Figure &&other) noexcept = default;

        Figure &SetFillColor(const Color &fill);

        Figure &SetStrokeColor(const Color &stroke);

        Figure &SetStrokeWidth(double width);

        Figure &SetStrokeLineCap(const std::string &lineCap);

        Figure &SetStrokeLineJoin(const std::string &lineJoin);

        friend std::ostream &operator<<(std::ostream &out, const Figure &figure) {
            figure.Print(out);
            return out;
        }

        virtual ~Figure() = default;

    private:
        virtual std::ostream &Print(std::ostream &out) const;
        Color fillColor = NoneColor;
        Color strokeColor = NoneColor;
        double strokeWidth = 1.0;
        std::optional<std::string> strokeLineCap;
        std::optional<std::string> strokeLineJoin;
    };

    template<typename Derived>
    class FigureProperties : public Figure {
    public:
        Derived &SetFillColor(const Color &fill) &{
            return static_cast<Derived &>(Figure::SetFillColor(fill));
        }

        Derived &SetStrokeColor(const Color &stroke) &{
            return static_cast<Derived &>(Figure::SetStrokeColor(stroke));
        }

        Derived &SetStrokeWidth(double width) &{
            return static_cast<Derived &>(Figure::SetStrokeWidth(width));
        }

        Derived &SetStrokeLineCap(const std::string &lineCap) &{
            return static_cast<Derived &>(Figure::SetStrokeLineCap(lineCap));
        }

        Derived &SetStrokeLineJoin(const std::string &lineJoin) &{
            return static_cast<Derived &>(Figure::SetStrokeLineJoin(lineJoin));
        }

        Derived &&SetFillColor(const Color &fill) &&{
            return static_cast<Derived &&>(Figure::SetFillColor(fill));
        }

        Derived &&SetStrokeColor(const Color &stroke) &&{
            return static_cast<Derived &&>(Figure::SetStrokeColor(stroke));
        }

        Derived &&SetStrokeWidth(double width) &&{
            return static_cast<Derived &&>(Figure::SetStrokeWidth(width));
        }

        Derived &&SetStrokeLineCap(const std::string &lineCap) &&{
            return static_cast<Derived &&>(Figure::SetStrokeLineCap(lineCap));
        }

        Derived &&SetStrokeLineJoin(const std::string &lineJoin) &&{
            return static_cast<Derived &&>(Figure::SetStrokeLineJoin(lineJoin));
        }
    };

    class Circle : public FigureAdapter<Circle> {
    public:
        Circle() = default;

        Circle(const Circle &other) = default;

        Circle(Circle &&other) noexcept = default;

        Circle &operator=(const Circle &other) = default;

        Circle &operator=(Circle &&other) noexcept = default;

        Circle &SetCenter(Point p);

        Circle &SetRadius(double r);


    private:
        std::ostream &Print(std::ostream &out) const override;

        Point center;
        double radius = 1.0;
    };

    class Polyline : public FigureAdapter<Polyline> {
    public:
        Polyline() = default;

        Polyline(const Polyline &other) = default;

        Polyline(Polyline &&other) noexcept = default;

        Polyline &operator=(const Polyline &other) = default;

        Polyline &operator=(Polyline &&other) noexcept = default;

        Polyline &AddPoint(Point point);


    private:
        std::ostream &Print(std::ostream &out) const override;

        std::list<Point> points;
    };

    class Text : public FigureAdapter<Text> {
    public:
        Text() = default;

        Text(const Text &other) = default;

        Text(Text &&other) noexcept = default;

        Text &operator=(const Text &other) = default;

        Text &operator=(Text &&other) noexcept = default;

        Text &SetPoint(Point p);

        Text &SetOffset(Point offP);

        Text &SetFontSize(uint32_t size);

        Text &SetFontFamily(const std::string &font);

        Text &SetData(const std::string &text);

    private:
        std::ostream &Print(std::ostream &out) const override;

        Point point;
        Point offsetPoint;
        uint32_t fontSize = 1;
        std::optional<std::string> fontFamily;
        std::string data;
    };

    class Document {
    public:
        Document() = default;

        template<typename FigureObject>
        Document &Add(const FigureObject &object) {
            auto ptr = std::make_unique<FigureObject>(object);
            figures.push_back(std::move(ptr));
            return *this;
        }

        void Render(std::ostream &out) const;

    private:
        std::vector<std::unique_ptr<Figure>> figures;
    };
}

