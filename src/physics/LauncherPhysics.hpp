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
    LauncherPhysics(StaticRect* launcher, b2WorldId world_id, float bounciness): StaticRectPhysics(launcher, world_id, 0, bounciness) {
        this->bounciness = bounciness;
    }

    b2BodyId getBodyId() override {
        return StaticRectPhysics::getBodyId();
    }

    void onContact(ObjectPhysics *object) override {
    }


    void step() override {
        StaticRectPhysics::step();
    }

private:

    float bounciness;

};



#endif //LAUNCHERPHYSICS_HPP
