
#include "MainBallPhysics.hpp"


MainBallPhysics::MainBallPhysics(b2WorldId world_id, const BallPhysicsConfig &config) {
    this->world_id = world_id;
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {config.position.x, config.position.y};
    this->body_id = b2CreateBody(world_id, &bodyDef);
    b2Circle circle = {{0, 0}, config.radius};
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = config.density;
    shapeDef.friction = config.friction;
    shapeDef.restitution = config.restitution;
    shapeDef.enableSensorEvents = true;
    this->shape_id = b2CreateCircleShape(this->body_id, &shapeDef, &circle);
}


b2BodyId MainBallPhysics::getBodyId() const {
    return this->body_id;
}

b2ShapeId MainBallPhysics::getShapeId() const {
    return this->shape_id;
}

Vector2D MainBallPhysics::getPosition() const {
    auto [x, y] = b2Body_GetPosition(this->body_id);
    return {x, y};
}

float MainBallPhysics::getRadius() const {
    return b2Shape_GetCircle(this->shape_id).radius;
}

float MainBallPhysics::getRotation() const {
    return b2Rot_GetAngle(b2Body_GetRotation(this->body_id));
}

b2BodyId MainBallPhysics::getBodyId() {
    return this->body_id;
}

void MainBallPhysics::step() {
    // b2Vec2 v = b2Body_GetPosition(this->body_id);
}
