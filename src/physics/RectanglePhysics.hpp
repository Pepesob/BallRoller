//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECTPHYSICS_HPP
#define STATICRECTPHYSICS_HPP

#include "common.hpp"
#include "MainBallPhysics.hpp"
#include <iostream>

#include "ObjectPhysics.hpp"
#include "box2d/box2d.h"

struct RectanglePhysicsConfig {
    Vector2D position = {0,0};
    Vector2D size = {1,1};
    float rotation = 0;
    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 1.f;
    b2BodyType bodyType = b2_staticBody;
};


class RectanglePhysics: public ObjectPhysics {
public:
    RectanglePhysics(b2WorldId world_id, const RectanglePhysicsConfig& config=RectanglePhysicsConfig());

    [[nodiscard]] Vector2D getPosition() const {
        auto [x, y] = b2Body_GetPosition(this->body_id);
        return {x, y};
    }

    [[nodiscard]] Vector2D getSize() const {
        return this->size;
    }

    [[nodiscard]] float getRotation() const {
        return b2Rot_GetAngle(b2Body_GetRotation(this->body_id));
    }

    [[nodiscard]] b2ShapeId getShapeId() const {
        return this->shape_id;
    }
    b2BodyId getBodyId() override {
        return this->body_id;
    }

    void onContact(ObjectPhysics *object) override {
        if (auto* ball = object->getObjectAsType<MainBallPhysics*>()) {
            std::cout << "Collision with ball" << std::endl;
        }
    }

    void step() override;

protected:
    b2WorldId world_id = {};
    b2BodyId body_id = {};
    b2ShapeId shape_id = {};
    Vector2D size = {};
};



#endif //STATICRECTPHYSICS_HPP
