//
// Created by sp on 02.04.2025.
//

#ifndef MAINBALLPHYSICS_HPP
#define MAINBALLPHYSICS_HPP

#include "ObjectPhysics.hpp"
#include "common.hpp"
#include "box2d/box2d.h"


struct BallPhysicsConfig: ObjectPhysicsConfig {
    float radius = 0.1f;
    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 1.f;

    BallPhysicsConfig() {
        this->position = {0,1};
    }
};


class MainBallPhysics: public ObjectPhysics {

public:
    explicit MainBallPhysics(b2WorldId world_id, const BallPhysicsConfig& config=BallPhysicsConfig());

    [[nodiscard]] b2BodyId getBodyId() const;
    [[nodiscard]] b2ShapeId getShapeId() const;

    [[nodiscard]] Vector2D getPosition() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] float getRotation() const;

    b2BodyId getBodyId() override;

    void onContactBegin(ObjectPhysics *object) override {}

    void step() override;

private:
    b2WorldId world_id = {};
    b2BodyId body_id = {};
    b2ShapeId shape_id = {};
};



#endif //MAINBALLPHYSICS_HPP
