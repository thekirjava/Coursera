#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <list>

#include "json.h"
#include "request.h"
#include "database.h"
#include "route.h"
#include "map.h"

namespace TransportDatabase {
    void PrintResults(const std::vector<std::string> &results, std::ostream &out = std::cout);
    class DatabaseManager {
    public:
        DatabaseManager();
        explicit DatabaseManager(std::shared_ptr<Database> db);
        void changeDatabase(std::shared_ptr<Database> db);
        Json::Node processAllJsonRequests(std::istream &in = std::cin);
        Json::Node processJsonReadRequest(const Json::Node &node);
        Json::Node processJsonModifyRequest(const Json::Node &node);
    private:

        RenderParams extractRenderParams(const Json::Node& node);

        Json::Node makeJsonAnswerFromAnyRequest(RequestHolder request);
        RequestHolder parseModifyJsonRequest(const Json::Node &node);
        RequestHolder parseReadJsonRequest(const Json::Node &node);

        template<typename RequestType>
        RequestHolder parseRequest(RequestType type, std::string_view request_str);
        template<typename RequestType>
        RequestHolder jsonRequest(RequestType type, const Json::Node &node);

        std::shared_ptr<Database> db_;
        std::shared_ptr<Route> router;
        std::shared_ptr<Map> render;
    };
}