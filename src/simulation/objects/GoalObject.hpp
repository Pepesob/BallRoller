//
// Created by sp on 04.05.2025.
//

#ifndef GOALOBJECT_HPP
#define GOALOBJECT_HPP
#include "MainBallObject.hpp"
#include "RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"


class GoalObject: public SimulationObjectBase {
public:
    GoalObject() {
        this->rectangle.rectangle.config.isSensor = true;
        this->rectangle.rectangle.config.size = {1,1};
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody &this_body, SimulationBody &other_body) override {
        if (auto main_ball = getObjectAs<MainBallObject>(simulation.getAssociatedObject(other_body))) {
            simulation.goalReached = true;
        }
    }

    std::vector<SimulationBody *> getBodies() override {
        return this->rectangle.getBodies();
    }

    void setInitialPosition(const Vector2D &position) override {
        this->rectangle.setInitialPosition(position);
    }

    void setInitialRotation(float radians) override {
        this->rectangle.setInitialRotation(radians);
    }

    YAML::Node saveConfig() override {
        YAML::Node node = SimulationObjectBase::saveConfig();
        node["objectType"] = "Goal";
        return node;
    }

    void loadConfig(const YAML::Node &config) override {
        this->rectangle.loadConfig(config);
    }

    RectangleObject rectangle;
};



#endif //GOALOBJECT_HPP
