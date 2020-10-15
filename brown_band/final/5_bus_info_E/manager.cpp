#include "manager.h"

std::vector<std::string> TransportManager::ProcessAll(std::istream &in) {
    std::vector<std::string> ans;
    int N = readNumber<int>(in);
    ans.reserve(N);
    for (int i = 0; i < N; i++) {
        std::string request;
        std::getline(in, request);
        auto answer = ProcessModifyRequest(request);
        std::cerr << answer << '\n';
    }
    int M = readNumber<int>(in);
    ans.reserve(M);
    for (int i = 0; i < M; i++) {
        std::string request;
        std::getline(in, request);
        auto answer = ProcessGetRequest(request);
        std::cerr << answer << '\n';
        ans.emplace_back(answer);
    }
    return ans;
}

Json::Node TransportManager::ProcessAllJSON(std::istream &in) {
    auto doc = Json::Load(in);
    auto global_map = doc.GetRoot().AsMap();
    const std::string SETTINGS = "routing_settings";
    Json::Node params_request = global_map.at(SETTINGS);
    db.setParams({params_request.AsMap().at("bus_velocity").AsInt() * 1000.0 / 60.0, static_cast<double>(params_request.AsMap().at("bus_wait_time").AsInt())});
    const std::string MODIFY = "base_requests";
    Json::Node modify_requests = global_map.at(MODIFY);
    const std::string READ = "stat_requests";
    Json::Node get_requests = global_map.at(READ);
    for (const auto &node:modify_requests.AsArray()) {
        ProcessModifyRequestJSON(node);
    }
    std::vector<Json::Node> ans;
    for (const auto &node:get_requests.AsArray()) {
        ans.push_back(ProcessGetRequestJSON(node));
    }
    return Json::Node(ans);
}

std::string TransportManager::ProcessGetRequest(const std::string &get) {
    return MakeAnswerFromRequest(ParseGetRequest(get));
}

Json::Node TransportManager::ProcessGetRequestJSON(const Json::Node& get) {
    return MakeAnswerFromRequestJSON(ParseGetRequestJSON(get));
}

std::string TransportManager::ProcessModifyRequest(const std::string &mod) {
    return MakeAnswerFromRequest(ParseModifyRequest(mod));
}

Json::Node TransportManager::ProcessModifyRequestJSON(const Json::Node &mod) {
    return MakeAnswerFromRequestJSON(ParseModifyRequestJSON(mod));
}

std::string TransportManager::MakeAnswerFromRequest(RequestHolder request) {
    switch (request->getType()) {
        case Request::ADD_STOP: {
            const auto &cast_request = dynamic_cast<ModifyRequest &>(*request);
            cast_request.Process(db);
            return "Stop added";
        }
        case Request::ADD_BUS: {
            const auto &cast_request = dynamic_cast<ModifyRequest &>(*request);
            cast_request.Process(db);
            return "Bus added";
        }
        case Request::GET_BUS: {
            const auto &cast_request = dynamic_cast<GetRequest<GetBusAnswer> &>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToString(ans);
        }
        case Request::GET_STOP: {
            const auto &cast_request = dynamic_cast<GetRequest<GetStopAnswer> &>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToString(ans);
        }
        case Request::GET_ROUTE: {
            const auto &cast_request = dynamic_cast<GetRequest<GetRouteAnswer> &>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToString(ans);
        }
        default:
            return "error";
    }
}

Json::Node TransportManager::MakeAnswerFromRequestJSON(RequestHolder request) {
    switch (request->getType()) {
        case Request::ADD_STOP: {
            const auto &cast_request = dynamic_cast<ModifyRequest &>(*request);
            cast_request.Process(db);
            return Json::Node("Stop added");
        }
        case Request::ADD_BUS: {
            const auto &cast_request = dynamic_cast<ModifyRequest &>(*request);
            cast_request.Process(db);
            return Json::Node("Bus added");
        }
        case Request::GET_BUS: {
            const auto &cast_request = dynamic_cast<GetRequest<GetBusAnswer> &>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToJSON(ans);
        }
        case Request::GET_STOP: {
            const auto &cast_request = dynamic_cast<GetRequest<GetStopAnswer> &>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToJSON(ans);
        }
        case Request::GET_ROUTE: {
            const auto &cast_request = dynamic_cast<GetRequest<GetRouteAnswer> &>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToJSON(ans);
        }
        default:
            return Json::Node("error");
    }
}

RequestHolder TransportManager::ParseModifyRequest(std::string_view request) {
    char split = ' ';
    size_t first_space = request.find(split);
    std::string_view type = request.substr(0, first_space);
    if (type == "Stop") {
        return ParseAddStop(request.substr(first_space + 1));
    } else if (type == "Bus") {
        return ParseAddBus(request.substr(first_space + 1));
    } else {
        return nullptr;
    }
}

RequestHolder TransportManager::ParseModifyRequestJSON(const Json::Node &request) {
    auto type = request.AsMap().at("type").AsString();
    if (type == "Stop") {
        return ParseAddStopJSON(request);
    } else if (type == "Bus") {
        return ParseAddBusJSON(request);
    } else {
        return nullptr;
    }
}

RequestHolder TransportManager::ParseAddStop(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::ADD_STOP);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseAddStopJSON(const Json::Node &request) {
    auto request_ptr = Request::Create(Request::RequestType::ADD_STOP);
    if (request_ptr) {
        request_ptr->ParseFromJSON(request);
    }
    return request_ptr;
}


RequestHolder TransportManager::ParseAddBus(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::ADD_BUS);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseAddBusJSON(const Json::Node &request) {
    auto request_ptr = Request::Create(Request::RequestType::ADD_BUS);
    if (request_ptr) {
        request_ptr->ParseFromJSON(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseGetRequest(std::string_view request) {
    char split = ' ';
    size_t first_space = request.find(split);
    std::string_view type = request.substr(0, first_space);
    if (type == "Bus") {
        return ParseGetBus(request.substr(first_space + 1));
    } else if (type == "Stop") {
        return ParseGetStop(request.substr(first_space + 1));
    } else {
        return nullptr;
    }
}

RequestHolder TransportManager::ParseGetRequestJSON(const Json::Node &request) {
    auto type = request.AsMap().at("type").AsString();
    if (type == "Stop") {
        return ParseGetStopJSON(request);
    } else if (type == "Bus") {
        return ParseGetBusJSON(request);
    } else if (type == "Route") {
        return ParseGetRouteJSON(request);
    } else {
        return nullptr;
    }
}

RequestHolder TransportManager::ParseGetBus(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::GET_BUS);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseGetBusJSON(const Json::Node &request) {
    auto request_ptr = Request::Create(Request::RequestType::GET_BUS);
    if (request_ptr) {
        request_ptr->ParseFromJSON(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseGetStop(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::GET_STOP);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseGetStopJSON(const Json::Node &request) {
    auto request_ptr = Request::Create(Request::RequestType::GET_STOP);
    if (request_ptr) {
        request_ptr->ParseFromJSON(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseGetRouteJSON(const Json::Node &request) {
    auto request_ptr = Request::Create(Request::RequestType::GET_ROUTE);
    if (request_ptr) {
        request_ptr->ParseFromJSON(request);
    }
    return request_ptr;
}

RequestHolder TransportManager::ParseGetRoute(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::GET_ROUTE);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}


void PrintResults(const std::vector<std::string> &result, std::ostream &out) {
    for (const auto &r:result) {
        out << r << '\n';
    }
}
