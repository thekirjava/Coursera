#pragma once

#include "descriptions.h"
#include "sphere.h"
#include "svg.h"
#include "utils.h"
#include <algorithm>
#include <cmath>
#include <optional>
#include <map>
#include <fstream>

namespace Sphere {

    class Projector {
    public:
        template<typename StopInputIt, typename BusInputIt>
        Projector(StopInputIt stops_begin, StopInputIt stops_end,
                  BusInputIt buses_begin, BusInputIt buses_end,
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


    template<typename StopInputIt, typename BusInputIt>
    Projector::Projector(StopInputIt stops_begin, StopInputIt stops_end, BusInputIt buses_begin, BusInputIt buses_end,
                         double max_width, double max_height, double padding)
            :height_(max_height), padding_(padding) {
        std::ofstream ferr("test.txt");
        if (stops_begin == stops_end) {
            return;
        }
        std::vector<Descriptions::Stop> stops(stops_begin, stops_end);
        std::vector<Descriptions::Bus> buses(buses_begin, buses_end);
        std::sort(begin(stops), end(stops), [](
                const Descriptions::Stop &lhs,
                const Descriptions::Stop &rhs) { return lhs.position.longitude < rhs.position.longitude; });
        size_t cur_idx = 0;
        for (int i = 0; i < stops.size(); i++) {
            bool neighbor = false;
            for (int j = i - 1; j >= 0 && (long_idx[stops[j].position.longitude] == cur_idx); j--) {
                neighbor = neighbor || isNeighbors(stops[i], stops[j], buses);
            }
            if (neighbor) {
                cur_idx++;
            }
            long_idx[stops[i].position.longitude] = cur_idx;
            ferr << stops[i].name << " " << cur_idx << '\n';
        }

        if (cur_idx != 0) {
            x_step = (max_width - 2 * padding_) / cur_idx;
        } else {
            x_step = 0;
        }

        std::sort(begin(stops), end(stops),
                  [](const Descriptions::Stop &lhs, const Descriptions::Stop &rhs) {
                      return lhs.position.latitude < rhs.position.latitude;
                  });
        cur_idx = 0;
        for (int i = 0; i < stops.size(); i++) {
            bool neighbor = false;
            for (int j = i - 1; j >= 0 && (lat_idx[stops[j].position.latitude] == cur_idx); j--) {
                neighbor = neighbor || isNeighbors(stops[i], stops[j], buses);
            }
            if (neighbor) {
                cur_idx++;
            }
            lat_idx[stops[i].position.latitude] = cur_idx;
            ferr << stops[i].name << " " << cur_idx << '\n';
        }
        if (cur_idx != 0) {
            y_step = (max_height - 2 * padding_) / cur_idx;
        } else {
            y_step = 0;
        }
    }

}
