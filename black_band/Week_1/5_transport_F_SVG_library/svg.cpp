#include "svg.h"

namespace Svg {
    Figure &Figure::SetFillColor(const Svg::Color &fill) {
        fillColor = fill;
        return *this;
    }

    Figure &Figure::SetStrokeColor(const Color &stroke) {
        strokeColor = stroke;
        return *this;
    }

    Figure &Figure::SetStrokeWidth(double width) {
        strokeWidth = width;
        return *this;
    }

    Figure &Figure::SetStrokeLineCap(const std::string &lineCap) {
        strokeLineCap = lineCap;
        return *this;
    }

    Figure &Figure::SetStrokeLineJoin(const std::string &lineJoin) {
        strokeLineJoin = lineJoin;
        return *this;
    }

    std::ostream &Figure::Print(std::ostream &out) const {
        out << "fill=\"" << this->fillColor << "\" ";
        out << "stroke=\"" << this->strokeColor << "\" ";
        out << "stroke-width=\"" << this->strokeWidth << "\" ";
        if (this->strokeLineCap.has_value()) {
            out << "stroke-linecap=\"" << this->strokeLineCap.value() << "\" ";
        }
        if (this->strokeLineJoin.has_value()) {
            out << "stroke-linejoin=\"" << this->strokeLineJoin.value() << "\" ";
        }
        return out;
    }

    Circle &Circle::SetCenter(Point p) {
        center = p;
        return *this;
    }

    Circle &Circle::SetRadius(double r) {
        radius = r;
        return *this;
    }

    std::ostream &Circle::Print(std::ostream &out) const {
        out << "<circle ";
        out << Figure(*this);
        out << "cx=\"" << this->center.x << "\" ";
        out << "cy=\"" << this->center.y << "\" ";
        out << "r=\"" << this->radius << "\"";
        out << "/>\n";
        return out;
    }

    Polyline &Polyline::AddPoint(Point point) {
        points.push_back(point);
        return *this;
    }

    std::ostream &Polyline::Print(std::ostream &out) const {
        out << "<polyline ";
        out << Figure(*this);
        out << "points=\"";
        for (const auto &p:this->points) {
            out << p << " ";
        }
        out << "\"";
        out << "/>\n";
        return out;
    }

    Text &Text::SetPoint(Point p) {
        point = p;
        return *this;
    }

    Text &Text::SetOffset(Point offP) {
        offsetPoint = offP;
        return *this;
    }

    Text &Text::SetFontSize(uint32_t size) {
        fontSize = size;
        return *this;
    }

    Text &Text::SetFontFamily(const std::string &font) {
        fontFamily = font;
        return *this;
    }

    Text &Text::SetData(const std::string &text) {
        data = text;
        return *this;
    }

    std::ostream &Text::Print(std::ostream &out) const {
        out << "<text ";
        out << Figure(*this);
        out << "x=\"" << this->point.x << "\" ";
        out << "y=\"" << this->point.y << "\" ";
        out << "dx=\"" << this->offsetPoint.x << "\" ";
        out << "dy=\"" << this->offsetPoint.y << "\" ";
        out << "font-size=\"" << this->fontSize << "\" ";
        if (this->fontFamily.has_value()) {
            out << "font-family=\"" << this->fontFamily.value() << "\" ";
        }
        out << ">";
        out << this->data;
        out << "</text>\n";
        return out;
    }

    void Document::Render(std::ostream &out) const {
        out << R"(<?xml version="1.0" encoding="UTF-8" ?>)" << '\n' <<
            R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)" << '\n';
        for (const auto &ptr:figures) {
            out << *ptr;
        }
        out << "</svg>\n";
    }
}
