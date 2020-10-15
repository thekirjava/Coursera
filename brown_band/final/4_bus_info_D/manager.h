#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "request.h"
#include "database.h"

void PrintResults(const std::vector<std::string> &result, std::ostream & out = std::cout);
class TransportManager {
public:
    TransportManager() = delete;

    explicit TransportManager(Database &db) : db(db) {}

    std::vector<std::string> ProcessAll(std::istream &in = std::cin);
    Json::Node ProcessAllJSON(std::istream &in = std::cin);

private:
    template<typename Number>
    Number readNumber(std::istream& in);
    std::string ProcessGetRequest(const std::string& get);
    std::string ProcessModifyRequest(const std::string& mod);

    std::string MakeAnswerFromRequest(RequestHolder request);
    RequestHolder ParseModifyRequest(std::string_view request);
    RequestHolder ParseAddStop(std::string_view request);
    RequestHolder ParseAddBus(std::string_view request);

    RequestHolder ParseGetRequest(std::string_view request);
    RequestHolder ParseGetBus(std::string_view request);
    RequestHolder ParseGetStop(std::string_view request);

    Json::Node ProcessGetRequestJSON(const Json::Node& get);
    Json::Node ProcessModifyRequestJSON(const Json::Node& mod);

    Json::Node MakeAnswerFromRequestJSON(RequestHolder request);
    RequestHolder ParseModifyRequestJSON(const Json::Node& request);
    RequestHolder ParseAddStopJSON(const Json::Node& request);
    RequestHolder ParseAddBusJSON(const Json::Node& request);

    RequestHolder ParseGetRequestJSON(const Json::Node& request);
    RequestHolder ParseGetBusJSON(const Json::Node& request);
    RequestHolder ParseGetStopJSON(const Json::Node& request);
    Database &db;
};

template<typename Number>
Number TransportManager::readNumber(std::istream &in) {
    Number number;
    in >> number;
    std::string buf;
    std::getline(in, buf);
    return number;
}