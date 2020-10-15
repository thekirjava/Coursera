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
        case ADD_BUS:
            return std::make_unique<AddBusRequest>();
        case GET_BUS:
            return std::make_unique<GetBusRequest>();
        case GET_STOP:
            return std::make_unique<GetStopRequest>();
        case GET_ROUTE:
            return std::make_unique<GetRouteRequest>();
        default:
            return nullptr;
    }
}

void AddStopRequest::Process(Database &db) const {
    db.AddStop({stop_name, CoordinatesBuilder().setLatitude(latitude).setLongitude(longitude).Build(), distances});
}

void AddStopRequest::ParseFrom(std::string_view input) {
    size_t name = input.find(':');
    stop_name = Strip(input.substr(0, name));
    auto tokens = SplitBy(input.substr(name + 2), ',');
    latitude = std::stod(Strip(tokens[0]));
    longitude = std::stod(Strip(tokens[1]));
    for (size_t i = 2; i < tokens.size(); ++i) {
        size_t m_pos = tokens[i].find('m');
        double distance = std::stod(Strip(tokens[i].substr(0, m_pos)));
        auto tail = tokens[i].substr(m_pos);
        size_t to_pos = tail.find('o');
        std::string stop_name = Strip(tail.substr(to_pos + 1));
        distances.insert({stop_name, distance});
    }
}

void AddStopRequest::ParseFromJSON(const Json::Node &node) {
    const auto &map_elem = node.AsMap();
    stop_name = map_elem.at("name").AsString();
    latitude = map_elem.at("latitude").AsDouble();
    longitude = map_elem.at("longitude").AsDouble();
    if (map_elem.count("road_distances") != 0) {
        for (const auto&[key, value]:map_elem.at("road_distances").AsMap()) {
            distances.insert({key, value.AsInt()});
        }
    }
}

void AddBusRequest::Process(Database &db) const {
    db.AddRoute(bus_name,
                BusBuilder(db).MakeBus({bus_type, bus_name, stop_names}));
}

void AddBusRequest::ParseFrom(std::string_view input) {
    size_t name = input.find(':');
    bus_name = Strip(input.substr(0, name));
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
        bus_type = Bus::BusType::LINEAR;
    } else {
        bus_type = Bus::BusType::CYCLE;
    }
    auto tokens = SplitBy(input.substr(name + 2), type);
    stop_names.reserve(tokens.size());
    for (auto &token : tokens) {
        std::string stop;
        stop = Strip(token);
        stop_names.push_back(stop);
    }
}

void AddBusRequest::ParseFromJSON(const Json::Node &node) {
    const auto &map_elem = node.AsMap();
    bus_name = map_elem.at("name").AsString();
    bus_type = map_elem.at("is_roundtrip").AsBool() ? Bus::BusType::CYCLE : Bus::BusType::LINEAR;
    stop_names.reserve(map_elem.at("stops").AsArray().size());
    for (const auto &value:map_elem.at("stops").AsArray()) {
        stop_names.emplace_back(value.AsString());
    }
}

GetBusAnswer GetBusRequest::Process(Database &db) const {
    auto route = db.GetBus(bus_name);
    if (route) {
        return {request_id, true, bus_name, route->StopsCount(), route->UniqueStopsCount(), route->Length(),
                route->Curvature()};
    } else {
        return {request_id, false, bus_name, 0, 0, 0, 0};
    }
}

void GetBusRequest::ParseFrom(std::string_view input) {
    bus_name = input;
}

std::string GetBusRequest::ResultToString(const GetBusAnswer &result) const {
    std::stringstream s;
    if (result.has_value) {
        s << std::fixed << std::setprecision(6) << "Bus " << result.name << ": " << result.stops_count
          << " stops on route, " <<
          result.unique_stops_count << " unique stops, " << result.length << " route length, " << result.curvature
          << " curvature";
    } else {
        s << "Bus " << result.name << ": not found";
    }
    return s.str();
}

void GetBusRequest::ParseFromJSON(const Json::Node &node) {
    const auto &map_elem = node.AsMap();
    bus_name = map_elem.at("name").AsString();
    request_id = map_elem.at("id").AsInt();
}

