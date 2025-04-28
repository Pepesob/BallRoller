//
// Created by sp on 24.04.2025.
//

#ifndef ACCELERATIONFIELDDRAWER_HPP
#define ACCELERATIONFIELDDRAWER_HPP


#include "Rectangle.hpp"
#include "physics/MainBallPhysics.hpp"
#include "physics/ObjectPhysics.hpp"

struct AccelerationFieldPhysicsConfig: RectanglePhysicsConfig {
    Vector2D force = {1,1};

    AccelerationFieldPhysicsConfig() {
        isSensor = true;
        enableSensorEvents = true;
    }
};


class AccelerationFieldPhysics: public RectanglePhysics {
public:
    AccelerationFieldPhysics(b2WorldId world_id, const AccelerationFieldPhysicsConfig& config): RectanglePhysics(world_id, config) {
        this->force = config.force;
    }

    void onContactBegin(ObjectPhysics *object) override {
        if (auto* main_ball_physics = object->getObjectAsType<MainBallPhysics*>()) {
            b2Body_ApplyForce(main_ball_physics->getBodyId(), {this->force.x, this->force.y}, {0,0}, true);
        }
    }

    b2BodyId getBodyId() override {
        return this->body_id;
    }

    void step() override {

    }

private:
    Vector2D force = {};
};


#endif //ACCELERATIONFIELDDRAWER_HPP
