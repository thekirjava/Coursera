#pragma once

#include "json.h"
#include "sphere.h"

#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>


namespace Descriptions {
    struct Stop {
        std::string name;
        Sphere::Point position;
        std::unordered_map<std::string, int> distances;
        bool supporting = false;
        static Stop ParseFrom(const Json::Dict &attrs);
    };

    int ComputeStopsDistance(const Stop &lhs, const Stop &rhs);



    struct Bus {
        std::string name;
        std::vector<std::string> stops;
        std::vector<std::string> endpoints;

        static Bus ParseFrom(const Json::Dict &attrs);
    };

    using InputQuery = std::variant<Stop, Bus>;

    std::vector<InputQuery> ReadDescriptions(const Json::Array &nodes);


    template<typename Object>
    using Dict = std::map<std::string, const Object *>;

    using StopsDict = Dict<Stop>;
    using BusesDict = Dict<Bus>;
    bool isNeighbors(const Stop& lhs, const Stop& rhs, const std::vector<Bus>& buses);
    bool isSupporting(const Stop& stop, const std::vector<Bus> & buses);
    void Recount(std::vector<Stop>& stops, const Bus& bus);
}
