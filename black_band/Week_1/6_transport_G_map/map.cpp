#include <sstream>
#include <utility>
#include <map>

#include "map.h"

namespace TransportDatabase {

    RenderConfig::RenderConfig(const RenderParams& rp) {
        changeRoutingParams(rp);
    }

    void RenderConfig::changeRoutingParams(const TransportDatabase::RenderParams& rp) {
        render_params = rp;
        double real_width = render_params.width - 2*render_params.padding;
        double real_height = render_params.height - 2*render_params.padding;
        double min_x = render_params.min_long;
        double max_x = render_params.max_long;
        double min_y = render_params.max_lat;
        double max_y = render_params.min_lat;
        double coef_x = (max_x - min_x) != 0 ? real_width/(max_x - min_x) : 0;
        double coef_y = (max_y - min_y) !=0 ? real_height/(min_y - max_y) : 0;
        if ((coef_x == 0) && (coef_y == 0)) {
            coef = 0;
        }
        else if (coef_x == 0) {
            coef = coef_y;
        }
        else if (coef_y == 0) {
            coef = coef_x;
        }
        else {
            coef = std::min(coef_x, coef_y);
        }
        curr_color = 0;
    }

    Svg::Point RenderConfig::zoomIn(const Coordinates& coord) {
        return {.x = (coord.getLongitude() - render_params.min_long) * coef + render_params.padding,
                .y = (render_params.max_lat - coord.getLatitude()) * coef + render_params.padding};
    }

    Svg::Color RenderConfig::getNewColor() {
        return render_params.color_palette[curr_color++ % render_params.color_palette.size()];
    }

    Layer::Layer(RenderConfig &rp) : config(rp) {}

    void Layer::clear() {
        config.changeRoutingParams(config.render_params);
    }

    std::vector<Svg::SvgFigureHolder> BusLayer::createLayer(const TransportDatabase::Database &db) {
        std::cerr << "Bus layer" << std::endl;
        std::vector<Svg::SvgFigureHolder> result;
        std::map<std::string, std::shared_ptr<Bus>> sorted_buses;
        for (const auto& [bus_name, bus_ptr] : db.getBuses()) {
            sorted_buses[bus_name] = bus_ptr;
        }
        std::cerr << "Count of buses " << db.getBuses().size() << std::endl;
        std::cerr << "Count of sorted buses " << db.getBuses().size() << std::endl;
        Svg::Polyline basic_line;
        basic_line.SetStrokeWidth(config.render_params.line_width);
        basic_line.SetStrokeLineCap("round");
        basic_line.SetStrokeLineJoin("round");
        for (const auto& [bus_name, bus_ptr] : sorted_buses) {
            Svg::Polyline bus = basic_line;
            bus.SetStrokeColor(config.getNewColor());
            auto stops_name = bus_ptr->getStopsName();
            if (bus_ptr->bus_type == Bus::BusTypes::LINEAR) {
                for (auto i = stops_name.begin(); i != stops_name.end(); ++i) {
                    auto stop = db.getStop(*i);
                    bus.AddPoint(config.zoomIn(stop->getCoordinates()));
                }
                for (auto i = std::next(stops_name.rbegin()); i != stops_name.rend(); ++i) {
                    auto stop = db.getStop(*i);
                    bus.AddPoint(config.zoomIn(stop->getCoordinates()));
                }
            }
            if (bus_ptr->bus_type == Bus::BusTypes::CYCLE) {
                for (auto i = stops_name.begin(); i != stops_name.end(); ++i) {
                    auto stop = db.getStop(*i);
                    bus.AddPoint(config.zoomIn(stop->getCoordinates()));
                }
            }
            result.push_back(Svg::MakeSvgFigure(bus));
        }
        return result;
    }

