//
// Created by sp on 02.05.2025.
//

#ifndef ACCELERATOROBJECT_HPP
#define ACCELERATOROBJECT_HPP

#include "SimulationObjectBase.hpp"


class AcceleratorObject : public SimulationObjectBase {
public:
    AcceleratorObject() {
        rectangle.config.isSensor = true;
        rectangle.config.size = {0.5, 0.5};
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody& this_body, SimulationBody& other_body) override {
        simulation.applyForce(other_body, {10,0});
    }

    void setInitialPosition(const Vector2D& position) override {
        rectangle.config.initial_position = position;
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&rectangle};
    }
    RectangleBody rectangle;
};


#endif //ACCELERATOROBJECT_HPP
