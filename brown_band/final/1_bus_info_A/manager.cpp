#include "manager.h"

std::vector<std::string> BusManager::ProcessAll(std::istream &in) {
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

std::string BusManager::ProcessGetRequest(const std::string &get) {
    return MakeAnswerFromRequest(ParseGetRequest(get));
}

std::string BusManager::ProcessModifyRequest(const std::string &mod) {
    return MakeAnswerFromRequest(ParseModifyRequest(mod));
}

std::string BusManager::MakeAnswerFromRequest(RequestHolder request) {
    switch (request->getType()) {
        case Request::ADD_STOP: {
            const auto &cast_request = dynamic_cast<ModifyRequest &>(*request);
            cast_request.Process(db);
            return "Stop added";
        }
        case Request::ADD_ROUTE: {
            const auto &cast_request = dynamic_cast<ModifyRequest &>(*request);
            cast_request.Process(db);
            return "Route added";
        }
        case Request::GET_ROUTE: {
            const auto& cast_request = dynamic_cast<GetRequest<GetRouteAnswer>&>(*request);
            const auto ans = cast_request.Process(db);
            return cast_request.ResultToString(ans);
        }
        default:
            return "error";
    }
}

RequestHolder BusManager::ParseModifyRequest(std::string_view request) {
    char split = ' ';
    size_t first_space = request.find(split);
    std::string_view type = request.substr(0, first_space);
    if (type == "Stop") {
        return ParseAddStop(request.substr(first_space + 1));
    }
    else if (type == "Bus") {
        return ParseAddRoute(request.substr(first_space + 1));
    }
    else {
        return nullptr;
    }
}

RequestHolder BusManager::ParseAddStop(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::ADD_STOP);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}

RequestHolder BusManager::ParseAddRoute(std::string_view request) {
    auto request_ptr = Request::Create(Request::RequestType::ADD_ROUTE);
    if (request_ptr) {
        request_ptr->ParseFrom(request);
    }
    return request_ptr;
}

RequestHolder BusManager::ParseGetRequest(std::string_view request) {
    char split = ' ';
    size_t first_space = request.find(split);
    std::string_view type = request.substr(0, first_space);
    if (type == "Bus") {
        return ParseGetRoute(request.substr(first_space + 1));
    }
    else {
        return nullptr;
    }
}

RequestHolder BusManager::ParseGetRoute(std::string_view request) {
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
