//
// Created by sp on 02.04.2025.
//

#ifndef MAINBALLPHYSICS_HPP
#define MAINBALLPHYSICS_HPP

#include "box2d/box2d.h"
#include "MainBall.hpp"


class MainBallPhysics {

public:
    MainBallPhysics(MainBall* main_ball, b2WorldId world_id) {
        // Physics init
        this->main_ball = main_ball;

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = {this->main_ball->getX(), this->main_ball->getY()};
        this->body_id = b2CreateBody(world_id, &bodyDef);
        b2Circle circle = {{0, 0}, this->main_ball->getRatius()};
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.friction = 0.f;
        shapeDef.restitution = 0.8f;
        this->shape_id = b2CreateCircleShape(this->body_id, &shapeDef, &circle);
    }

    void update() {
        b2Vec2 v = b2Body_GetPosition(this->body_id);
        this->main_ball->setXY(v.x, v.y);
        std::cout << "Ball position" << std::endl;
        std::cout << v.x << " " << v.y << std::endl;
    }

private:
    MainBall* main_ball;
    b2BodyId body_id;
    b2ShapeId shape_id;
};



#endif //MAINBALLPHYSICS_HPP
