//
// Created by sp on 08.05.2025.
//

#ifndef SIMULATIONOBJECTBASE_HPP
#define SIMULATIONOBJECTBASE_HPP

#include "simulation/physics/Simulation.hpp"
#include "common.hpp"


class SimulationObjectBase {
public:
    virtual ~SimulationObjectBase() = default;
    SimulationObjectBase() = delete;
    explicit SimulationObjectBase(const std::string& objectType): objectType(objectType) {
        this->config["initial_position"] = Vector2D{0,0};
        this->config["initial_rotation"] = float{0};
        this->config["objectType"] = objectType;
    }

    virtual void onCollisionBegin(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void onCollisionEnd(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void step() {}
    virtual std::vector<SimulationBody*> getBodies() = 0;
    virtual void applyConfig() = 0;

    YAML::Node config{};
    B2dSimulation* simulation = nullptr;

private:
    std::string objectType;
};



#endif //SIMULATIONOBJECTBASE_HPP
