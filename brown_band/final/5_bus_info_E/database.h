#pragma once

#include "coordinates.h"
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <set>
#include <list>
#include "graph.h"
#include "router.h"
class Stop {
public:
    Stop(std::string name, const Coordinates &coordinates) : name(std::move(name)), coordinates(coordinates) {}

    Stop(std::string name, const Coordinates &coordinates, const std::unordered_map<std::string, double> &distances)
            : name(std::move(name)), coordinates(coordinates), distance_to_stop(distances) {}

    Stop(const Stop &other);

    Stop(Stop &&other) noexcept;

    Stop &operator=(const Stop &other);

    Stop &operator=(Stop &&other) noexcept;

    const std::string &getName() const;

    const Coordinates &getCoordinates() const;

    void AddBus(const std::string &bus);

    void AddDistance(const std::string &stop_name, double distance);

    void SafeAddDistance(const std::string &stop_name, double distance);

    std::vector<std::string> getBuses();

    const std::unordered_map<std::string, double> &getDistanceToStop() const;

    double GetDistance(const std::string &s) const;

private:
    std::string name;
    Coordinates coordinates;
    std::unordered_map<std::string, double> distance_to_stop;
    std::set<std::string> buses;

};

class Bus {
public:
    enum BusType {
        LINEAR, CYCLE
    };

    explicit Bus(const std::string &name, const std::vector<std::string> &stop_names) : name(name),
                                                                                        stop_names(stop_names) {}

    const std::vector<std::string> &getStopNames() const;

    virtual int StopsCount() const = 0;

    virtual int UniqueStopsCount() const = 0;

    virtual double Length() const = 0;

    virtual double Curvature() const = 0;

    virtual BusType GetType() const = 0;

    const std::string &getName() const {
        return name;
    }

protected:
    virtual double PlainDistance() const = 0;

    std::string name;
    std::vector<std::string> stop_names;
};

class LinearBus : public Bus {
public:
    explicit LinearBus(const std::string &name, const std::vector<std::string> &stop_names,
                       const std::vector<std::shared_ptr<Stop> > &stops) : Bus(name, stop_names),
                                                                           stops(stops) {
        for (const auto &s:stop_names) {
            unique.insert(s);
        }
    }

    int StopsCount() const override;

    int UniqueStopsCount() const override;

    double Length() const override;

    double Curvature() const override;

    BusType GetType() const override {
        return LINEAR;
    }

private:
    double PlainDistance() const override;

    std::vector<std::shared_ptr<Stop> > stops;
    std::unordered_set<std::string_view> unique;
};

class CycleBus : public Bus {
public:
    explicit CycleBus(const std::string &name, const std::vector<std::string> &stop_names,
                      const std::vector<std::shared_ptr<Stop> > &stops) : Bus(name, stop_names),
                                                                          stops(stops) {
        for (const auto &s:stop_names) {
            unique.insert(s);
        }
    }

    int StopsCount() const override;

    int UniqueStopsCount() const override;

    double Length() const override;

    double Curvature() const override;

    BusType GetType() const override {
        return CYCLE;
    }

private:
    double PlainDistance() const override;

    std::vector<std::shared_ptr<Stop> > stops;
    std::unordered_set<std::string_view> unique;
};

struct BusInfo {
    Bus::BusType type;
    std::string name;
    std::vector<std::string> stops;
};

enum NodeType {
    INFO, WAIT, BUS
};

struct BaseNode {
    BaseNode() = default;

    BaseNode(NodeType t) : type(t) {}

    virtual ~BaseNode() = default;

    NodeType type;
};

struct InfoNode : public BaseNode {
    using BaseNode::BaseNode;

    InfoNode() = default;

    InfoNode(double value) : BaseNode(NodeType::INFO), total_time(value) {}

    std::optional<double> total_time;
};

struct WaitNode : public BaseNode {
    using BaseNode::BaseNode;

    WaitNode() = default;

    WaitNode(const std::string &stop_name, double time)
            : BaseNode(NodeType::WAIT), stop_name(stop_name), time(time) {}

    std::string stop_name;
    double time;
};

struct BusNode : public BaseNode {
    using BaseNode::BaseNode;

    BusNode() = default;

    BusNode(const std::string &route_name, int span_count, double time)
            : BaseNode(NodeType::BUS), route_name(route_name), span_count(span_count), time(time) {}

    std::string route_name;
    int span_count;
    double time;
};

class Database {
    using WeightType = double;
    struct RoutingParam {
        double velocity;
        double waiting_time;
    };
public:
    Database();

    void AddStop(const Stop &stop);

    void AddRoute(const std::string &name, std::shared_ptr<Bus> route);

    std::shared_ptr<Stop> GetOrAddStop(const std::string &name);

    std::shared_ptr<Stop> GetStop(const std::string &name) const;

    std::shared_ptr<Bus> GetBus(const std::string &name) const;

    std::list<std::unique_ptr<BaseNode>> CreateRoute(const std::string &first_stop, const std::string &last_stop) const;

    void setParams(const RoutingParam &params) {
        Database::params = params;
    }

private:
    Graph::DirectedWeightedGraph<WeightType> UpdateGraph() const;
    void MakeWeightsFromCycleBus(Graph::DirectedWeightedGraph<WeightType> &graph, const std::shared_ptr<Bus> &ptr) const;
    void MakeWeightsFromLinearBus(Graph::DirectedWeightedGraph<WeightType> &graph, const std::shared_ptr<Bus> &ptr) const;
    void AddStops() const;

    std::unordered_map<std::string, std::shared_ptr<Stop>> stops;
    std::unordered_map<std::string, std::shared_ptr<Bus>> buses;

    template <typename Weight>
    struct Edge {
        bool is_wait_edge;
        double weight;
        int span_count;
        std::string bus_name;
        Graph::VertexId from;
        Graph::VertexId to;
    };
    template <typename Weight>
    struct GraphCache {
        bool is_outdated = true;
        Graph::DirectedWeightedGraph<Weight> weightedGraph;
        std::unique_ptr<Graph::Router<Weight>> router = nullptr;
        Graph::VertexId curr_id = 0;
        std::unordered_map<std::string, std::pair<Graph::VertexId, Graph::VertexId>> name_to_vertex_id;
        std::unordered_map<Graph::VertexId, std::pair<std::string, std::string>> vertex_id_to_name;
        std::unordered_map<Graph::EdgeId, Edge<Weight>> edges;
    };
    mutable GraphCache<WeightType> graphCache;
    RoutingParam params;
};

class BusBuilder {
public:
    BusBuilder() = delete;

    explicit BusBuilder(Database &db) : db(db) {}

    std::shared_ptr<Bus> MakeBus(BusInfo &&info);

private:
    Database &db;

    std::shared_ptr<Bus> MakeLinear(BusInfo &&info);

    std::shared_ptr<Bus> MakeCycle(BusInfo &&info);
};