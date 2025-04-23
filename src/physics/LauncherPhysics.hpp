//
// Created by sp on 11.04.2025.
//

#ifndef LAUNCHERPHYSICS_HPP
#define LAUNCHERPHYSICS_HPP

#include <box2d/box2d.h>

#include "MainBallPhysics.hpp"
#include "StaticRectPhysics.hpp"
#include "CollisionObserver.hpp"

class LauncherPhysics: public StaticRectPhysics, public CollisionObserver {
public:
    LauncherPhysics(StaticRect* launcher, b2WorldId world_id, float acceleration): StaticRectPhysics(launcher, world_id) {
        this->acceleration = acceleration;
    }

    b2BodyId getBodyId() override {
        return StaticRectPhysics::getBodyId();
    }

    void onContact(ObjectPhysics *object) override {
        if (MainBallPhysics* main_ball_physics = object->getObjectAsType<MainBallPhysics*>(); main_ball_physics != nullptr) {
            // b2Body_ApplyLinearImpulse(main_ball_physics->getBodyId(), this->accelerationVector(), {0,0}, true);
        }
    }


    void step() override {
        StaticRectPhysics::step();
    }

private:
    b2Vec2 accelerationVector() {
        return b2MulSV(this->acceleration, b2RotateVector(b2MakeRot(this->static_rect->getRotation()), {0,1}));
    }

    float acceleration;

};



#endif //LAUNCHERPHYSICS_HPP
