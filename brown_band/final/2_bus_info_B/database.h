#pragma once

#include "coordinates.h"
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <set>

class Stop {
public:
    Stop(std::string name, const Coordinates &coordinates) : name(std::move(name)), coordinates(coordinates) {}

    Stop(const Stop& other);
    Stop(Stop&& other);
    Stop& operator=(const Stop& other);
    Stop& operator=(Stop&& other);
    const std::string &getName() const;

    const Coordinates &getCoordinates() const;

    void AddRoute(const std::string &route);

    std::vector<std::string> getRoutes();

private:
    std::string name;
    Coordinates coordinates;
    std::set<std::string> routes;
};

class Route {
public:
    enum RouteType {
        LINEAR, CYCLE
    };

    explicit Route(const std::string &name, const std::vector<std::string> &stop_names) : name(name),
                                                                                          stop_names(stop_names) {}

    const std::vector<std::string> &getStopNames() const;

    virtual int StopsCount() const = 0;

    virtual int UniqueStopsCount() const = 0;

    virtual double Length() const = 0;

private:
    std::string name;
    std::vector<std::string> stop_names;
};

class LinearRoute : public Route {
public:
    explicit LinearRoute(const std::string &name, const std::vector<std::string> &stop_names,
                         const std::vector<std::shared_ptr<Stop> > &stops) : Route(name, stop_names),
                                                                             stops(stops) {
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
    explicit CycleRoute(const std::string &name, const std::vector<std::string> &stop_names,
                        const std::vector<std::shared_ptr<Stop> > &stops) : Route(name, stop_names),
                                                                            stops(stops) {
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

    void AddStop(const Stop &stop);

    void AddRoute(const std::string &name, std::shared_ptr<Route> route);

    std::shared_ptr<Stop> GetOrAddStop(const std::string &name);

    std::shared_ptr<Stop> GetStop(const std::string &name) const;

    std::shared_ptr<Route> GetRoute(const std::string &name) const;

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

    explicit RouteBuilder(Database &db) : db(db) {}

    std::shared_ptr<Route> MakeRoute(RouteInfo &&info);

private:
    Database &db;

    std::shared_ptr<Route> MakeLinear(RouteInfo &&info);

    std::shared_ptr<Route> MakeCycle(RouteInfo &&info);
};