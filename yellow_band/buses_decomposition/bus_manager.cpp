
#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
    buses_to_stops[bus] = stops;
    for (const string &stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
    BusesForStopResponse ans = {};
    if (stops_to_buses.count(stop) == 0) {
        ans.buses_exist = false;
    } else {
        ans.buses_exist = true;
        for (const string &bus : stops_to_buses.at(stop)) {
            ans.buses.emplace_back(bus);
        }
    }
    return ans;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
    StopsForBusResponse ans = {};
    if (buses_to_stops.count(bus) == 0) {
        ans.stops_exist = false;
    } else {
        ans.stops_exist = true;
        for (const string &stop : buses_to_stops.at(bus)) {
            auto p = make_pair(stop, vector<string>());
            if (stops_to_buses.at(stop).size() != 1) {
                for (const string &other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        p.second.emplace_back(other_bus);
                    }
                }
            }
            ans.stops.emplace_back(p);
        }
    }
    return ans;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse ans = {};
    if (buses_to_stops.empty()) {
        ans.all_exist = false;
    } else {
        ans.all_exist = true;
        ans.all = buses_to_stops;
    }
    return ans;
}