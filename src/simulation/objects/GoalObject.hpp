//
// Created by sp on 04.05.2025.
//

#ifndef GOALOBJECT_HPP
#define GOALOBJECT_HPP

#include "MainBallObject.hpp"
#include "RectangleObject.hpp"


class GoalObject: public RectangleObject {
public:
    GoalObject(): RectangleObject("Goal") {
        this->rectangle.config.isSensor = true;
        this->rectangle.config.size = {1,1};
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody &this_body, SimulationBody &other_body) override {
        if (auto main_ball = getObjectAs<MainBallObject>(simulation.getAssociatedObject(other_body))) {
            simulation.goalReached = true;
        }
    }

};

class GoalObjectDrawer: public RectangleObjectDrawer {
public:
    GoalObjectDrawer(GoalObject& goal_object): RectangleObjectDrawer(goal_object) {
        this->texture_path = "resources/finish_texture.png";
        this->drawer.texture = TextureLoader::getTexture(this->texture_path);
    }
};



#endif //GOALOBJECT_HPP
