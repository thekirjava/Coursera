#pragma once

#include <memory>
#include <sstream>
#include <iomanip>
#include "database.h"
#include "json.h"
std::vector<std::string> SplitBy(std::string_view s, char split = '.');
std::string Strip(std::string_view str);

class Request;

using RequestHolder = std::unique_ptr<Request>;

class Request {
public:
    enum RequestType {
        ADD_STOP,
        ADD_BUS,
        GET_BUS,
        GET_STOP,
        GET_ROUTE
    };

    explicit Request(RequestType type) : type(type) {}

    virtual void ParseFrom(std::string_view input) = 0;

    virtual void ParseFromJSON(const Json::Node& node) = 0;

    virtual ~Request() = default;

    RequestType getType() const;

    static RequestHolder Create(RequestType type);

private:
    RequestType type;
};

template<typename Result>
class GetRequest : public Request {
public:
    using Request::Request;
    virtual Result Process(Database &db) const = 0;

    void ParseFrom(std::string_view input) override = 0;
    void ParseFromJSON(const Json::Node& node) override = 0;
    virtual std::string ResultToString(const Result& result) const = 0;
    virtual Json::Node ResultToJSON(const Result& result) const = 0;

protected:
    int request_id = -1;
};

class ModifyRequest : public Request {
public:
    using Request::Request;
    virtual void Process( Database& db) const = 0;
    void ParseFromJSON(const Json::Node& node) override = 0;
    void ParseFrom(std::string_view input) override = 0;
};

class AddStopRequest : public ModifyRequest {
public:
    AddStopRequest() : ModifyRequest(Request::RequestType::ADD_STOP) {}
    void ParseFrom(std::string_view input) override;

    void ParseFromJSON(const Json::Node &node) override;

    void Process(Database &db) const override;

private:
    std::string stop_name;
    std::unordered_map<std::string, double> distances;
    double latitude, longitude;
};

class AddBusRequest: public ModifyRequest {
public:
    AddBusRequest(): ModifyRequest(Request::RequestType::ADD_BUS) {}

    void Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;
    void ParseFromJSON(const Json::Node& node) override;

private:
    std::string bus_name;
    Bus::BusType bus_type;
    std::vector<std::string> stop_names;
};

struct GetBusAnswer {
    int request_id;
    bool has_value;
    std::string name;
    int stops_count;
    int unique_stops_count;
    double length;
    double curvature;
};

struct GetStopAnswer {
    int request_id;
    bool has_value;
    std::string name;
    std::vector<std::string> buses;
};

struct GetRouteAnswer {
    int id;
    bool has_value;
    double total_time;
    std::list<std::unique_ptr<BaseNode>> nodes;
};
class GetBusRequest: public GetRequest<GetBusAnswer> {
public:
    GetBusRequest(): GetRequest(Request::RequestType::GET_BUS) {}

    GetBusAnswer Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;
    void ParseFromJSON(const Json::Node& node) override;

    std::string ResultToString(const GetBusAnswer &result) const override;

    Json::Node ResultToJSON(const GetBusAnswer &result) const override;

private:
    std::string bus_name;
};

class GetStopRequest: public GetRequest<GetStopAnswer> {
public:
    GetStopRequest():GetRequest(Request::RequestType::GET_STOP) {}

    GetStopAnswer Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;
    void ParseFromJSON(const Json::Node& node) override;

    std::string ResultToString(const GetStopAnswer &result) const override;

    Json::Node ResultToJSON(const GetStopAnswer &result) const override;

private:
    std::string stop_name;
};

class GetRouteRequest: public GetRequest<GetRouteAnswer> {
public:
    GetRouteRequest():GetRequest(Request::RequestType::GET_ROUTE) {}

    GetRouteAnswer Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;

    void ParseFromJSON(const Json::Node &node) override;

    std::string ResultToString(const GetRouteAnswer &result) const override;

    Json::Node ResultToJSON(const GetRouteAnswer &result) const override;
private:
    std::string from;
    std::string to;
};