Json::Node GetBusRequest::ResultToJSON(const GetBusAnswer &result) const {
    std::map<std::string, Json::Node> ans;
    ans["request_id"] = Json::Node(result.request_id);
    if (result.has_value) {
        ans["route_length"] = Json::Node(result.length);
        ans["curvature"] = Json::Node(result.curvature);
        ans["stop_count"] = Json::Node(result.stops_count);
        ans["unique_stop_count"] = Json::Node(result.unique_stops_count);
    } else {
        ans["error_message"] = Json::Node(std::string("not found"));
    }
    return Json::Node(ans);
}

GetStopAnswer GetStopRequest::Process(Database &db) const {
    auto stop = db.GetStop(stop_name);
    if (stop) {
        return {request_id, true, stop_name, stop->getBuses()};
    } else {
        return {request_id, false, stop_name, std::vector<std::string>()};
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

void GetStopRequest::ParseFromJSON(const Json::Node &node) {
    const auto &map_elem = node.AsMap();
    stop_name = map_elem.at("name").AsString();
    request_id = map_elem.at("id").AsInt();
}

Json::Node GetStopRequest::ResultToJSON(const GetStopAnswer &result) const {
    std::map<std::string, Json::Node> ans;
    ans["request_id"] = Json::Node(result.request_id);
    if (result.has_value) {
        if (result.buses.empty()) {
            ans["buses"] = Json::Node(std::vector<Json::Node>());
        } else {
            std::vector<Json::Node> buf;
            buf.reserve(result.buses.size());
            for (const auto& bus:result.buses) {
                buf.emplace_back(Json::Node(std::string(bus)));
            }
            ans["buses"] = std::move(Json::Node(buf));
        }
    } else {
        ans["error_message"] = Json::Node(std::string("not found"));
    }
    return Json::Node(ans);
}

GetRouteAnswer GetRouteRequest::Process(Database &db) const {
    auto nodes = db.CreateRoute(from, to);
    auto first = dynamic_cast<InfoNode&>(*nodes.front());
    nodes.pop_front();
    if (!first.total_time) {
        return {request_id, false, 0};
    } else {
        return {request_id, true, first.total_time.value(), std::move(nodes)};
    }
}

void GetRouteRequest::ParseFrom(std::string_view input) {}

void GetRouteRequest::ParseFromJSON(const Json::Node &node) {
    const auto& map_elem = node.AsMap();
    from = map_elem.at("from").AsString();
    to = map_elem.at("to").AsString();
    request_id = map_elem.at("id").AsInt();
}

std::string GetRouteRequest::ResultToString(const GetRouteAnswer &result) const {
    return std::string();
}

Json::Node GetRouteRequest::ResultToJSON(const GetRouteAnswer &result) const {
    std::map<std::string, Json::Node> answer;
    answer["request_id"] = Json::Node(result.id);
    if (!result.has_value) {
        answer["error_message"] = Json::Node(std::string("not found"));
        return answer;
    }
    answer["total_time"] = Json::Node(result.total_time);
    std::vector<Json::Node> items;
    for (const auto& node : result.nodes) {
        if (node->type == NodeType::WAIT) {
            auto node_wait = dynamic_cast<WaitNode&>(*node);
            std::map<std::string, Json::Node> wait_ans;
            wait_ans["type"] = Json::Node(std::string("Wait"));
            wait_ans["stop_name"] = Json::Node(node_wait.stop_name);
            wait_ans["time"] = Json::Node(node_wait.time);
            items.emplace_back(wait_ans);
        }
        if (node->type == NodeType::BUS) {
            auto node_bus = dynamic_cast<BusNode&>(*node);
            std::map<std::string, Json::Node> bus_ans;
            bus_ans["type"] = Json::Node(std::string("Bus"));
            bus_ans["bus"] = Json::Node(node_bus.route_name);
            bus_ans["span_count"] = Json::Node(node_bus.span_count);
            bus_ans["time"] = Json::Node(node_bus.time);
            items.emplace_back(bus_ans);
        }
    }
    answer["items"] = Json::Node(items);
    return answer;
}
