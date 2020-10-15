#include "database.h"

const std::string &Stop::getName() const {
    return name;
}

const Coordinates &Stop::getCoordinates() const {
    return coordinates;
}

void Stop::AddRoute(const std::string &route) {
    routes.insert(route);
}

std::vector<std::string> Stop::getRoutes() {
    return {routes.begin(), routes.end()};
}

Stop::Stop(const Stop &other) {
    if (name == other.name) {
        routes.insert(other.routes.begin(), other.routes.end());
    } else {
        routes = other.routes;
    }
    name = other.name;
    coordinates = other.coordinates;
}

Stop::Stop(Stop &&other) {
    if (name == other.name) {
        routes.insert(std::make_move_iterator(other.routes.begin()), std::make_move_iterator(other.routes.end()));
    } else {
        routes = std::move(other.routes);
    }
    name = std::move(other.name);
    coordinates = std::move(other.coordinates);
}

Stop &Stop::operator=(const Stop &other) {
    if (name == other.name) {
        routes.insert(other.routes.begin(), other.routes.end());
    } else {
        routes = other.routes;
    }
    name = other.name;
    coordinates = other.coordinates;
    return *this;
}

Stop &Stop::operator=(Stop &&other) {
    if (name == other.name) {
        routes.insert(std::make_move_iterator(other.routes.begin()), std::make_move_iterator(other.routes.end()));
    } else {
        routes = std::move(other.routes);
    }
    name = std::move(other.name);
    coordinates = std::move(other.coordinates);
    return *this;
}


int LinearRoute::StopsCount() const {
    return stops.size() * 2 - 1;
}

int LinearRoute::UniqueStopsCount() const {
    return unique.size();
}

double LinearRoute::Length() const {
    double length = 0;
    for (int i = 1; i < stops.size(); i++) {
        length += Distance(stops[i]->getCoordinates(), stops[i - 1]->getCoordinates());
    }
    length *= 2;
    return length;
}

int CycleRoute::StopsCount() const {
    return stops.size();
}

int CycleRoute::UniqueStopsCount() const {
    return unique.size();
}

double CycleRoute::Length() const {
    double length = 0;
    for (int i = 1; i < stops.size(); i++) {
        length += Distance(stops[i]->getCoordinates(), stops[i - 1]->getCoordinates());
    }
    return length;
}

void Database::AddStop(const Stop &stop) {
    if (stops.count(stop.getName()) == 0) {
        stops.insert({stop.getName(), std::make_shared<Stop>(stop)});
    } else {
        *stops[stop.getName()] = stop;
    }
}

void Database::AddRoute(const std::string &name, std::shared_ptr<Route> route) {
    for (const auto &stop_name:route->getStopNames()) {
        stops[stop_name]->AddRoute(name);
    }
    routes.insert({name, std::move(route)});
}

std::shared_ptr<Stop> Database::GetOrAddStop(const std::string &name) {
    if (stops.count(name) == 0) {
        stops.insert({name, std::make_shared<Stop>(name, Coordinates())});
    }
    return stops.at(name);
}

std::shared_ptr<Route> Database::GetRoute(const std::string &name) const {
    if (routes.count(name) == 0) {
        return nullptr;
    } else {
        return routes.at(name);
    }
}

std::shared_ptr<Stop> Database::GetStop(const std::string &name) const {
    if (stops.count(name) == 0) {
        return nullptr;
    }
    return stops.at(name);
}

std::shared_ptr<Route> RouteBuilder::MakeRoute(RouteInfo &&info) {
    if (info.type == Route::RouteType::LINEAR) {
        return MakeLinear(std::move(info));
    } else if (info.type == Route::RouteType::CYCLE) {
        return MakeCycle(std::move(info));
    } else {
        return nullptr;
    }
}

std::shared_ptr<Route> RouteBuilder::MakeLinear(RouteInfo &&info) {
    std::vector<std::shared_ptr<Stop>> stop_ptr;
    stop_ptr.reserve(info.stops.size());
    for (const auto &s:info.stops) {
        stop_ptr.push_back(db.GetOrAddStop(s));
    }
    return std::make_shared<LinearRoute>(info.name, info.stops, stop_ptr);
}

std::shared_ptr<Route> RouteBuilder::MakeCycle(RouteInfo &&info) {
    std::vector<std::shared_ptr<Stop>> stop_ptr;
    stop_ptr.reserve(info.stops.size());
    for (const auto &s:info.stops) {
        stop_ptr.push_back(db.GetOrAddStop(s));
    }
    return std::make_shared<CycleRoute>(info.name, info.stops, stop_ptr);
}


const std::vector<std::string> &Route::getStopNames() const {
    return stop_names;
}
