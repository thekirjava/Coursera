#include "database.h"

#include <utility>

namespace TransportDatabase {
    Stop::Stop() {
        name_ = "unnamed";
    }

    Stop::Stop(std::string name, const Coordinates &coord) : name_(std::move(name)), coord_(coord) {}

    Stop::Stop(std::string name, const Coordinates &coord, const std::vector<std::pair<std::string, int>> &distances)
            : name_(std::move(name)), coord_(coord) {
        for (const auto&[key, value] : distances) {
            distance_to_stop[key] = value;
        }
    }

    Stop::Stop(const Stop &other) {
        name_ = other.name_;
        coord_ = other.coord_;
        for (const auto&[stop_name, distance] : other.distance_to_stop) {
            distance_to_stop[stop_name] = distance;
        }
    }

    Stop::Stop(Stop &&other) noexcept {
        name_ = std::move(other.name_);
        coord_ = other.coord_;
        for (auto&[stop_name, distance] : other.distance_to_stop) {
            distance_to_stop[std::move(stop_name)] = std::move(distance);
        }
    }

    Stop &Stop::operator=(const Stop &other) {
        name_ = other.name_;
        coord_ = other.coord_;
        for (const auto&[stop_name, distance] : other.distance_to_stop) {
            distance_to_stop[stop_name] = distance;
        }
        return *this;
    }

    Stop &Stop::operator=(Stop &&other) noexcept {
        name_ = std::move(other.name_);
        coord_ = other.coord_;
        for (auto&[stop_name, distance] : other.distance_to_stop) {
            distance_to_stop[std::move(stop_name)] = std::move(distance);
        }
        return *this;
    }

    std::string Stop::getName() const {
        return name_;
    }

    Coordinates Stop::getCoordinates() const {
        return coord_;
    }

    void Stop::addBus(const std::string &bus_name) {
        buses_for_stop.insert(bus_name);
    }

    std::vector<std::string> Stop::getBuses() const {
        return {buses_for_stop.begin(), buses_for_stop.end()};
    }

    double Bus::curvature() const {
        return realLength() / length();
    }

    std::string Bus::getName() const {
        return name_;
    }

    std::vector<std::string> Bus::getStopsName() const {
        return stops_name_;
    }

    size_t LinearBus::countOfStops() const {
        return stops_.size() * 2 - 1;
    }

    size_t LinearBus::countOfUniqueStops() const {
        return unique_stops_.size();
    }

    double LinearBus::realLength() const {
        double result = 0;
        for (size_t i = 0; i < stops_.size() - 1; ++i) {
            result += stops_[i]->distance_to_stop.at(stops_[i + 1]->getName()) +
                      stops_[i + 1]->distance_to_stop.at(stops_[i]->getName());
        }
        return result;
    }

    double LinearBus::length() const {
        double result = 0;
        for (size_t i = 0; i < stops_.size() - 1; ++i) {
            result += Distance(stops_[i]->getCoordinates(), stops_[i + 1]->getCoordinates())
                      + Distance(stops_[i + 1]->getCoordinates(), stops_[i]->getCoordinates());
        }
        return result;
    }

    size_t CycleBus::countOfStops() const {
        return stops_.size();
    }

    size_t CycleBus::countOfUniqueStops() const {
        return unique_stops_.size();
    }

    double CycleBus::realLength() const {
        double result = 0;
        for (size_t i = 0; i < stops_.size() - 1; ++i) {
            result += stops_[i]->distance_to_stop.at(stops_[i + 1]->getName());
        }
        return result;
    }

    double CycleBus::length() const {
        double result = 0;
        for (size_t i = 0; i < stops_.size() - 1; ++i) {
            result += Distance(stops_[i]->getCoordinates(), stops_[i + 1]->getCoordinates());
        }
        return result;
    }

    void Database::addStop(const Stop &stop) {
        auto inserted = stops_.try_emplace(stop.getName(), std::make_shared<Stop>(stop));
        if (!inserted.second) {
            *(inserted.first->second) = stop;
        }
        for (const auto&[stop_name, distance] : stop.distance_to_stop) {
            auto curr_stop = getOrAddStop(stop_name);
            if (!curr_stop->distance_to_stop.count(stop.getName())) {
                curr_stop->distance_to_stop[stop.getName()] = distance;
            }
        }
        stat.min_lat = std::min(stat.min_lat, stop.getCoordinates().getLatitude());
        stat.max_lat = std::max(stat.max_lat, stop.getCoordinates().getLatitude());
        stat.min_long = std::min(stat.min_long, stop.getCoordinates().getLongitude());
        stat.max_long = std::max(stat.max_long, stop.getCoordinates().getLongitude());
    }

    std::shared_ptr<Stop> Database::getOrAddStop(const std::string &stop_name) {
        if (!stops_.count(stop_name)) {
            auto inserted = stops_.insert({stop_name, std::make_shared<Stop>(stop_name, Coordinates())});
        }
        return stops_.at(stop_name);
    }

    std::shared_ptr<Stop> Database::getStop(const std::string &stop_name) const {
        if (!stops_.count(stop_name)) {
            return nullptr;
        }
        return stops_.at(stop_name);
    }

    void Database::addBus(const std::string &bus_name, std::shared_ptr<Bus> bus) {
        for (const auto &stop_name : bus->getStopsName()) {
            stops_[stop_name]->addBus(bus_name);
        }
        buses_[bus_name] = std::move(bus);
    }

    std::shared_ptr<Bus> Database::getBus(const std::string &bus_name) const {
        if (buses_.count(bus_name)) {
            return buses_.at(bus_name);
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<Bus> BusBuilder::makeBus(BusInfo &&info) {
        switch (info.type) {
            case Bus::BusTypes::LINEAR:
                return makeLinear(std::move(info));
            case Bus::BusTypes::CYCLE:
                return makeCycle(std::move(info));
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Bus> BusBuilder::makeCycle(BusInfo &&info) {
        std::vector<std::shared_ptr<Stop>> stops_ptr;
        stops_ptr.reserve(info.stop_names.size());
        for (auto &str : info.stop_names) {
            auto stop = db_.getOrAddStop(str);
            stops_ptr.push_back(std::move(stop));
        }
        return std::make_shared<CycleBus>(std::move(info.name), std::move(info.stop_names), std::move(stops_ptr));
    }

    std::shared_ptr<Bus> BusBuilder::makeLinear(BusInfo &&info) {
        std::vector<std::shared_ptr<Stop>> stops_ptr;
        stops_ptr.reserve(info.stop_names.size());
        for (auto &str : info.stop_names) {
            auto stop = db_.getOrAddStop(str);
            stops_ptr.push_back(std::move(stop));
        }
        return std::make_shared<LinearBus>(std::move(info.name), std::move(info.stop_names), std::move(stops_ptr));
    }

    const Database::StopData &Database::getStops() const {
        return stops_;
    }

    const Database::BusData &Database::getBuses() const {
        return buses_;
    }

    const DatabaseStat &Database::getStat() const {
        return stat;
    }
}
