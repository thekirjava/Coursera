#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <memory>
#include <list>

#include "graph.h"
#include "router.h"
#include "json.h"
#include "coordinates.h"

namespace TransportDatabase {
    class Stop {
    public:

        Stop();

        Stop(std::string name, const Coordinates &coord);

        Stop(std::string name, const Coordinates &coord, const std::vector<std::pair<std::string, int>> &distances);

        Stop(const Stop &other);

        Stop(Stop &&other) noexcept;

        Stop &operator=(const Stop &other);

        Stop &operator=(Stop &&other) noexcept;

        std::string getName() const;

        Coordinates getCoordinates() const;

        void addBus(const std::string &bus_name);

        std::vector<std::string> getBuses() const;

        std::unordered_map<std::string, int> distance_to_stop;
    private:
        std::string name_;
        Coordinates coord_;
        std::set<std::string> buses_for_stop;
    };

    class Bus {
    public:
        enum class BusTypes {
            LINEAR, CYCLE
        };

        explicit Bus(const std::string &name, const std::vector<std::string> &stops_name, BusTypes type)
                : bus_type(type), name_(name), stops_name_(stops_name) {}

        virtual ~Bus() = default;

        virtual size_t countOfStops() const = 0;

        virtual size_t countOfUniqueStops() const = 0;

        virtual double realLength() const = 0;

        virtual double length() const = 0;

        double curvature() const;

        std::string getName() const;

        std::vector<std::string> getStopsName() const;

        BusTypes bus_type;
    protected:
        std::string name_;
        std::vector<std::string> stops_name_;
    };

    static const std::unordered_map<char, Bus::BusTypes> sign_to_route = {{'-', Bus::BusTypes::LINEAR},
                                                                          {'>', Bus::BusTypes::CYCLE}};

    class LinearBus : public Bus {
    public:
        LinearBus() = default;

        explicit LinearBus(const std::string &name, const std::vector<std::string> &stops_name,
                           const std::vector<std::shared_ptr<Stop>> &stops) : Bus(name, stops_name, BusTypes::LINEAR),
                                                                              stops_(stops) {
            for (const auto &elem : stops_name_) {
                unique_stops_.insert(elem);
            }
        }

        size_t countOfStops() const override;

        size_t countOfUniqueStops() const override;

        double realLength() const override;

        double length() const override;

    private:
        // Порядок маршрутов с данными о остановках
        std::vector<std::shared_ptr<Stop>> stops_;
        // Хранение уникальных остановок
        std::unordered_set<std::string_view> unique_stops_;
    };

    class CycleBus : public Bus {
    public:
        CycleBus() = default;

        explicit CycleBus(const std::string &name, const std::vector<std::string> &stops_name,
                          const std::vector<std::shared_ptr<Stop>> &stops) : Bus(name, stops_name, BusTypes::CYCLE),
                                                                             stops_(stops) {
            for (const auto &elem : stops_name_) {
                unique_stops_.insert(elem);
            }
        }

        size_t countOfStops() const override;

        size_t countOfUniqueStops() const override;

        double realLength() const override;

        double length() const override;

    private:
        // Порядок маршрутов с данными о остановках
        std::vector<std::shared_ptr<Stop>> stops_;
        // Хранение уникальных остановок
        std::unordered_set<std::string_view> unique_stops_;
    };

    struct BusInfo {
        Bus::BusTypes type;
        std::string name;
        std::vector<std::string> stop_names;
    };

    struct DatabaseStat {
        double min_lat = std::numeric_limits<double>::max();
        double max_lat = 0;
        double min_long = std::numeric_limits<double>::max();
        double max_long = 0;
    };

    class Database {
    public:
        using StopData = std::unordered_map<std::string, std::shared_ptr<Stop>>;
        using BusData = std::unordered_map<std::string, std::shared_ptr<Bus>>;

        Database() = default;

        void addStop(const Stop &stop);

        std::shared_ptr<Stop> getOrAddStop(const std::string &stop_name);

        std::shared_ptr<Stop> getStop(const std::string &stop_name) const;

        const StopData &getStops() const;

        void addBus(const std::string &bus_name, std::shared_ptr<Bus> bus);

        std::shared_ptr<Bus> getBus(const std::string &bus_name) const;

        // TODO возвращать контейнер, который НЕ позволяет изменять хранимые значения?
        const BusData &getBuses() const;

        const DatabaseStat &getStat() const;

    private:
        DatabaseStat stat;
        StopData stops_;
        BusData buses_;
    };

    class BusBuilder {
    public:
        BusBuilder() = delete;

        explicit BusBuilder(Database &db) : db_(db) {}

        std::shared_ptr<Bus> makeBus(BusInfo &&info);

    private:
        Database &db_;

        std::shared_ptr<Bus> makeCycle(BusInfo &&info);

        std::shared_ptr<Bus> makeLinear(BusInfo &&info);
    };
}
