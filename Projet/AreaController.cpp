#ifndef ATC_BASE_CLASSES_HPP
#define ATC_BASE_CLASSES_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <fstream>

class AreaController : public Controller {
private:
    struct Sector {
        std::string id;
        double minAltitude;
        double maxAltitude;
    };

    std::vector<Sector> sectors;
    std::vector<ApproachController*> destinationAPPs;

public:
    AreaController(const std::string& id);

    void addSector(const std::string& sectorID,
        double minAlt, double maxAlt);
    void addDestinationAPP(ApproachController* app);

    // Gestion du trafic en-route
    void checkSeparation();
    void transferToAPP(std::shared_ptr<Aircraft> aircraft,
        ApproachController* destination);

    void update(double deltaTime) override;
    void displayStatus() const override;
};

#endif // ATC_BASE_CLASSES_HPP