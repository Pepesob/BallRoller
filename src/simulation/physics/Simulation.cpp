#include "Simulation.hpp"

#include "simulation/objects/SimulationObjectBase.hpp"

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

    rectangle.position = rectangle.config.initial_position;
    rectangle.rotation = rectangle.config.initial_rotation;
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

    circle.position = circle.config.initial_position;
    circle.rotation = circle.config.initial_rotation;
}




B2dSimulation::B2dSimulation(Vector2D gravity) {
    this->gravity = gravity;
    this->createWorld();
}

B2dSimulation::B2dSimulation(const YAML::Node &config) {
    this->gravity = config["gravity"].as<Vector2D>();
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {this->gravity.x, this->gravity.y};
    this->world_id = b2CreateWorld(&worldDef);
}

B2dSimulation::~B2dSimulation() {
    this->destroyWorld();
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
    if (this->check_click) {
        this->clickNotify(this->click_world_point);
        this->check_click = false;
    }


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

void B2dSimulation::teleport(SimulationBody &body, Vector2D position) {
    b2Rot rotation = b2MakeRot(body.rotation);
    b2Body_SetTransform(body.id, {position.x, position.y}, rotation);
}

void B2dSimulation::click(Vector2D world_point) {
    this->check_click = true;
    this->click_world_point = world_point;
}

void B2dSimulation::clickNotify(Vector2D world_point)
{
    const int max_shape_n = 10;
    b2ShapeId shape_ids[max_shape_n];
    for (auto body : this->bodies) {
        b2Body_GetShapes(body->id, shape_ids, max_shape_n);
        int shape_n = b2Body_GetShapeCount(body->id);
        for (int i = 0; i < shape_n; i++) {
            if (b2Shape_TestPoint(shape_ids[i], { world_point.x, world_point.y})) {
                auto obj = this->getAssociatedObject(*body);
                obj->onClick();
            }
        }
    }
}

Vector2D B2dSimulation::getVelocity(SimulationBody &body) {
    b2BodyId body_id = body.id;
    b2Vec2 v = b2Body_GetLinearVelocity(body_id);
    return {v.x, v.y};
}

void B2dSimulation::destroyWorld() {
    if (!b2World_IsValid(this->world_id)) {
        throw std::runtime_error("World does not exist");
    }
    for (const auto obj: this->objects) {
        obj->simulation = nullptr;
    }
    for (const auto body: this->bodies) {
        body->id = b2_nullBodyId;
    }
    this->objects.clear();
    this->bodies.clear();
    b2DestroyWorld(this->world_id);
    this->world_id = b2_nullWorldId;
}

void B2dSimulation::createWorld() {
    if (b2World_IsValid(this->world_id)) {
        throw std::runtime_error("World alerady exist");
    }
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {this->gravity.x, this->gravity.y};
    this->world_id = b2CreateWorld(&worldDef);
    this->prev_time = std::chrono::steady_clock::time_point::min();
}


