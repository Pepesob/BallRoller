//
// Created by sp on 24.04.2025.
//

#ifndef ACCELERATIONFIELDPHYSICS_HPP
#define ACCELERATIONFIELDPHYSICS_HPP
#include "AccelerationField.hpp"
#include "CollisionObserver.hpp"
#include "MainBallPhysics.hpp"

#include "box2d/box2d.h"


class AccelerationFieldPhysics: public CollisionObserver {
public:
    AccelerationFieldPhysics(AccelerationField* acceleration_field, b2WorldId world_id) {
        this->acceleration_field = acceleration_field;
        this->world_id = world_id;

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.position = {this->acceleration_field->getX(), this->acceleration_field->getY()};
        bodyDef.rotation = b2MakeRot(this->acceleration_field->getRotation());
        this->body_id = b2CreateBody(world_id, &bodyDef);
        b2Polygon dynamicBox = b2MakeBox(this->acceleration_field->getWidth()/2, this->acceleration_field->getHeight()/2);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.friction = 0;
        shapeDef.restitution = 0.1;
        shapeDef.isSensor = true;
        shapeDef.enableSensorEvents = true;
        this->shape_id = b2CreatePolygonShape(this->body_id, &shapeDef, &dynamicBox);
    }

    void onContact(ObjectPhysics *object) override {
        if (auto* main_ball_physics = object->getObjectAsType<MainBallPhysics*>()) {
            b2Body_ApplyForce(main_ball_physics->getBodyId(), this->b2dAccelerationVector(), {0,0}, true);
        }
    }

    b2BodyId getBodyId() override {
        return this->body_id;
    }

private:
    b2Vec2 b2dAccelerationVector() {
        auto [x, y] = this->acceleration_field->getAcceleration();
        return {x, y};
    }


    AccelerationField* acceleration_field;
    b2WorldId world_id = {};
    b2BodyId body_id = {};
    b2ShapeId shape_id = {};
};



#endif //ACCELERATIONFIELDPHYSICS_HPP
