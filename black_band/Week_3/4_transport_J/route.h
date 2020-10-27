#pragma once
#include <memory>
#include <list>
#include <optional>

#include "graph.h"
#include "router.h"
#include "linker.h"

namespace TransportDatabase {
    enum class NodeType {INFO, WAIT, BUS};
    struct BaseNode {
        BaseNode() = default;
        BaseNode(NodeType t) : type(t) {}
        virtual ~BaseNode() = default;
        NodeType type;
    };

    struct InfoNode : public BaseNode {
        using BaseNode::BaseNode;
        InfoNode() = default;
        InfoNode(double val) : BaseNode(NodeType::INFO), total_time(val) {}
        std::optional<double> total_time;
    };

    struct WaitNode : public BaseNode {
        using BaseNode::BaseNode;
        WaitNode() = default;
        WaitNode(const std::string& stop_name_, double time_)
                : BaseNode(NodeType::WAIT), stop_name(stop_name_), time(time_) {}
        std::string stop_name;
        double time;
    };

    struct BusNode : public BaseNode {
        using BaseNode::BaseNode;
        BusNode() = default;
        BusNode(const std::string& route_name_, int span_count_, double time_)
                : BaseNode(NodeType::BUS), route_name(route_name_), span_count(span_count_), time(time_) {}
        std::string route_name;
        int span_count;
        double time;
    };

    struct RoutingParam {
        double velocity;
        double waiting_time;
    };

    class Route : public Linker {
        using WeightType = double;
        struct Edge {
            bool is_wait_edge;
            WeightType weight;
            int span_count;
            std::string bus_name;
            Graph::VertexId from;
            Graph::VertexId to;
        };
    public:
        Route();
        Route(std::shared_ptr<Database> db, const RoutingParam& rp);
        void changeDatabase(std::shared_ptr<Database> db) override;
        void changeRoutingParams(const RoutingParam& rp);
        std::list<std::unique_ptr<BaseNode>> createRoute(const std::string &first_stop, const std::string &second_stop) const;
        void updateGraph();
        RoutingParam routing_param;
    private:

        void addStops();
        void rebase();
        void rebaseGraph();
        void rebaseRouter();

        void makeWeightFromCycleRoute(Graph::DirectedWeightedGraph<WeightType>& graph, const std::shared_ptr<Bus>& ptr);
        void makeWeightFromLinearRoute(Graph::DirectedWeightedGraph<WeightType>& graph, const std::shared_ptr<Bus>& ptr);

        double Velocity() const;
        std::unique_ptr<Graph::DirectedWeightedGraph<WeightType>> graph = nullptr;
        std::unique_ptr<Graph::Router<WeightType>> router = nullptr;

        Graph::VertexId curr_id = 0;
        std::unordered_map<std::string, std::pair<Graph::VertexId, Graph::VertexId>> name_to_vertex_id;
        std::unordered_map<Graph::VertexId, std::pair<std::string, std::string>> vertex_id_to_name;
        std::unordered_map<Graph::EdgeId, Edge> edges;
    };
}
