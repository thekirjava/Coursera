#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "request.h"
#include "database.h"

void PrintResults(const std::vector<std::string> &result, std::ostream & out = std::cout);
class BusManager {
public:
    BusManager() = delete;

    explicit BusManager(Database &db) : db(db) {}

    std::vector<std::string> ProcessAll(std::istream &in = std::cin);

private:
    template<typename Number>
    Number readNumber(std::istream& in);
    std::string ProcessGetRequest(const std::string& get);
    std::string ProcessModifyRequest(const std::string& mod);

    std::string MakeAnswerFromRequest(RequestHolder request);
    RequestHolder ParseModifyRequest(std::string_view request);
    RequestHolder ParseAddStop(std::string_view request);
    RequestHolder ParseAddRoute(std::string_view request);

    RequestHolder ParseGetRequest(std::string_view request);
    RequestHolder ParseGetRoute(std::string_view request);
    Database &db;
};

template<typename Number>
Number BusManager::readNumber(std::istream &in) {
    Number number;
    in >> number;
    std::string buf;
    std::getline(in, buf);
    return number;
}