#include "descriptions.h"
#include <algorithm>

using namespace std;

namespace Descriptions {

    Stop Stop::ParseFrom(const Json::Dict &attrs) {
        Stop stop = {
                .name = attrs.at("name").AsString(),
                .position = {
                        .latitude = attrs.at("latitude").AsDouble(),
                        .longitude = attrs.at("longitude").AsDouble(),
                }
        };
        if (attrs.count("road_distances") > 0) {
            for (const auto&[neighbour_stop, distance_node] : attrs.at("road_distances").AsMap()) {
                stop.distances[neighbour_stop] = distance_node.AsInt();
            }
        }
        return stop;
    }

    static vector<string> ParseStops(const Json::Array &stop_nodes, bool is_roundtrip) {
        vector<string> stops;
        stops.reserve(stop_nodes.size());
        for (const Json::Node &stop_node : stop_nodes) {
            stops.push_back(stop_node.AsString());
        }
        if (is_roundtrip || stops.size() <= 1) {
            return stops;
        }
        stops.reserve(stops.size() * 2 - 1);  // end stop is not repeated
        for (size_t stop_idx = stops.size() - 1; stop_idx > 0; --stop_idx) {
            stops.push_back(stops[stop_idx - 1]);
        }
        return stops;
    }

    int ComputeStopsDistance(const Stop &lhs, const Stop &rhs) {
        if (auto it = lhs.distances.find(rhs.name); it != lhs.distances.end()) {
            return it->second;
        } else {
            return rhs.distances.at(lhs.name);
        }
    }

    Bus Bus::ParseFrom(const Json::Dict &attrs) {
        const auto &name = attrs.at("name").AsString();
        const auto &stops = attrs.at("stops").AsArray();
        if (stops.empty()) {
            return Bus{.name = name};
        } else {
            Bus bus{
                    .name = name,
                    .stops = ParseStops(stops, attrs.at("is_roundtrip").AsBool()),
                    .endpoints = {stops.front().AsString(), stops.back().AsString()}
            };
            if (bus.endpoints.back() == bus.endpoints.front()) {
                bus.endpoints.pop_back();
            }
            return bus;
        }
    }

    vector<InputQuery> ReadDescriptions(const Json::Array &nodes) {
        vector<InputQuery> result;
        result.reserve(nodes.size());

        for (const Json::Node &node : nodes) {
            const auto &node_dict = node.AsMap();
            if (node_dict.at("type").AsString() == "Bus") {
                result.emplace_back(Bus::ParseFrom(node_dict));
            } else {
                result.emplace_back(Stop::ParseFrom(node_dict));
            }
        }

        return result;
    }

    bool isNeighbors(const Stop &lhs, const Stop &rhs, const std::vector<Bus> &buses) {
        for (const auto &b:buses) {
            auto pos = std::find(begin(b.stops), end(b.stops), lhs.name);
            while (pos != end(b.stops)) {
                if (((next(pos) != end(b.stops) && (*next(pos) == rhs.name))) ||
                    ((pos != begin(b.stops)) && (*prev(pos) == rhs.name))) {
                    return true;
                }
                pos = std::find(next(pos), end(b.stops), lhs.name);
            }
        }
        return false;
    }

    bool isSupporting(const Stop &stop, const vector<Bus> &buses) {
        size_t counter = 0;
        for (const auto &bus:buses) {
            if (std::find(begin(bus.endpoints), end(bus.endpoints), stop.name) != end(bus.endpoints)) {
                return true;
            }
            if (std::count(begin(bus.stops), end(bus.stops), stop.name) > 2) {
                return true;
            }
            if (std::find(begin(bus.stops), end(bus.stops), stop.name) != end(bus.stops)) {
                counter++;
            }
            if (counter > 1) {
                return true;
            }
        }
        return false;
    }

    void Recount(vector<Stop> &stops, const Bus &bus) {
        size_t prev = 0;
        for (size_t stop_name = 0;
             stop_name < (bus.endpoints.size() == 1 ? bus.stops.size() : (bus.stops.size() / 2) + 1); stop_name++) {
            auto pos = std::lower_bound(begin(stops), end(stops), bus.stops[stop_name],
                                        [](const Stop &stop, const std::string &value) {
                                            return stop.name < value;
                                        });
            if (pos->supporting) {
                size_t len = stop_name - prev;
                if (len <= 1) {
                    prev = stop_name;
                    continue;
                }
                auto firstStop = std::lower_bound(begin(stops), end(stops), bus.stops[prev],
                                                  [](const Stop &stop, const std::string &value) {
                                                      return stop.name < value;
                                                  });
                double lat_step = (pos->position.latitude - firstStop->position.latitude) / len;
                double lon_step = (pos->position.longitude - firstStop->position.longitude) / len;
                for (size_t i = prev; i < stop_name; i++) {
                    auto cur = std::lower_bound(begin(stops), end(stops), bus.stops[i],
                                                [](const Stop &stop, const std::string &value) {
                                                    return stop.name < value;
                                                });
                    if (!cur->supporting) {
                        cur->position.longitude = firstStop->position.longitude + lon_step * (i - prev);
                        cur->position.latitude = firstStop->position.latitude + lat_step * (i - prev);
                    }
                }
                prev = stop_name;
            }
        }
    }

}
