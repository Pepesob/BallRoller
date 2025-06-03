#pragma once


#include "common.hpp"

#include "BodyCompound.hpp"


class SimulationObjectBase {
public:
    virtual ~SimulationObjectBase() = default;
    SimulationObjectBase() = delete;
    explicit SimulationObjectBase(const std::string& objectType): objectType(objectType) {}
    virtual void onInit() {};
    virtual void onCollisionBegin(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void onCollisionEnd(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void onClick(SimulationBody& this_body) {};
    virtual void step() {}
    virtual std::vector<SimulationBody*> getBodies() = 0;

    BodyCompound compound;
    B2dSimulation* simulation = nullptr;
    std::string objectType;
};



