//
// Created by sp on 03.05.2025.
//

#ifndef SIMULATIONOBJECTFACTORY_HPP
#define SIMULATIONOBJECTFACTORY_HPP
#include "simulation/objects/AcceleratorObject.hpp"
#include "simulation/objects/GoalObject.hpp"
#include "simulation/objects/MainBallObject.hpp"
#include "simulation/objects/RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"


class SimulationObjectFactory {

public:

    [[nodiscard]] std::shared_ptr<SimulationObjectBase> createSimulationObject(const std::string& name) {
        if  (name == "MainBall") {
            return std::make_shared<MainBallObject>();
        }
        if (name == "Rectangle") {
            return std::make_shared<RectangleObject>();
        }
        if (name == "Accelerator") {
            return std::make_shared<AcceleratorObject>();
        }
        if (name == "Goal") {
            return std::make_shared<GoalObject>();
        }
        throw std::invalid_argument("Object type not recognised: " + name);
    }

};



#endif //SIMULATIONOBJECTFACTORY_HPP
