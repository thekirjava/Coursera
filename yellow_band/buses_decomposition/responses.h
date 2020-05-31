#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using BusStruct = map<string, vector<string>>;
struct BusesForStopResponse {
    vector<string> buses;
    bool buses_exist;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);
struct StopsForBusResponse {
    vector<pair<string, vector<string>>> stops;
    bool stops_exist;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) ;

struct AllBusesResponse {
    BusStruct all;
    bool all_exist;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);