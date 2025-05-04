//
// Created by sp on 27.04.2025.
//

#ifndef AVAILABLELEVELOBJECTS_HPP
#define AVAILABLELEVELOBJECTS_HPP
#include <iostream>
#include <string>
#include <vector>

#include "SimulationObjectFactory.hpp"
#include "simulation/physics/Simulation.hpp"


class AvailableLevelObjects {

public:
    // explicit AvailableLevelObjects(const YAML::Node& config) {
    // }

    AvailableLevelObjects() {
        // this->objectTags.emplace_back("MainBall");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Accelerator");
        this->objectTags.emplace_back("Accelerator");
        this->objectTags.emplace_back("Accelerator");


        for (const auto& tag: objectTags) {
            SimulationObjectFactory factory;
            this->objects.push_back(factory.createSimulationObject(tag));
        }
    }

    bool isPlaced(int index) const {
        return index >= 0 && index < this->objects.size() && this->objects[index]->simulation != nullptr;
    }

    void place(B2dSimulation& simulation, int index) {
        if (this->isPlaced(index)) {
            throw std::runtime_error("Object already placed");
        }
        simulation.addObject(this->objects[index]);
    }

    std::shared_ptr<SimulationObjectBase> operator[](int index) const {
        return this->objects[index];
    }

    [[nodiscard]] size_t size() const {
        return this->objects.size();
    }

    std::vector<std::string> objectTags;
    std::vector<std::shared_ptr<SimulationObjectBase>> objects;
};



#endif //AVAILABLELEVELOBJECTS_HPP
