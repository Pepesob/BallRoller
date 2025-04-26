//
// Created by sp on 04.04.2025.
//

#include "RectanglePhysics.hpp"

RectanglePhysics::RectanglePhysics(b2WorldId world_id, const RectanglePhysicsConfig& config) {
    this->world_id = world_id;

    this->size = config.size;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = config.bodyType;
    bodyDef.position = {config.position.x, config.position.y};
    bodyDef.rotation = b2MakeRot(config.rotation);
    this->body_id = b2CreateBody(world_id, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(config.size.x/2, config.size.y/2);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.friction = config.friction;
    shapeDef.restitution = config.restitution;
    shapeDef.density = config.density;
    this->shape_id = b2CreatePolygonShape(this->body_id, &shapeDef, &dynamicBox);
}



void RectanglePhysics::step() {
    // b2Polygon polygon = b2Shape_GetPolygon(this->shape_id);
}


