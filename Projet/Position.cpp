#ifndef ATC_BASE_CLASSES_HPP
#define ATC_BASE_CLASSES_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <fstream>


struct Position {
    double x;        // Coordonnées cartésiennes (km)
    double y;
    double altitude; // Altitude (pieds)

    Position(double _x = 0, double _y = 0, double _alt = 0)
        : x(_x), y(_y), altitude(_alt) {}

    double distanceTo(const Position& other) const;
};

struct Velocity {
    double speed;    // Vitesse (nœuds)
    double heading;  // Cap (degrés, 0-360)
    double verticalSpeed; // Vitesse verticale (pieds/min)

    Velocity(double s = 0, double h = 0, double vs = 0)
        : speed(s), heading(h), verticalSpeed(vs) {}
};

enum class AircraftState {
    EN_ROUTE,
    APPROACHING,
    LANDING,
    TAXIING_TO_PARKING,
    PARKED,
    TAXIING_TO_RUNWAY,
    TAKING_OFF,
    DEPARTED,
    EMERGENCY
};

enum class EmergencyType {
    NONE,
    LOW_FUEL,
    MECHANICAL_FAILURE,
    MEDICAL,
    OTHER
};