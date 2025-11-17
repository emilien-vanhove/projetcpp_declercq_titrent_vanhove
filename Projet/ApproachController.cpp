#ifndef ATC_BASE_CLASSES_HPP
#define ATC_BASE_CLASSES_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <fstream>

class ApproachController : public Controller {
private:
    Position airportCenter;
    double controlRadius;          // Rayon de contrôle (km)
    TowerController* towerController;

    struct HoldingPattern {
        Position center;
        double radius;
        double altitude;
        int sequence;
    };

    std::vector<HoldingPattern> holdingPatterns;

public:
    ApproachController(const std::string& id,
        const Position& center,
        double radius);

    void setTowerController(TowerController* twr);

    bool isInControlZone(const Position& pos) const;
    void assignHoldingPattern(std::shared_ptr<Aircraft> aircraft);
    void assignLandingSequence(std::shared_ptr<Aircraft> aircraft);

    // Gestion des urgences
    void handleEmergency(std::shared_ptr<Aircraft> aircraft);

    void update(double deltaTime) override;
    void displayStatus() const override;
};
