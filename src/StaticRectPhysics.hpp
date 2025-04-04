//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECTPHYSICS_HPP
#define STATICRECTPHYSICS_HPP

#include "StaticRect.hpp"
#include "box2d/box2d.h"


class StaticRectPhysics {

public:
    StaticRectPhysics(StaticRect* static_rect, b2WorldId world_id) {
        // Physics init
        this->static_rect = static_rect;
        this->world_id = world_id;

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.position = {this->static_rect->getX(), this->static_rect->getY()};
        this->body_id = b2CreateBody(world_id, &bodyDef);
        b2Polygon dynamicBox = b2MakeBox(this->static_rect->getW()/2, this->static_rect->getH()/2);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.friction = 0.f;
        this->shape_id = b2CreatePolygonShape(this->body_id, &shapeDef, &dynamicBox);
    }

    void update() {
        b2Vec2 v = b2Body_GetPosition(this->body_id);

        std::cout << "Rect position" << std::endl;
        std::cout << v.x << " " << v.y << std::endl;

    }

private:
    StaticRect* static_rect;
    b2WorldId world_id;
    b2BodyId body_id;
    b2ShapeId shape_id;
};



#endif //STATICRECTPHYSICS_HPP
