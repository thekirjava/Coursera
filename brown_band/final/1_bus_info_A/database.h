#pragma once

#include "coordinates.h"
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

class Stop {
public:
    Stop(std::string name, const Coordinates &coordinates) : name(std::move(name)), coordinates(coordinates) {}

    const std::string &getName() const;

    const Coordinates &getCoordinates() const;

private:
    std::string name;
    Coordinates coordinates;
};

class Route {
public:
    enum RouteType {
        LINEAR, CYCLE
    };

    explicit Route(std::string name, std::vector<std::string> stop_names) : name(std::move(name)),
                                                                            stop_names(std::move(stop_names)) {}

    virtual int StopsCount() const = 0;

    virtual int UniqueStopsCount() const = 0;

    virtual double Length() const = 0;

private:
    std::string name;
    std::vector<std::string> stop_names;
};

class LinearRoute : public Route {
public:
    explicit LinearRoute(std::string name, std::vector<std::string> stop_names,
                         std::vector<std::shared_ptr<Stop> > stops) : Route(std::move(name), std::move(stop_names)),
                                                                      stops(std::move(stops)) {
        for (const auto &s:stop_names) {
            unique.insert(s);
        }
    }

    int StopsCount() const override;

    int UniqueStopsCount() const override;

    double Length() const override;

private:
    std::vector<std::shared_ptr<Stop> > stops;
    std::unordered_set<std::string_view> unique;
};

class CycleRoute : public Route {
public:
    explicit CycleRoute(std::string name, std::vector<std::string> stop_names,
                        std::vector<std::shared_ptr<Stop> > stops) : Route(std::move(name), std::move(stop_names)),
                                                                     stops(std::move(stops)) {
        for (const auto &s:stop_names) {
            unique.insert(s);
        }
    }

    int StopsCount() const override;

    int UniqueStopsCount() const override;

    double Length() const override;

private:
    std::vector<std::shared_ptr<Stop> > stops;
    std::unordered_set<std::string_view> unique;
};

class Database {
public:
    Database() = default;
    void AddStop(const Stop& stop);
    void AddRoute(const std::string& name, std::shared_ptr<Route> route);
    std::shared_ptr<Stop> GetStop(const std::string& name) const;
    std::shared_ptr<Route> GetRoute(const std::string& name) const;
private:
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops;
    std::unordered_map<std::string, std::shared_ptr<Route>> routes;
};

struct RouteInfo {
    Route::RouteType type;
    std::string name;
    std::vector<std::string> stops;
};
class RouteBuilder {
public:
    RouteBuilder() = delete;
    explicit RouteBuilder(Database& db):db(db) {}
    std::shared_ptr<Route> MakeRoute(RouteInfo&& info);
private:
    Database& db;
    std::shared_ptr<Route> MakeLinear(RouteInfo&& info);
    std::shared_ptr<Route> MakeCycle(RouteInfo&& info);
};