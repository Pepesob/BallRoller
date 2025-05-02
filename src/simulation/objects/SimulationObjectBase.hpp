//
// Created by sp on 02.05.2025.
//

#ifndef SIMULATIONOBJECTBASE_HPP
#define SIMULATIONOBJECTBASE_HPP


#include "Screen.hpp"
#include "Camera.hpp"
#include "simulation/physics/Simulation.hpp"

class SimulationObjectBase {
public:
    virtual ~SimulationObjectBase() = default;
    virtual void onCollisionBegin(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void onCollisionEnd(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void step() {}
    virtual std::vector<SimulationBody*> getBodies() = 0;
    virtual void setInitialPosition(const Vector2D& position) = 0;

    B2dSimulation* simulation = nullptr;
};

class SimulationObjectDrawer {
public:
    virtual ~SimulationObjectDrawer() = default;

    virtual void drawPreview(Screen* screen, Camera* camera) = 0;
    virtual void drawSimulation(Screen* screen, Camera* camera) = 0;
};

#endif //SIMULATIONOBJECTBASE_HPP
