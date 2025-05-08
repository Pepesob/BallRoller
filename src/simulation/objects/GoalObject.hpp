//
// Created by sp on 04.05.2025.
//

#ifndef GOALOBJECT_HPP
#define GOALOBJECT_HPP
#include "MainBallObject.hpp"
#include "RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"


class GoalObject: public RectangleObject {
public:
    GoalObject(): RectangleObject("Goal") {
        this->rectangle.config.isSensor = true;
        this->rectangle.config.size = {1,1};
        this->texture_path = "resources/finish_texture.png";
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody &this_body, SimulationBody &other_body) override {
        if (auto main_ball = getObjectAs<MainBallObject>(simulation.getAssociatedObject(other_body))) {
            simulation.goalReached = true;
        }
    }
};



#endif //GOALOBJECT_HPP
