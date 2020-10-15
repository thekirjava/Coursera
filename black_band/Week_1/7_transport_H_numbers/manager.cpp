#include <sstream>
#include "manager.h"

namespace TransportDatabase {
    void PrintResults(const std::vector<std::string> &results, std::ostream &out) {
        for (const auto &result : results) {
            out << result << "\n";
        }
    }

    DatabaseManager::DatabaseManager() : router(nullptr) {
        db_ = std::make_shared<Database>();
    }

    DatabaseManager::DatabaseManager(std::shared_ptr<Database> db) {
        changeDatabase(std::move(db));
    }

    void DatabaseManager::changeDatabase(std::shared_ptr<Database> db) {
        db_ = std::move(db);
    }

    template<typename RequestType>
    RequestHolder DatabaseManager::parseRequest(RequestType type, std::string_view request_str) {
        auto request_ptr = Request::create(type);
        if (request_ptr) {
            request_ptr->ParseFrom(request_str);
        }
        return request_ptr;
    }

    Json::Node DatabaseManager::processAllJsonRequests(std::istream &in) {
        auto doc = Json::Load(in);
        auto global_type_map = doc.GetRoot().AsMap();
        const std::string modify_type = "base_requests";
        Json::Node modify_requests = global_type_map.at(modify_type);
        const std::string params_type = "routing_settings";
        Json::Node params_request = global_type_map.at(params_type);
        for (const auto &node : modify_requests.AsArray()) {
            processJsonModifyRequest(node);
        }
        RoutingParam rp = {params_request.AsMap().at("bus_velocity").AsDouble(),
                           params_request.AsMap().at("bus_wait_time").AsDouble()};
        router = std::make_shared<Route>(Route{db_, rp});

        const std::string render_type = "render_settings";
        Json::Node render_requests = global_type_map.at(render_type);
        RenderParams params = extractRenderParams(render_requests);
        render = std::make_shared<Map>(Map(db_, params));

        const std::string read_type = "stat_requests";
        Json::Node read_requests = global_type_map.at(read_type);

        std::vector<Json::Node> result;
        for (const auto &node : read_requests.AsArray()) {
            result.push_back(processJsonReadRequest(node));
        }
        return Json::Node(result);
    }

    Json::Node DatabaseManager::processJsonModifyRequest(const Json::Node &node) {
        return makeJsonAnswerFromAnyRequest(parseModifyJsonRequest(node));
    }

    Json::Node DatabaseManager::processJsonReadRequest(const Json::Node &node) {
        return makeJsonAnswerFromAnyRequest(parseReadJsonRequest(node));
    }

    Json::Node DatabaseManager::makeJsonAnswerFromAnyRequest(RequestHolder request) {
        switch (request->getType()) {
            case Request::Type::ADD_STOP: {
                const auto &cast_request = dynamic_cast<ModifyRequest<Database> &>(*request);
                cast_request.process(*db_);
                return Json::Node("Stop added");
            }
            case Request::Type::ADD_BUS: {
                const auto &cast_request = dynamic_cast<ModifyRequest<Database> &>(*request);
                cast_request.process(*db_);
                return Json::Node("Route added");
            }
            case Request::Type::GET_BUS: {
                const auto &cast_request = dynamic_cast<ReadRequest<GetBusAnswer, Database> &>(*request);
                const auto result = cast_request.process(*db_);
                return cast_request.jsonAnswer(result);
            }
            case Request::Type::GET_STOP: {
                const auto &cast_request = dynamic_cast<ReadRequest<GetStopAnswer, Database> &>(*request);
                const auto result = cast_request.process(*db_);
                return cast_request.jsonAnswer(result);
            }
            case Request::Type::CREATE_ROUTE: {
                const auto &cast_request = dynamic_cast<ReadRequest<CreateRouteAnswer, Route> &>(*request);
                const auto result = cast_request.process(*router);
                return cast_request.jsonAnswer(result);
            }
            case Request::Type::CREATE_MAP: {
                const auto &cast_request = dynamic_cast<ReadRequest<CreateMapAnswer, Map> &>(*request);
                const auto result = cast_request.process(*render);
                return cast_request.jsonAnswer(result);
            }
            default:
                return Json::Node("error");
        }
    }

