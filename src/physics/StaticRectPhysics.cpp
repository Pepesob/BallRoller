//
// Created by sp on 04.04.2025.
//

#include "StaticRectPhysics.hpp"

StaticRectPhysics::StaticRectPhysics(StaticRect *static_rect, b2WorldId world_id) {
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

void StaticRectPhysics::step() {
    b2Polygon polygon = b2Shape_GetPolygon(this->shape_id);
}
