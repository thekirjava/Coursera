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

std::list<std::unique_ptr<BaseNode>>
Database::CreateRoute(const std::string &first_stop, const std::string &last_stop) const {
    if (graphCache.is_outdated) {
        graphCache.weightedGraph = UpdateGraph();
        graphCache.router = std::make_unique<Graph::Router<WeightType>>(graphCache.weightedGraph);
        graphCache.is_outdated = false;
    }
    auto route = graphCache.router->BuildRoute(graphCache.name_to_vertex_id.at(first_stop).first, graphCache.name_to_vertex_id.at(last_stop).first);
    std::list<std::unique_ptr<BaseNode>> nodes;
    if (!route) {
        nodes.push_back(std::make_unique<InfoNode>());
        return nodes;
    }
    nodes.push_back(std::make_unique<InfoNode>(route->weight));
    for (size_t i = 0; i<route->edge_count; i++) {
        Graph::EdgeId edgeId = graphCache.router->GetRouteEdge(route->id, i);
        Edge edge = graphCache.edges.at(edgeId);
        if (edge.is_wait_edge) {
            nodes.push_back(std::make_unique<WaitNode>(graphCache.vertex_id_to_name.at(edge.from).first, edge.weight));
        } else {
            nodes.push_back(std::make_unique<BusNode>(edge.bus_name, edge.span_count, edge.weight));
        }
    }
    return nodes;
}

Graph::DirectedWeightedGraph<Database::WeightType> Database::UpdateGraph() const {
    AddStops();
    auto newWeightGraph = Graph::DirectedWeightedGraph<WeightType>(graphCache.name_to_vertex_id.size() * 2);
    for (const auto& [stop_name, stop_ptr] : stops) {
        auto from = graphCache.name_to_vertex_id.at(stop_name).first;
        auto to = graphCache.name_to_vertex_id.at(stop_name).second;
        auto edge = newWeightGraph.AddEdge({from,
                                        to,
                                        params.waiting_time});
        graphCache.edges[edge] = {true, params.waiting_time, 0, "no", from, to};
    }
    for (const auto& [bus_name, bus_ptr] : buses) {
        if (bus_ptr->GetType() == Bus::BusType::CYCLE) {
           MakeWeightsFromCycleBus(newWeightGraph, bus_ptr);
        }
        if (bus_ptr->GetType() == Bus::BusType::LINEAR) {
            MakeWeightsFromLinearBus(newWeightGraph, bus_ptr);
        }
    }
    return newWeightGraph;
}

void Database::MakeWeightsFromCycleBus(Graph::DirectedWeightedGraph<WeightType> &graph,
                                       const std::shared_ptr<Bus> &ptr) const {
    auto stop_names = ptr->getStopNames();
    for (size_t i = 0; i < stop_names.size() - 1; ++i) {
        double accumulate_time = 0;
        int span_count = 0;
        for (size_t j = i + 1; j < stop_names.size(); ++j) {
            accumulate_time += stops.at(stop_names[j - 1])->getDistanceToStop().at(stop_names[j]) * 1.0 / params.velocity;
            span_count++;
            auto from = graphCache.name_to_vertex_id.at(stop_names[i]).second;
            auto to = graphCache.name_to_vertex_id.at(stop_names[j]).first;
            auto edge = graph.AddEdge({from,
                                       to,
                                       accumulate_time});
            graphCache.edges[edge] = {false, accumulate_time, span_count, ptr->getName(), from, to};
        }
    }

}

void Database::MakeWeightsFromLinearBus(Graph::DirectedWeightedGraph<WeightType> &graph,
                                        const std::shared_ptr<Bus> &ptr) const {
    auto stop_names = ptr->getStopNames();
    for (int64_t i = 0; i < stop_names.size(); ++i) {
        double accumulate_time_str = 0;
        int span_count_str = 0;
        double accumulate_time_rev = 0;
        int span_count_rev = 0;
        for (int64_t j = i - 1; j >= 0; --j) {
            accumulate_time_rev += stops.at(stop_names[j + 1])->getDistanceToStop().at(stop_names[j]) * 1.0 / params.velocity;
            span_count_rev++;
            auto from = graphCache.name_to_vertex_id.at(stop_names[i]).second;
            auto to = graphCache.name_to_vertex_id.at(stop_names[j]).first;
            auto edge = graph.AddEdge({from,
                                       to,
                                       accumulate_time_rev});
            graphCache.edges[edge] = {false, accumulate_time_rev, span_count_rev, ptr->getName(), from, to};
        }
        for (int64_t j = i + 1; j < stop_names.size(); ++j) {
            accumulate_time_str += stops.at(stop_names[j - 1])->getDistanceToStop().at(stop_names[j]) * 1.0 / params.velocity;
            span_count_str++;
            auto from = graphCache.name_to_vertex_id.at(stop_names[i]).second;
            auto to = graphCache.name_to_vertex_id.at(stop_names[j]).first;
            auto edge = graph.AddEdge({from,
                                       to,
                                       accumulate_time_str});
            graphCache.edges[edge] = {false, accumulate_time_str, span_count_str, ptr->getName(), from, to};
        }
    }
}

void Database::AddStops() const {
    for (const auto& [stop_name, stop_ptr] : stops) {
        graphCache.name_to_vertex_id[stop_name] = {graphCache.curr_id, graphCache.curr_id + 1};
        graphCache.vertex_id_to_name[graphCache.curr_id] = {stop_name, "start"};
        graphCache.vertex_id_to_name[graphCache.curr_id + 1] = {stop_name, "end"};
        graphCache.curr_id += 2;
    }
}

Database::Database() {
    params = {1, 1};
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