    RequestHolder DatabaseManager::parseModifyJsonRequest(const Json::Node &node) {
        auto type = node.AsMap().at("type").AsString();
        if (type == "Stop") {
            return jsonRequest(Request::Type::ADD_STOP, node);
        } else if (type == "Bus") {
            return jsonRequest(Request::Type::ADD_BUS, node);
        } else {
            return nullptr;
        }
    }

    RequestHolder DatabaseManager::parseReadJsonRequest(const Json::Node &node) {
        auto type = node.AsMap().at("type").AsString();
        if (type == "Stop") {
            return jsonRequest(Request::Type::GET_STOP, node);
        } else if (type == "Bus") {
            return jsonRequest(Request::Type::GET_BUS, node);
        } else if (type == "Route") {
            return jsonRequest(Request::Type::CREATE_ROUTE, node);
        } else if (type == "Map") {
            return jsonRequest(Request::Type::CREATE_MAP, node);
        } else {
            return nullptr;
        }
    }

    template<typename RequestType>
    RequestHolder DatabaseManager::jsonRequest(RequestType type, const Json::Node &node) {
        auto request_ptr = Request::create(type);
        if (request_ptr) {
            request_ptr->parseFromJson(node);
        }
        return request_ptr;
    }

    Svg::Color GetColor(Json::Node node) {
        if (std::holds_alternative<std::string>(node)) {
            return node.AsString();
        } else {
            auto rgb_vec = node.AsArray();
            if (rgb_vec.size() == 3) {
                return Svg::Rgb{static_cast<uint8_t>(rgb_vec[0].AsInt()),
                                static_cast<uint8_t>(rgb_vec[1].AsInt()),
                                static_cast<uint8_t>(rgb_vec[2].AsInt())};
            }
            if (rgb_vec.size() == 4) {
                return Svg::Rgba{static_cast<uint8_t>(rgb_vec[0].AsInt()),
                                 static_cast<uint8_t>(rgb_vec[1].AsInt()),
                                 static_cast<uint8_t>(rgb_vec[2].AsInt()),
                                 rgb_vec[3].AsDouble()};
            }
        }
        return Svg::NoneColor;
    }

    RenderParams DatabaseManager::extractRenderParams(const Json::Node &node) {
        RenderParams rp;
        const auto &param_map = node.AsMap();
        rp.width = param_map.at("width").AsDouble();
        rp.height = param_map.at("height").AsDouble();
        rp.padding = param_map.at("padding").AsDouble();
        rp.stop_radius = param_map.at("stop_radius").AsDouble();
        rp.line_width = param_map.at("line_width").AsDouble();
        rp.stop_label_font_size = param_map.at("stop_label_font_size").AsInt();
        auto point = param_map.at("stop_label_offset").AsArray();
        rp.stop_label_offset = {.x = point[0].AsDouble(),
                .y = point[1].AsDouble()};
        rp.underlayer_width = param_map.at("underlayer_width").AsDouble();
        rp.underlayer_color = GetColor(param_map.at("underlayer_color"));
        rp.bus_label_font_size = param_map.at("bus_label_font_size").AsInt();
        rp.bus_label_offset = {param_map.at("bus_label_offset").AsArray()[0].AsDouble(),
                               param_map.at("bus_label_offset").AsArray()[1].AsDouble()};
        rp.layers_order = {LayersType::BUS, LayersType::BUS_NAME, LayersType::STOP, LayersType::STOP_NAME};
        rp.min_lat = db_->getStat().min_lat;
        rp.max_lat = db_->getStat().max_lat;
        rp.min_long = db_->getStat().min_long;
        rp.max_long = db_->getStat().max_long;
        auto pallete_vec = param_map.at("color_palette").AsArray();
        for (const auto &elem : pallete_vec) {
            rp.color_palette.push_back(GetColor(elem));
        }
        return rp;
    }

}