//
// Created by sp on 28.04.2025.
//
#include "Shape.hpp"

void ShapeBuilder::buildRectangle(const RectangleShape &rectangle) {
    b2Polygon dynamicBox = b2MakeBox(rectangle.size.x/2, rectangle.size.y/2);
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

void B2dSimulation::step() {
    b2World_Step(world_id, timeStep, subStepCount);
    collisionNotify(*this);
    for (auto sim_obj: this->objects) {
        sim_obj->step();
    }
}

void B2dSimulation::addObject(SimulationObject *obj) {
    this->objects.push_back(obj);
    for (auto b: obj->bodies) {
        this->addBody(b);
    }
}

SimulationObject * B2dSimulation::getAssociatedObject(SimulationBody* body) const {
    for (auto obj: this->objects) {
        for (auto it2: obj->bodies) {
            if (it2 == body) {
                return obj;
            }
        }
    }
    return nullptr;
}

void collisionNotify(B2dSimulation &simulation) {
    b2ContactEvents contactEvents = b2World_GetContactEvents(simulation.world_id);
    for (int i = 0; i < contactEvents.beginCount; ++i)
    {
        b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
        b2BodyId body_a = b2Shape_GetBody(beginEvent->shapeIdA);
        b2BodyId body_b = b2Shape_GetBody(beginEvent->shapeIdB);

        SimulationBody* obja = simulation.getAssociatedBody(body_a);
        SimulationBody* objb = simulation.getAssociatedBody(body_b);
        if (obja == nullptr || objb == nullptr) {
            throw std::runtime_error("Object that collided is not registered!");
        }
        if (auto sim_obj_a = simulation.getAssociatedObject(obja)) {
            sim_obj_a->onCollisionBegin(simulation, *obja, *objb);
        }
        if (auto sim_obj_b = simulation.getAssociatedObject(objb)) {
            sim_obj_b->onCollisionBegin(simulation, *objb, *obja);
        }
    }

    b2SensorEvents sensor_events = b2World_GetSensorEvents(simulation.world_id);
    for (int i = 0; i < sensor_events.beginCount; ++i)
    {
        b2SensorBeginTouchEvent* beginEvent = sensor_events.beginEvents + i;
        b2BodyId body_a = b2Shape_GetBody(beginEvent->sensorShapeId);
        b2BodyId body_b = b2Shape_GetBody(beginEvent->visitorShapeId);

        SimulationBody* obja = simulation.getAssociatedBody(body_a);
        SimulationBody* objb = simulation.getAssociatedBody(body_b);
        if (obja == nullptr || objb == nullptr) {
            throw std::runtime_error("Object that collided is not registered!");
        }
        if (auto sim_obj_a = simulation.getAssociatedObject(obja)) {
            sim_obj_a->onCollisionBegin(simulation, *obja, *objb);
        }
        if (auto sim_obj_b = simulation.getAssociatedObject(objb)) {
            sim_obj_b->onCollisionBegin(simulation, *objb, *obja);
        }
    }
}
