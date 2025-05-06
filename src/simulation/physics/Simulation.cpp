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
    bodyDef.rotation = b2MakeRot(config.initial_rotation);
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

B2dSimulation::B2dSimulation(Vector2D gravity) {
    this->gravity = gravity;
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {this->gravity.x, this->gravity.y};
    this->world_id = b2CreateWorld(&worldDef);
}

void B2dSimulation::step() {
    b2World_Step(world_id, timeStep, subStepCount);
    collisionNotify(*this);
    for (auto sim_obj: this->objects) {
        sim_obj->step();
    }
    this->updateBodies();
}

void B2dSimulation::fixedStep() {
    if (this->prev_time == std::chrono::steady_clock::time_point::min()) {
        this->prev_time = std::chrono::steady_clock::now();
    }
    std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeStepChrono{this->timeStep};
    auto diff = current - this->prev_time;
    int possible_step_count = diff / timeStepChrono;


    int actual_step_count = std::ceil(std::sqrt(possible_step_count)); // > 0 ? 1 : 0;


    for (int i = 0; i < actual_step_count; i++) {
        this->step();
    }

    this->prev_time += std::chrono::duration_cast<std::chrono::nanoseconds>(timeStepChrono * actual_step_count);
}

void B2dSimulation::resetTimer() {
    this->prev_time = std::chrono::steady_clock::time_point::min();
}

void B2dSimulation::addObject(SimulationObjectBase& obj) {
    this->objects.push_back(&obj);
    for (SimulationBody* b: obj.getBodies()) {
        this->addBody(*b);
    }
    obj.simulation = this;
}

void B2dSimulation::addBody(SimulationBody &body) {
    if (B2_IS_NON_NULL(body.id)) {
        throw std::runtime_error("Body already exists in the simulation!");
    }
    B2dBodyBuilder builder(this->world_id);
    body.accept(builder);
    this->bodies.push_back(&body);
}

SimulationBody & B2dSimulation::b2dGetAssociatedBody(b2BodyId body_id) const {
    for (auto it: this->bodies) {
        if (B2_ID_EQUALS(it->id, body_id)) {
            return *it;
        }
    }
    throw std::runtime_error("Unknown body with given body_id");
}

SimulationObjectBase* B2dSimulation::getAssociatedObject(const SimulationBody& body) const {
    for (auto obj: this->objects) {
        for (const auto it2: obj->getBodies()) {
            if (B2_ID_EQUALS(it2->id, body.id)) {
                return obj;
            }
        }
    }
    return nullptr;
}

Vector2D B2dSimulation::getBodyPosition(SimulationBody &body) {
    b2BodyId body_id = body.id;
    b2Vec2 v = b2Body_GetPosition(body_id);
    return {v.x, v.y};
}

float B2dSimulation::getBodyRotation(SimulationBody &body) {
    b2BodyId body_id = body.id;
    b2Rot r = b2Body_GetRotation(body_id);
    return b2Rot_GetAngle(r);
}

void B2dSimulation::updateBodies() {
    for (auto body: this->bodies) {
        body->position = getBodyPosition(*body);
        body->rotation = getBodyRotation(*body);
    }
}

void B2dSimulation::applyForce(SimulationBody &body, Vector2D force) {
    b2BodyId body_id = body.id;
    b2Body_ApplyForce(body_id, {force.x, force.y}, {0,0}, false);
}

void B2dSimulation::setVelocity(SimulationBody &body, Vector2D velocity) {
    b2BodyId body_id = body.id;
    b2Body_SetLinearVelocity(body_id, {velocity.x, velocity.y});
}

Vector2D B2dSimulation::getVelocity(SimulationBody &body) {
    b2BodyId body_id = body.id;
    b2Vec2 v = b2Body_GetLinearVelocity(body_id);
    return {v.x, v.y};
}

