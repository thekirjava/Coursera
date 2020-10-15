#include "route.h"

#include <utility>

namespace TransportDatabase {
    Route::Route() {
        changeRoutingParams({0, 0});
    }

    Route::Route(std::shared_ptr<Database> db, const RoutingParam& rp) : Linker(std::move(db)) {
        changeRoutingParams(rp);
        rebase();
    }

    void Route::changeDatabase(std::shared_ptr<Database> db) {
        Linker::changeDatabase(db);
        rebase();
    }

    void Route::changeRoutingParams(const RoutingParam &rp) {
        routing_param.velocity = rp.velocity;
        routing_param.waiting_time = rp.waiting_time;
    }

    std::list<std::unique_ptr<BaseNode>> Route::createRoute(const std::string& first_stop,
                                                            const std::string& second_stop) const {
        if (!graph) throw std::runtime_error("graph in database router not set");
        if (!router) throw std::runtime_error("router in database router not set");
        auto route = router->BuildRoute(name_to_vertex_id.at(first_stop).first,name_to_vertex_id.at(second_stop).first);
        std::list<std::unique_ptr<BaseNode>> nodes;
        if (!route) {
            nodes.push_back(std::make_unique<InfoNode>());
            return nodes;
        }
        nodes.push_back(std::make_unique<InfoNode>(route->weight));
        for (size_t i = 0; i < route->edge_count; ++i) {
            Graph::EdgeId edge_id = router->GetRouteEdge(route->id, i);
            Edge edge = edges.at(edge_id);
            if (edge.is_wait_edge) {
                nodes.push_back(std::make_unique<WaitNode>(vertex_id_to_name.at(edge.from).first,
                                                           edge.weight));
            }
            else {
                nodes.push_back(std::make_unique<BusNode>(edge.bus_name, edge.span_count, edge.weight));
            }
        }
        return nodes;
    }

    void Route::updateGraph() {
        rebase();
    }

    void Route::rebase() {
        name_to_vertex_id.clear();
        vertex_id_to_name.clear();
        edges.clear();
        curr_id = 0;
        addStops();
        rebaseGraph();
        rebaseRouter();
    }

    void Route::rebaseGraph() {
        auto new_graph = Graph::DirectedWeightedGraph<WeightType>(name_to_vertex_id.size() * 2);
        auto& stops = db_->getStops();
        for (const auto& [stop_name, stop_ptr] : stops) {
            auto from = name_to_vertex_id.at(stop_name).first;
            auto to = name_to_vertex_id.at(stop_name).second;
            auto edge = new_graph.AddEdge({from,
                                           to,
                                           routing_param.waiting_time});
            edges[edge] = {true, routing_param.waiting_time, 0, "no", from, to};
        }
        auto& buses = db_->getBuses();
        for (const auto& [bus_name, bus_ptr] : buses) {
            if (bus_ptr->bus_type == Bus::BusTypes::CYCLE) {
                makeWeightFromCycleRoute(new_graph, bus_ptr);
            }
            if (bus_ptr->bus_type == Bus::BusTypes::LINEAR) {
                makeWeightFromLinearRoute(new_graph, bus_ptr);
            }
        }
        graph = std::make_unique<Graph::DirectedWeightedGraph<WeightType>>(std::move(new_graph));
    }

    void Route::rebaseRouter() {
        router = std::make_unique<Graph::Router<WeightType>>(Graph::Router(*graph));
    }

    void Route::makeWeightFromCycleRoute(Graph::DirectedWeightedGraph<WeightType> &graph,
                                         const std::shared_ptr<Bus> &ptr) {
        auto& stops = db_->getStops();
        auto stop_names = ptr->getStopsName();
        for (size_t i = 0; i < stop_names.size() - 1; ++i) {
            double accumulate_time = 0;
            int span_count = 0;
            for (size_t j = i + 1; j < stop_names.size(); ++j) {
                accumulate_time += stops.at(stop_names[j - 1])->distance_to_stop.at(stop_names[j]) * 1.0 / Velocity();
                span_count++;
                auto from = name_to_vertex_id.at(stop_names[i]).second;
                auto to = name_to_vertex_id.at(stop_names[j]).first;
                auto edge = graph.AddEdge({from,
                                           to,
                                           accumulate_time});
                edges[edge] = {false, accumulate_time, span_count, ptr->getName(), from, to};
            }
        }
    }

// TODO Возможно нужно переделать
    void Route::makeWeightFromLinearRoute(Graph::DirectedWeightedGraph<WeightType> &graph,
                                          const std::shared_ptr<Bus> &ptr) {
        auto& stops = db_->getStops();
        auto stop_names = ptr->getStopsName();
        for (int64_t i = 0; i < stop_names.size(); ++i) {
            double accumulate_time_str = 0;
            int span_count_str = 0;
            double accumulate_time_rev = 0;
            int span_count_rev = 0;
            for (int64_t j = i - 1; j >= 0; --j) {
                accumulate_time_rev += stops.at(stop_names[j + 1])->distance_to_stop.at(stop_names[j]) * 1.0 / Velocity();
                span_count_rev++;
                auto from = name_to_vertex_id.at(stop_names[i]).second;
                auto to = name_to_vertex_id.at(stop_names[j]).first;
                auto edge = graph.AddEdge({from,
                                           to,
                                           accumulate_time_rev});
                edges[edge] = {false, accumulate_time_rev, span_count_rev, ptr->getName(), from, to};
            }
            for (int64_t j = i + 1; j < stop_names.size(); ++j) {
                accumulate_time_str += stops.at(stop_names[j - 1])->distance_to_stop.at(stop_names[j]) * 1.0 / Velocity();
                span_count_str++;
                auto from = name_to_vertex_id.at(stop_names[i]).second;
                auto to = name_to_vertex_id.at(stop_names[j]).first;
                auto edge = graph.AddEdge({from,
                                           to,
                                           accumulate_time_str});
                edges[edge] = {false, accumulate_time_str, span_count_str, ptr->getName(), from, to};
            }
        }
    }

    void Route::addStops() {
        auto& stops = db_->getStops();
        for (const auto& [stop_name, stop_ptr] : stops) {
            name_to_vertex_id[stop_name] = {curr_id, curr_id + 1};
            vertex_id_to_name[curr_id] = {stop_name, "start"};
            vertex_id_to_name[curr_id + 1] = {stop_name, "end"};
            curr_id += 2;
        }
    }

    double Route::Velocity() const {
        return routing_param.velocity * 1000.0 / 60.0;
    }
}