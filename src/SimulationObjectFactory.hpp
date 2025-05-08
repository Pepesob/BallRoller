//
// Created by sp on 03.05.2025.
//

#ifndef SIMULATIONOBJECTFACTORY_HPP
#define SIMULATIONOBJECTFACTORY_HPP
#include "simulation/base_drawers/SimulationObjectDrawer.hpp"
#include "simulation/objects/AcceleratorObject.hpp"
#include "simulation/objects/GoalObject.hpp"
#include "simulation/objects/MainBallObject.hpp"
#include "simulation/objects/RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"



class SimulationObjectFactory {

public:

    [[nodiscard]] SimulationObjectBase* createSimulationObject(const std::string& name) {
        if  (name == "MainBall") {
            return new MainBallObject();
        }
        if (name == "Rectangle") {
            return new RectangleObject();
        }
        if (name == "Accelerator") {
            return new AcceleratorObject();
        }
        if (name == "Goal") {
            return new GoalObject();
        }
        throw std::invalid_argument("Object type not recognised: " + name);
    }

    [[nodiscard]] ISimulationObjectDrawer* createSimulationObjectDrawer(const std::string& name, SimulationObjectBase* simulation_object) {
        if  (name == "MainBall") {
            auto obj = dynamic_cast<MainBallObject*>(simulation_object);
            return new MainBallObjectDrawer(*obj);
        }
        if (name == "Rectangle") {
            auto obj = dynamic_cast<RectangleObject*>(simulation_object);
            return new RectangleObjectDrawer(*obj);
        }
        if (name == "Accelerator") {
            auto obj = dynamic_cast<AcceleratorObject*>(simulation_object);
            return new RectangleObjectDrawer(*obj);
        }
        if (name == "Goal") {
            auto obj = dynamic_cast<GoalObject*>(simulation_object);
            return new RectangleObjectDrawer(*obj);
        }
        return new DefaultObjectDrawer(*simulation_object);
    }

};



#endif //SIMULATIONOBJECTFACTORY_HPP
