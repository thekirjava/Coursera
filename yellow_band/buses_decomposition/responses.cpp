#include "responses.h"

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (r.buses_exist) {
        for (const string &bus : r.buses) {
            os << bus << " ";
        }
        os << endl;
    } else {
        os << "No stop" << endl;;
    }
    return os;
}
ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (r.stops_exist) {
        for (const auto &p : r.stops) {
            os << "Stop " << p.first << ": ";
            if (p.second.empty()) {
                os << "no interchange";
            } else {
                for (const string &other_bus :p.second) {
                    os << other_bus << " ";
                }
            }
            os << endl;
        }
    } else {
        os << "No bus" << endl;
    }
    return os;
}
ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (r.all_exist) {
        for (const auto &bus_item : r.all) {
            os << "Bus " << bus_item.first << ": ";
            for (const string &stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    } else {
        os << "No buses" << endl;
    }
    return os;
}