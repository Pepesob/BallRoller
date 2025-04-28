//
// Created by sp on 28.04.2025.
//
#include "Shape.hpp"

void ShapeBuilder::buildRectangle(const RectangleShape &rectangle) {
    b2Polygon dynamicBox = b2MakeBox(rectangle.size.x/2, rectangle.size.y/2);
    dynamicBox.centroid = {rectangle.position_self.x, rectangle.position_self.y};
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.friction = rectangle.config.friction;
    shapeDef.restitution = rectangle.config.restitution;
    shapeDef.density = rectangle.config.density;
    shapeDef.isSensor = rectangle.config.isSensor;
    shapeDef.enableSensorEvents = true;
    b2CreatePolygonShape(body_id, &shapeDef, &dynamicBox);
}

void ShapeBuilder::buildCircle(const CircleShape &shape) {
    b2Circle circle = {{0, 0}, shape.radius};
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = shape.config.density;
    shapeDef.friction = shape.config.friction;
    shapeDef.restitution = shape.config.restitution;
    shapeDef.enableSensorEvents = true;
    b2CreateCircleShape(this->body_id, &shapeDef, &circle);
}
