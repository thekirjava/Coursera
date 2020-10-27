#pragma once
#include <string>
#include <optional>

#include "json.h"
#include "database.h"
#include "route.h"
#include "map.h"

namespace TransportDatabase {

    std::vector<std::string> splitBy(std::string_view s, char split = '.');
    std::string strip(std::string_view str);

    class Request;
    using RequestHolder = std::unique_ptr<Request>;
    class Request {
    public:
        enum class Type {
            ADD_BUS,
            ADD_STOP,
            GET_BUS,
            GET_STOP,
            CREATE_ROUTE,
            CREATE_MAP
        };
        explicit Request(Type type) : type_(type) {}
        virtual void parseFromJson(const Json::Node& node) = 0;
        virtual ~Request() = default;

        static RequestHolder create(Request::Type type);

        Type getType() const {
            return type_;
        }
    private:
        Type type_;
    };

    template <typename Result, typename Processor>
    class ReadRequest : public Request {
    public:
        using Request::Request;
        void parseFromJson(const Json::Node& node) override = 0;
        virtual Result process(Processor &db) const = 0;
        virtual Json::Node jsonAnswer(const Result& result) const = 0;
    protected:
        int request_id = 0;
    };

    template <typename Processor>
    class ModifyRequest : public Request {
    public:
        using Request::Request;
        virtual void process(Processor& db) const = 0;
    };

    class AddStopRequest : public ModifyRequest<Database> {
    public:
        AddStopRequest() : ModifyRequest(Request::Type::ADD_STOP) {}
        void parseFromJson(const Json::Node& node) override;
        void process(Database& db) const override;
    private:
        std::string stop_name;
        double latitude, longitude;
        std::vector<std::pair<std::string, int>> distances;
    };

    class AddBusRequest : public ModifyRequest<Database> {
    public:
        AddBusRequest() : ModifyRequest(Request::Type::ADD_BUS) {}
        void parseFromJson(const Json::Node& node) override;
        void process(Database& db) const override;
    private:
        std::string bus_name;
        Bus::BusTypes bus_type;
        std::vector<std::string> stops_name;
    };

    struct GetBusAnswer {
        int id;
        bool has_value;
        std::string bus_name;
        size_t stops_count;
        size_t unique_stops_count;
        double length;
        double curvature;
    };

    class GetBusRequest : public ReadRequest<GetBusAnswer, Database> {
    public:
        GetBusRequest() : ReadRequest(Request::Type::GET_BUS) {}
        void parseFromJson(const Json::Node& node) override;
        GetBusAnswer process(Database& db) const override;
        Json::Node jsonAnswer(const GetBusAnswer& result) const override;
    private:
        std::string bus_name;
    };

    struct GetStopAnswer {
        int id;
        bool in_base;
        std::string stop_name;
        std::vector<std::string> names;
    };

    class TakeStopRequest : public ReadRequest<GetStopAnswer, Database> {
    public:
        TakeStopRequest() : ReadRequest(Request::Type::GET_STOP) {}
        void parseFromJson(const Json::Node& node) override;
        GetStopAnswer process(Database& db) const override;
        Json::Node jsonAnswer(const GetStopAnswer& result) const override;
    private:
        std::string stop_name;
    };

    struct CreateRouteAnswer {
        int id;
        bool has_route;
        double total_time;
        std::list<std::unique_ptr<BaseNode>> nodes;
    };

    class CreateRouteRequest : public ReadRequest<CreateRouteAnswer, Route> {
    public:
        CreateRouteRequest() : ReadRequest(Request::Type::CREATE_ROUTE) {}
        void parseFromJson(const Json::Node& node) override;
        CreateRouteAnswer process(Route& db) const override;
        Json::Node jsonAnswer(const CreateRouteAnswer& result) const override;
    private:
        std::string from;
        std::string to;
    };

    struct CreateMapAnswer {
        int id;
        std::string svg;
    };

    class CreateMapRequest : public ReadRequest<CreateMapAnswer, Map> {
    public:
        CreateMapRequest() : ReadRequest(Request::Type::CREATE_MAP) {}
        void parseFromJson(const Json::Node& node) override;
        CreateMapAnswer process(Map& db) const override;
        Json::Node jsonAnswer(const CreateMapAnswer& result) const override;
    };
}
