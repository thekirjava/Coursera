#pragma once

#include "sphere.h"
#include "svg.h"
#include "utils.h"
#include <algorithm>
#include <cmath>
#include <optional>
#include <map>

namespace Sphere {

    class Projector {
    public:
        template<typename PointInputIt>
        Projector(PointInputIt points_begin, PointInputIt points_end,
                  double max_width, double max_height, double padding);

        Svg::Point operator()(Point point) const;

    private:
        double min_lon_ = 0;
        double max_lat_ = 0;

        const double height_;
        const double padding_;
        double zoom_coef_ = 0;
        double x_step = 0;
        double y_step = 0;
        std::map<double, size_t> lat_idx;
        std::map<double, size_t> long_idx;
    };


    template<typename PointInputIt>
    Projector::Projector(PointInputIt points_begin, PointInputIt points_end,
                         double max_width, double max_height, double padding)
            :height_(max_height), padding_(padding) {
        if (points_begin == points_end) {
            return;
        }
        std::vector<Point> points(points_begin, points_end);
        std::sort(begin(points), end(points),
                  [](const Point &lhs, const Point &rhs) { return lhs.latitude < rhs.latitude; });
        size_t cur_idx = 0;
        for (size_t i = 0; i < points.size(); i++) {
            lat_idx[points[i].latitude] = i;
        }
        if (points.size() > 1) {
            x_step = (max_width - 2 * padding_) / (points.size() - 1);
        } else {
            x_step = 0;
        }
        std::sort(begin(points), end(points),
                  [](const Point &lhs, const Point &rhs) { return lhs.longitude < rhs.longitude; });
        cur_idx = 0;
        for (size_t i = 0; i < points.size(); i++) {
            long_idx[points[i].longitude] = i;
        }
        if (points.size() > 1) {
            y_step = (max_height - 2 * padding_) / (points.size() - 1);
        } else {
            y_step = 0;
        }
    }

}
