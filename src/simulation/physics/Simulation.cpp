//
// Created by sp on 02.05.2025.
//

#include "simulation/physics/Simulation.hpp"

void collisionNotify(B2dSimulation &simulation) {
    b2ContactEvents contactEvents = b2World_GetContactEvents(simulation.world_id);
    for (int i = 0; i < contactEvents.beginCount; ++i)
    {
        b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
        b2BodyId body_a = b2Shape_GetBody(beginEvent->shapeIdA);
        b2BodyId body_b = b2Shape_GetBody(beginEvent->shapeIdB);

        SimulationBody& obja = simulation.b2dGetAssociatedBody(body_a);
        SimulationBody& objb = simulation.b2dGetAssociatedBody(body_b);

        if (auto sim_obj_a = simulation.getAssociatedObject(obja)) {
            sim_obj_a->onCollisionBegin(simulation, obja, objb);
        }
        if (auto sim_obj_b = simulation.getAssociatedObject(objb)) {
            sim_obj_b->onCollisionBegin(simulation, objb, obja);
        }
    }

    b2SensorEvents sensor_events = b2World_GetSensorEvents(simulation.world_id);
    for (int i = 0; i < sensor_events.beginCount; ++i)
    {
        b2SensorBeginTouchEvent* beginEvent = sensor_events.beginEvents + i;
        b2BodyId body_a = b2Shape_GetBody(beginEvent->sensorShapeId);
        b2BodyId body_b = b2Shape_GetBody(beginEvent->visitorShapeId);

        SimulationBody& obja = simulation.b2dGetAssociatedBody(body_a);
        SimulationBody& objb = simulation.b2dGetAssociatedBody(body_b);

        if (auto sim_obj_a = simulation.getAssociatedObject(obja)) {
            sim_obj_a->onCollisionBegin(simulation, obja, objb);
        }
        if (auto sim_obj_b = simulation.getAssociatedObject(objb)) {
            sim_obj_b->onCollisionBegin(simulation, objb, obja);
        }
    }
}


b2BodyId B2dBodyBuilder::b2dCreateBody(const SimulationBodyConfig &config, b2WorldId world_id) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = {config.initial_position.x, config.initial_position.y};
    bodyDef.rotation = b2MakeRot(config.rotation);
    bodyDef.type = static_cast<b2BodyType>(config.bodyType);
    return b2CreateBody(world_id, &bodyDef);
}

void B2dBodyBuilder::visitRectangle(RectangleBody &rectangle) {
    rectangle.id = b2dCreateBody(rectangle.config, world_id);
    b2Polygon dynamicBox = b2MakeBox(rectangle.config.size.x/2, rectangle.config.size.y/2);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.friction = rectangle.config.friction;
    shapeDef.restitution = rectangle.config.restitution;
    shapeDef.density = rectangle.config.density;
    shapeDef.isSensor = rectangle.config.isSensor;
    shapeDef.enableSensorEvents = true;
    b2CreatePolygonShape(rectangle.id, &shapeDef, &dynamicBox);
}

void B2dBodyBuilder::visitCircle(CircleBody &circle) {
    circle.id = b2dCreateBody(circle.config, world_id);
    b2Circle b2d_circle = {{0, 0}, circle.config.radius};
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = circle.config.density;
    shapeDef.friction = circle.config.friction;
    shapeDef.restitution = circle.config.restitution;
    shapeDef.enableSensorEvents = true;
    b2CreateCircleShape(circle.id, &shapeDef, &b2d_circle);
}

void B2dSimulation::step() {
    b2World_Step(world_id, timeStep, subStepCount);
    collisionNotify(*this);
    for (auto sim_obj: this->objects) {
        sim_obj->step();
    }
}

void B2dSimulation::addObject(const std::shared_ptr<SimulationObjectBase> &obj) {
    this->objects.push_back(obj);
    for (SimulationBody* b: obj->getBodies()) {
        this->addBody(*b);
    }
    obj->simulation = this;
}

std::shared_ptr<SimulationObjectBase> B2dSimulation::getAssociatedObject(const SimulationBody& body) const {
    for (auto obj: this->objects) {
        for (const auto it2: obj->getBodies()) {
            if (B2_ID_EQUALS(it2->id, body.id)) {
                return obj;
            }
        }
    }
    return nullptr;
}

