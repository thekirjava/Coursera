#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <memory>

namespace Svg {

    struct Point {
        double x = 0;
        double y = 0;
    };

    struct Rgb {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    struct Rgba {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        double alpha;
    };

    using Color = std::variant<std::monostate, std::string, Rgb, Rgba>;
    const Color NoneColor{};

    void RenderColor(std::ostream& out, std::monostate);
    void RenderColor(std::ostream& out, const std::string& value);
    void RenderColor(std::ostream& out, Rgb rgb);
    void RenderColor(std::ostream& out, Rgba rgb);
    void RenderColor(std::ostream& out, const Color& color);

    class Figure;
    using SvgFigureHolder = std::unique_ptr<Figure>;
    template <typename FigureType>
    SvgFigureHolder MakeSvgFigure(FigureType figure) {
        return std::make_unique<FigureType>(figure);
    }

    class Figure {
    public:
        virtual void Render(std::ostream& out) const = 0;
        virtual ~Figure() = default;
    };

    template <typename Owner>
    class PathProps {
    public:
        Owner& SetFillColor(const Color& color) {
            fill_color_ = color;
            return AsOwner();
        }

        Owner& SetStrokeColor(const Color& color) {
            stroke_color_ = color;
            return AsOwner();
        }

        Owner& SetStrokeWidth(double value) {
            stroke_width_ = value;
            return AsOwner();
        }

        Owner& SetStrokeLineCap(const std::string& value) {
            stroke_line_cap_ = value;
            return AsOwner();
        }

        Owner& SetStrokeLineJoin(const std::string& value) {
            stroke_line_join_ = value;
            return AsOwner();
        }

        void RenderAttrs(std::ostream& out) const {
            out << R"(fill=\")";
            RenderColor(out, fill_color_);
            out << R"(\" )";
            out << R"(stroke=\")";
            RenderColor(out, stroke_color_);
            out << R"(\" )";
            out << R"(stroke-width=\")" << stroke_width_ << R"(\" )";
            if (stroke_line_cap_) {
                out << R"(stroke-linecap=\")" << *stroke_line_cap_ << R"(\" )";
            }
            if (stroke_line_join_) {
                out << R"(stroke-linejoin=\")" << *stroke_line_join_ << R"(\" )";
            }
        }

    private:
        Color fill_color_;
        Color stroke_color_;
        double stroke_width_ = 1.0;
        std::optional<std::string> stroke_line_cap_;
        std::optional<std::string> stroke_line_join_;

        Owner& AsOwner() {
            return static_cast<Owner&>(*this);
        }

    };

    class Circle : public Figure, public PathProps<Circle> {
    public:
        Circle& SetCenter(Point point);
        Circle& SetRadius(double radius);
        void Render(std::ostream& out) const override;
    private:
        Point center_;
        double radius_ = 1;
    };

    class Polyline : public Figure, public PathProps<Polyline> {
    public:
        Polyline& AddPoint(Point point);
        void Render(std::ostream& out) const override;
    private:
        std::vector<Point> points_;
    };

    class Text : public Figure, public PathProps<Text> {
    public:
        Text& SetPoint(Point point);
        Text& SetOffset(Point point);
        Text& SetFontSize(uint32_t size);
        Text&SetFontFamily(const std::string& value);
        Text& SetData(const std::string& data);
        void Render(std::ostream& out) const override;

    private:
        Point point_;
        Point offset_;
        uint32_t font_size_ = 1;
        std::optional<std::string> font_family_;
        std::string data_;
    };
    class Document : public Figure {
    public:
        template <typename ObjectType>
        void Add(ObjectType object) {
            objects_.push_back(std::make_unique<ObjectType>(object));
        }
        template <typename ObjectPtr>
        void AddDocumentPart(ObjectPtr object) {
            objects_.push_back(std::move(object));
        }
        void Render(std::ostream& out) const override;
        void Clear();
    private:
        std::vector<SvgFigureHolder> objects_;
    };

}