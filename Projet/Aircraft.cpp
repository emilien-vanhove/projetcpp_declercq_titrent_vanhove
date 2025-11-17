#ifndef ATC_BASE_CLASSES_HPP
#define ATC_BASE_CLASSES_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <fstream>

class Aircraft {
private:
    std::string callsign;           // Ex: "AFR10"
    std::string aircraftType;       // Ex: "A320"
    Position position;
    Velocity velocity;
    AircraftState state;
    EmergencyType emergency;

    double fuel;                    // Carburant restant (kg)
    double fuelConsumption;         // Consommation (kg/h)
    std::string assignedParking;    // Ex: "P1", "P2"

    std::chrono::system_clock::time_point parkingArrivalTime;
    int parkingDuration;            // Durée de stationnement (minutes)

    mutable std::mutex mtx;
    std::vector<std::string> communicationLog;

public:
    Aircraft(const std::string& cs, const std::string& type,
        const Position& pos, const Velocity& vel);

    // Getters
    std::string getCallsign() const { return callsign; }
    Position getPosition() const;
    Velocity getVelocity() const;
    AircraftState getState() const;
    EmergencyType getEmergency() const;
    double getFuel() const;
    std::string getAssignedParking() const;

    // Setters
    void setPosition(const Position& pos);
    void setVelocity(const Velocity& vel);
    void setState(AircraftState newState);
    void declareEmergency(EmergencyType type);
    void setAssignedParking(const std::string& parking);

    // Méthodes de mise à jour
    void updatePosition(double deltaTime); // deltaTime en secondes
    void consumeFuel(double deltaTime);
    bool isLowOnFuel() const;

    // Communication
    void logCommunication(const std::string& message);
    std::vector<std::string> getCommunicationLog() const;

    // Parking
    void arriveAtParking(int durationMinutes);
    bool isReadyToDepart() const;
};