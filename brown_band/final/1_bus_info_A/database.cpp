//
// Created by JUSTONEIDEA on 17.09.2020.
//

#include "database.h"

const std::string &Stop::getName() const {
    return name;
}

const Coordinates &Stop::getCoordinates() const {
    return coordinates;
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
    stops.insert({stop.getName(), std::make_shared<Stop>(stop)});
}

void Database::AddRoute(const std::string &name, std::shared_ptr<Route>route) {
    routes.insert({name, std::move(route)});
}

std::shared_ptr<Stop> Database::GetStop(const std::string &name) const {
    if (stops.count(name) == 0) {
        return nullptr;
    } else {
        return stops.at(name);
    }
}

std::shared_ptr<Route> Database::GetRoute(const std::string &name) const {
    if (routes.count(name) == 0) {
        return nullptr;
    } else {
        return routes.at(name);
    }
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
   for (const auto& s:info.stops) {
       stop_ptr.push_back(db.GetStop(s));
   }
    return std::make_shared<LinearRoute>(info.name, info.stops, stop_ptr);
}

std::shared_ptr<Route> RouteBuilder::MakeCycle(RouteInfo &&info) {
    std::vector<std::shared_ptr<Stop>> stop_ptr;
    stop_ptr.reserve(info.stops.size());
    for (const auto& s:info.stops) {
        stop_ptr.push_back(db.GetStop(s));
    }
    return std::make_shared<CycleRoute>(info.name, info.stops, stop_ptr);
}