    std::vector<Svg::SvgFigureHolder> StopLayer::createLayer(const TransportDatabase::Database &db) {
        std::cerr << "Stop layer" << std::endl;
        std::vector<Svg::SvgFigureHolder> result;
        std::map<std::string, std::shared_ptr<Stop>> sorted_stops;
        for (const auto& [stop_name, stop_ptr] : db.getStops()) {
            sorted_stops[stop_name] = stop_ptr;
        }
        std::cerr << "Count of stop " << db.getStops().size() << std::endl;
        std::cerr << "Count of sorted stop " << db.getStops().size() << std::endl;

        Svg::Circle base_circle;
        base_circle.SetRadius(config.render_params.stop_radius);
        base_circle.SetFillColor("white");
        for (const auto& [stop_name, stop_ptr] : sorted_stops) {
            Svg::Circle stop = base_circle;
            stop.SetCenter(config.zoomIn(stop_ptr->getCoordinates()));
            result.push_back(Svg::MakeSvgFigure(stop));
        }
        return result;
    }

    std::vector<Svg::SvgFigureHolder> StopNameLayer::createLayer(const TransportDatabase::Database &db) {
        std::cerr << "Stop name layer" << std::endl;
        std::vector<Svg::SvgFigureHolder> result;
        std::map<std::string, std::shared_ptr<Stop>> sorted_stops;
        for (const auto& [stop_name, stop_ptr] : db.getStops()) {
            sorted_stops[stop_name] = stop_ptr;
        }
        std::cerr << "Count of stop " << db.getStops().size() << std::endl;
        std::cerr << "Count of sorted stop " << db.getStops().size() << std::endl;
        Svg::Text base_text;
        base_text.SetOffset(config.render_params.stop_label_offset);
        base_text.SetFontSize(config.render_params.stop_label_font_size);
        base_text.SetFontFamily("Verdana");
        Svg::Text podl = base_text;
        podl.SetFillColor(config.render_params.underlayer_color);
        podl.SetStrokeColor(config.render_params.underlayer_color);
        podl.SetStrokeWidth(config.render_params.underlayer_width);
        podl.SetStrokeLineCap("round");
        podl.SetStrokeLineJoin("round");
        Svg::Text text = base_text;
        text.SetFillColor("black");
        for (const auto& [stop_name, stop_ptr] : sorted_stops) {
            Svg::Text name = text;
            Svg::Text podl_name = podl;
            name.SetData(stop_name);
            name.SetPoint(config.zoomIn(stop_ptr->getCoordinates()));
            podl_name.SetData(stop_name);
            podl_name.SetPoint(config.zoomIn(stop_ptr->getCoordinates()));
            result.push_back(Svg::MakeSvgFigure(podl_name));
            result.push_back(Svg::MakeSvgFigure(name));
        }
        return result;
    }

    Map::Map() {
        setLayerOrder({LayersType::BUS, LayersType::STOP, LayersType::STOP_NAME});
    }

    Map::Map(std::shared_ptr<Database> db, const RenderParams& params) : Linker(std::move(db)) {
        render_config = RenderConfig(params);
        setLayerOrder(render_config.render_params.layers_order);
    }

    template <typename LayerType>
    Map::LayerHolder Map::createLayer()  {
        return std::make_unique<LayerType>(render_config);
    }

    void Map::setLayerOrder(const std::vector<LayersType> &layers) {
        current_order = layers;
        createLayerOrder();
    }
/*case LayersType::BUS_NAME: {
  layers.push_back(CreateLayer<BusNameLayer>());
}*/
    void Map::createMap() {
        for (const auto& layer : layers) {
            auto objects = layer->createLayer(*db_);
            for (auto& object : objects) {
                doc.AddDocumentPart(std::move(object));
            }
        }
        doc.Render(std::cerr);
    }

    std::string Map::renderMap() {
        std::stringstream out;
        doc.Render(out);
        clearMap();
        return out.str();
    }

    void Map::createLayerOrder() {
        for (const auto layer_type : current_order) {
            if (layer_type == LayersType::BUS) {
                layers.push_back(createLayer<BusLayer>());
            }
            else if (layer_type == LayersType::STOP) {
                layers.push_back(createLayer<StopLayer>());
            }
            else if (layer_type == LayersType::STOP_NAME) {
                layers.push_back(createLayer<StopNameLayer>());
            }
            else {
                throw std::runtime_error("unknown layer type");
            }
        }
    }

    void Map::clearMap() {
        doc.Clear();
        layers.clear();
        createLayerOrder();
    }
}
