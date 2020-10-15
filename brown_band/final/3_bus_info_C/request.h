#pragma once

#include <memory>
#include <sstream>
#include <iomanip>
#include "database.h"

std::vector<std::string> SplitBy(std::string_view s, char split = '.');
std::string Strip(std::string_view str);

class Request;

using RequestHolder = std::unique_ptr<Request>;

class Request {
public:
    enum RequestType {
        ADD_STOP,
        ADD_ROUTE,
        GET_ROUTE,
        GET_STOP
    };

    explicit Request(RequestType type) : type(type) {}

    virtual void ParseFrom(std::string_view input) = 0;

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

    virtual std::string ResultToString(const Result& result) const = 0;
};

class ModifyRequest : public Request {
public:
    using Request::Request;
    virtual void Process( Database& db) const = 0;

    void ParseFrom(std::string_view input) override = 0;
};

class AddStopRequest : public ModifyRequest {
public:
    AddStopRequest() : ModifyRequest(Request::RequestType::ADD_STOP) {}
    void ParseFrom(std::string_view input) override;
    void Process(Database &db) const override;

private:
    std::string stop_name;
    std::unordered_map<std::string, double> distances;
    double latitude, longitude;
};

class AddRouteRequest: public ModifyRequest {
public:
    AddRouteRequest(): ModifyRequest(Request::RequestType::ADD_ROUTE) {}

    void Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;

private:
    std::string route_name;
    Route::RouteType route_type;
    std::vector<std::string> stop_names;
};

struct GetRouteAnswer {
    bool has_value;
    std::string name;
    int stops_count;
    int unique_stops_count;
    double length;
    double curvature;
};

struct GetStopAnswer {
    bool has_value;
    std::string name;
    std::vector<std::string> buses;
};
class GetRouteRequest: public GetRequest<GetRouteAnswer> {
public:
    GetRouteRequest():GetRequest(Request::RequestType::GET_ROUTE) {}

    GetRouteAnswer Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;

    std::string ResultToString(const GetRouteAnswer &result) const override;

private:
    std::string route_name;
};

class GetStopRequest: public GetRequest<GetStopAnswer> {
public:
    GetStopRequest():GetRequest(Request::RequestType::GET_STOP) {}

    GetStopAnswer Process(Database &db) const override;

    void ParseFrom(std::string_view input) override;

    std::string ResultToString(const GetStopAnswer &result) const override;

private:
    std::string stop_name;
};