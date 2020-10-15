#pragma once
#include <memory>
#include <string>

#include "linker.h"
#include "database.h"
#include "svg.h"

namespace TransportDatabase {
    enum class LayersType {BUS, STOP, STOP_NAME, BUS_NAME};
    class RenderParams {
    public:
        double min_lat;
        double max_lat;
        double min_long;
        double max_long;

        double width;
        double height;
        double padding;
        double stop_radius;
        double line_width;
        int32_t stop_label_font_size;
        Svg::Point stop_label_offset;
        Svg::Color underlayer_color;
        double underlayer_width;
        std::vector<Svg::Color> color_palette;
        std::vector<LayersType> layers_order;
        int32_t bus_label_font_size;
        Svg::Point bus_label_offset;
    };

    class RenderConfig {
    public:
        RenderConfig() = default;
        RenderConfig(const RenderParams& rp);
        void changeRoutingParams(const RenderParams& rp);
        Svg::Point zoomIn(const Coordinates& coord);
        Svg::Color getNewColor();
        void flushColor();
        RenderParams render_params;
    private:
        size_t curr_color = 0;
        double coef = 0;
    };



    class Layer {
    public:
        Layer(RenderConfig &rp);
        virtual ~Layer() = default;
        virtual std::vector<Svg::SvgFigureHolder> createLayer(const Database& db) = 0;
        void clear();
    protected:
        RenderConfig config;
    };

    class BusLayer : public Layer {
    public:
        using Layer::Layer;
        std::vector<Svg::SvgFigureHolder> createLayer(const Database& db) override;
    };

    class StopLayer : public Layer {
    public:
        using Layer::Layer;
        std::vector<Svg::SvgFigureHolder> createLayer(const Database& db) override;
    };

    class StopNameLayer : public Layer {
    public:
        using Layer::Layer;
        std::vector<Svg::SvgFigureHolder> createLayer(const Database& db) override;
    };

class BusNameLayer : public Layer {
public:
  using Layer::Layer;
  std::vector<Svg::SvgFigureHolder> createLayer(const Database& db) override;
};

    class Map : public Linker {
        using LayerHolder = std::unique_ptr<Layer>;
        template <typename LayerType>
        LayerHolder createLayer();
    public:
        using Linker::Linker;
        Map();
        Map(std::shared_ptr<Database> db, const RenderParams& params);

        void setLayerOrder(const std::vector<LayersType>& layers);
        void createMap();
        std::string renderMap();
        void clearMap();
    private:
        void createLayerOrder();
        Svg::Document doc;
        std::vector<LayerHolder> layers;
        RenderConfig render_config;
        std::vector<LayersType> current_order = {LayersType::BUS, LayersType::BUS_NAME, LayersType::STOP, LayersType::STOP_NAME};
    };
}