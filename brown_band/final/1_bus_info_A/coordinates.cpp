#include "coordinates.h"
#include <cmath>

using namespace std;

double Coordinates::getLatitude() const {
    return latitude;
}

double Coordinates::getLongitude() const {
    return longitude;
}

double Distance(const Coordinates &c1, const Coordinates &c2) {
    double sin_1 = sin(c1.latitude * Coordinates::PI / 180);
    double sin_2 = sin(c2.latitude * Coordinates::PI / 180);
    double cos_1 = cos(c1.latitude * Coordinates::PI / 180);
    double cos_2 = cos(c2.latitude * Coordinates::PI / 180);
    double cos_lambda = cos(c2.longitude * Coordinates::PI / 180 - c1.longitude * Coordinates::PI / 180);
    double delta = acos(sin_1 * sin_2 + cos_1 * cos_2 * cos_lambda);
    double D = delta * Coordinates::RADIUS;
    return D;
}
