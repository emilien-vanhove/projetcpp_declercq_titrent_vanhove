#ifndef ATC_BASE_CLASSES_HPP
#define ATC_BASE_CLASSES_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <fstream>

class TowerController : public Controller {
private:
    struct Runway {
        std::string id;
        bool occupied;
        std::chrono::system_clock::time_point occupiedUntil;

        Runway(const std::string& _id) : id(_id), occupied(false) {}
    };

    struct ParkingPosition {
        std::string id;
        Position location;
        bool occupied;
        double distanceToRunway;

        ParkingPosition(const std::string& _id, const Position& loc, double dist)
            : id(_id), location(loc), occupied(false), distanceToRunway(dist) {}
    };

    std::vector<Runway> runways;
    std::vector<ParkingPosition> parkingPositions;
    std::string activeRunway;

public:
    TowerController(const std::string& id);

    void addRunway(const std::string& runwayID);
    void addParkingPosition(const std::string& parkingID,
        const Position& location,
        double distanceToRunway);

    bool isRunwayAvailable(const std::string& runwayID = "") const;
    void occupyRunway(const std::string& runwayID, int seconds);
    void releaseRunway(const std::string& runwayID);

    std::string assignParking();
    void releaseParking(const std::string& parkingID);

    // Communication avec APP
    bool requestLandingClearance(const std::string& callsign);
    bool requestTakeoffClearance(const std::string& callsign);

    void update(double deltaTime) override;
    void displayStatus() const override;

    // Priorité au décollage (plus éloigné = prioritaire)
    std::shared_ptr<Aircraft> getNextDepartureAircraft();
};
