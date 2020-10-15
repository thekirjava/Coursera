#pragma once
#include <cmath>

class Coordinates {
public:
    Coordinates() =default;
    explicit Coordinates(double latitude, double longitude):latitude(latitude), longitude(longitude) {}

    double getLatitude() const;

    double getLongitude() const;

    friend double Distance(const Coordinates& c1, const Coordinates& c2);

private:
    constexpr static double PI =3.1415926535;
    constexpr static double RADIUS = 6371000;
    double latitude;
    double longitude;
};

class CoordinatesBuilder {
public:
    CoordinatesBuilder() = default;

    CoordinatesBuilder& setLatitude(double latitude);

    CoordinatesBuilder& setLongitude(double longitude);

    Coordinates Build() const;
private:
    double latitude;
    double longitude;
};
