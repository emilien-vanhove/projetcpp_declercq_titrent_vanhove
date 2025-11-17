#ifndef ATC_BASE_CLASSES_HPP
#define ATC_BASE_CLASSES_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <fstream>

class Controller {
protected:
    std::string controllerID;
    std::vector<std::shared_ptr<Aircraft>> trackedAircraft;
    mutable std::mutex mtx;
    std::ofstream logFile;

    virtual void logAction(const std::string& action);

public:
    Controller(const std::string& id);
    virtual ~Controller();

    virtual void addAircraft(std::shared_ptr<Aircraft> aircraft);
    virtual void removeAircraft(const std::string& callsign);
    virtual std::vector<std::shared_ptr<Aircraft>> getTrackedAircraft() const;

    virtual void update(double deltaTime) = 0;
    virtual void displayStatus() const = 0;

    std::string getID() const { return controllerID; }
};
