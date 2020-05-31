#pragma once

#include <vector>
#include <string>
#include "responses.h"

using namespace std;

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops);

    BusesForStopResponse GetBusesForStop(const string &stop) const;

    StopsForBusResponse GetStopsForBus(const string &bus) const;

    AllBusesResponse GetAllBuses() const;

private:
    BusStruct buses_to_stops, stops_to_buses;
};
