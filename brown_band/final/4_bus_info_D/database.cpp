#include "database.h"

const std::string &Stop::getName() const {
    return name;
}

const Coordinates &Stop::getCoordinates() const {
    return coordinates;
}

void Stop::AddBus(const std::string &bus) {
    buses.insert(bus);
}

std::vector<std::string> Stop::getBuses() {
    return {buses.begin(), buses.end()};
}

Stop::Stop(const Stop &other) {
    if (name == other.name) {
        buses.insert(other.buses.begin(), other.buses.end());
        for (const auto&[key, value]: other.distance_to_stop) {
            distance_to_stop[key] = value;
        }
    } else {
        buses = other.buses;
        distance_to_stop = other.distance_to_stop;
    }
    name = other.name;
    coordinates = other.coordinates;
}

Stop::Stop(Stop &&other) noexcept {
    if (name == other.name) {
        buses.insert(std::make_move_iterator(other.buses.begin()), std::make_move_iterator(other.buses.end()));
        for (auto&[key, value]: other.distance_to_stop) {
            distance_to_stop[key] = std::move(value);
        }
    } else {
        buses = std::move(other.buses);
        distance_to_stop = std::move(other.distance_to_stop);
    }
    name = std::move(other.name);
    coordinates = std::move(other.coordinates);
}

Stop &Stop::operator=(const Stop &other) {
    if (name == other.name) {
        buses.insert(other.buses.begin(), other.buses.end());
        for (const auto&[key, value]: other.distance_to_stop) {
            distance_to_stop[key] = value;
        }
    } else {
        buses = other.buses;
        distance_to_stop = other.distance_to_stop;
    }
    name = other.name;
    coordinates = other.coordinates;
    return *this;
}

Stop &Stop::operator=(Stop &&other) noexcept {
    if (name == other.name) {
        buses.insert(std::make_move_iterator(other.buses.begin()), std::make_move_iterator(other.buses.end()));
        for (auto&[key, value]: other.distance_to_stop) {
            distance_to_stop[key] = std::move(value);
        }
    } else {
        buses = std::move(other.buses);
        distance_to_stop = std::move(other.distance_to_stop);
    }
    name = std::move(other.name);
    coordinates = std::move(other.coordinates);
    return *this;
}

void Stop::AddDistance(const std::string &stop_name, double distance) {
    distance_to_stop[stop_name] = distance;
}

void Stop::SafeAddDistance(const std::string &stop_name, double distance) {
    if (distance_to_stop.count(stop_name) == 0) {
        distance_to_stop.insert({stop_name, distance});
    }
}

const std::unordered_map<std::string, double> &Stop::getDistanceToStop() const {
    return distance_to_stop;
}

double Stop::GetDistance(const std::string &s) const {
    if (distance_to_stop.count(s) == 0) {
        return 0;
    } else {
        return distance_to_stop.at(s);
    }
}


int LinearBus::StopsCount() const {
    return stops.size() * 2 - 1;
}

int LinearBus::UniqueStopsCount() const {
    return unique.size();
}

double LinearBus::PlainDistance() const {
    double distance = 0;
    for (int i = 1; i < stops.size(); i++) {
        distance += Distance(stops[i]->getCoordinates(), stops[i - 1]->getCoordinates());
    }
    distance *= 2;
    return distance;
}

double LinearBus::Length() const {
    double length = 0;
    for (int i = 0; i < stops.size() - 1; i++) {
        length += stops[i]->GetDistance(stops[i + 1]->getName());
        length += stops[i + 1]->GetDistance(stops[i]->getName());
    }
    return length;
}

double LinearBus::Curvature() const {
    return Length() / PlainDistance();
}

int CycleBus::StopsCount() const {
    return stops.size();
}

int CycleBus::UniqueStopsCount() const {
    return unique.size();
}

double CycleBus::PlainDistance() const {
    double distance = 0;
    for (int i = 1; i < stops.size(); i++) {
        distance += Distance(stops[i]->getCoordinates(), stops[i - 1]->getCoordinates());
    }
    return distance;
}

double CycleBus::Length() const {
    double length = 0;
    for (int i = 0; i < stops.size() - 1; i++) {
        length += stops[i]->GetDistance(stops[i + 1]->getName());
    }
    return length;
}

double CycleBus::Curvature() const {
    return Length() / PlainDistance();
}

void Database::AddStop(const Stop &stop) {
    if (stops.count(stop.getName()) == 0) {
        stops.insert({stop.getName(), std::make_shared<Stop>(stop)});
    } else {
        *stops[stop.getName()] = stop;
    }
    for (const auto&[key, value]:stop.getDistanceToStop()) {
        this->GetOrAddStop(key)->SafeAddDistance(stop.getName(), value);
    }
}

void Database::AddRoute(const std::string &name, std::shared_ptr<Bus> route) {
    for (const auto &stop_name:route->getStopNames()) {
        stops[stop_name]->AddBus(name);
    }
    buses.insert({name, std::move(route)});
}

std::shared_ptr<Stop> Database::GetOrAddStop(const std::string &name) {
    if (stops.count(name) == 0) {
        stops.insert({name, std::make_shared<Stop>(name, Coordinates())});
    }
    return stops.at(name);
}

std::shared_ptr<Bus> Database::GetBus(const std::string &name) const {
    if (buses.count(name) == 0) {
        return nullptr;
    } else {
        return buses.at(name);
    }
}

std::shared_ptr<Stop> Database::GetStop(const std::string &name) const {
    if (stops.count(name) == 0) {
        return nullptr;
    }
    return stops.at(name);
}

std::shared_ptr<Bus> BusBuilder::MakeBus(BusInfo &&info) {
    if (info.type == Bus::BusType::LINEAR) {
        return MakeLinear(std::move(info));
    } else if (info.type == Bus::BusType::CYCLE) {
        return MakeCycle(std::move(info));
    } else {
        return nullptr;
    }
}

std::shared_ptr<Bus> BusBuilder::MakeLinear(BusInfo &&info) {
    std::vector<std::shared_ptr<Stop>> stop_ptr;
    stop_ptr.reserve(info.stops.size());
    for (const auto &s:info.stops) {
        stop_ptr.push_back(db.GetOrAddStop(s));
    }
    return std::make_shared<LinearBus>(info.name, info.stops, stop_ptr);
}

std::shared_ptr<Bus> BusBuilder::MakeCycle(BusInfo &&info) {
    std::vector<std::shared_ptr<Stop>> stop_ptr;
    stop_ptr.reserve(info.stops.size());
    for (const auto &s:info.stops) {
        stop_ptr.push_back(db.GetOrAddStop(s));
    }
    return std::make_shared<CycleBus>(info.name, info.stops, stop_ptr);
}


const std::vector<std::string> &Bus::getStopNames() const {
    return stop_names;
}
