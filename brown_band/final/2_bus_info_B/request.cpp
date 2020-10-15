#include "request.h"

std::vector<std::string> SplitBy(std::string_view s, char split) {
    std::vector<std::string> ans;
    size_t i = 0;
    while (i != std::string_view::npos) {
        auto length = s.find(split, i);
        ans.emplace_back(s.substr(i, length - i));
        if (length != std::string_view::npos) {
            i = length + 1;
        } else {
            i = std::string_view::npos;
        }
    }
    return ans;
}

std::string Strip(std::string_view str) {
    size_t left_border = 0;
    while (str[left_border] == ' ') {
        left_border++;
    }
    size_t right_border = str.size() - 1;
    while (str[right_border] == ' ') {
        right_border--;
    }
    return std::string(str.substr(left_border, right_border - left_border + 1));
}

Request::RequestType Request::getType() const {
    return type;
}

RequestHolder Request::Create(Request::RequestType type) {
    switch (type) {
        case ADD_STOP:
            return std::make_unique<AddStopRequest>();
        case ADD_ROUTE:
            return std::make_unique<AddRouteRequest>();
        case GET_ROUTE:
            return std::make_unique<GetRouteRequest>();
        case GET_STOP:
            return std::make_unique<GetStopRequest>();
        default:
            return nullptr;
    }
}

void AddStopRequest::Process(Database &db) const {
    db.AddStop({stop_name, CoordinatesBuilder().setLatitude(latitude).setLongitude(longitude).Build()});
}

void AddStopRequest::ParseFrom(std::string_view input) {
    size_t name = input.find(':');
    stop_name = Strip(input.substr(0, name));
    size_t comma = input.find(',', name + 2);
    latitude = std::stod(std::string(input.substr(name + 2, comma)));
    longitude = std::stod(std::string(input.substr(comma + 1)));
}

void AddRouteRequest::Process(Database &db) const {
    db.AddRoute(route_name,
                RouteBuilder(db).MakeRoute({route_type, route_name, stop_names}));
}

void AddRouteRequest::ParseFrom(std::string_view input) {
    size_t name = input.find(':');
    route_name = Strip(input.substr(0, name));
    std::vector<char> types = {'-', '>'};
    char type = '-';
    for (auto t : types) {
        size_t delim_pos = input.find(t);
        if (delim_pos != input.npos) {
            type = t;
            break;
        }
    }
    if (type == '-') {
        route_type = Route::RouteType::LINEAR;
    } else {
        route_type = Route::RouteType::CYCLE;
    }
    auto tokens = SplitBy(input.substr(name + 2), type);
    stop_names.reserve(tokens.size());
    for (auto &token : tokens) {
        std::string stop;
        stop = Strip(token);
        stop_names.push_back(stop);
    }
}

GetRouteAnswer GetRouteRequest::Process(Database &db) const {
    auto route = db.GetRoute(route_name);
    if (route) {
        return {true, route_name, route->StopsCount(), route->UniqueStopsCount(), route->Length()};
    } else {
        return {false, route_name, 0, 0, 0};
    }
}

void GetRouteRequest::ParseFrom(std::string_view input) {
    route_name = input;
}

std::string GetRouteRequest::ResultToString(const GetRouteAnswer &result) const {
    std::stringstream s;
    if (result.has_value) {
        s << std::fixed << std::setprecision(6) << "Bus " << result.name << ": " << result.stops_count
          << " stops on route, " <<
          result.unique_stops_count << " unique stops, " << result.length << " route length";
    } else {
        s << "Bus " << result.name << ": not found";
    }
    return s.str();
}

GetStopAnswer GetStopRequest::Process(Database &db) const {
    auto stop = db.GetStop(stop_name);
    if (stop) {
        return {true, stop_name, stop->getRoutes()};
    } else {
        return {false, stop_name, std::vector<std::string>()};
    }
}

void GetStopRequest::ParseFrom(std::string_view input) {
    stop_name = input;
}

std::string GetStopRequest::ResultToString(const GetStopAnswer &result) const {
    std::stringstream ss;
    if (result.has_value) {
        if (result.buses.empty()) {
            ss << "Stop " << stop_name << ": no buses";
        } else {
            ss << "Stop " << stop_name << ": buses";
            for (const auto &bus:result.buses) {
                ss << " " << bus;
            }
        }
    } else {
        ss << "Stop " << stop_name << ": not found";
    }
    return ss.str();
}
