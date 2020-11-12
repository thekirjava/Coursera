#pragma once

#include <cmath>

namespace Sphere {
    double ConvertDegreesToRadians(double degrees);

    struct Point {
        double latitude;
        double longitude;

        static Point FromDegrees(double latitude, double longitude);

        bool operator!=(const Point &other) const {
            return (this->longitude != other.longitude) || (this->latitude != other.latitude);
        }

        bool operator<(const Point &other) const {
            return (this->latitude <= other.latitude) && (this->longitude < other.longitude);
        }
    };

    double Distance(Point lhs, Point rhs);
}
