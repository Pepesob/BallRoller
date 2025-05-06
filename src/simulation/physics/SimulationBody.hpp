//
// Created by sp on 02.05.2025.
//

#ifndef SIMULATIONBODY_H
#define SIMULATIONBODY_H

#include <stdexcept>
#include <box2d/box2d.h>
#include "common.hpp"


class RectangleBody;
class CircleBody;

class BodyVisitor {
public:
    virtual ~BodyVisitor() = default;

    virtual void visitCircle(CircleBody& circle) = 0;
    virtual void visitRectangle(RectangleBody& rectangle) = 0;
};




struct SimulationBodyConfig {
    int bodyType = b2_staticBody;
    Vector2D initial_position = {0,0};
    float initial_rotation = 0.f;
    float friction = 0.5f;
    float restitution = 0.5f;
    float density = 1.f;
    bool isSensor = false;
};

struct RectangleBodyConfig: SimulationBodyConfig {
    Vector2D size = {1.f,0.1f};
};

struct CircleBodyConfig: SimulationBodyConfig {
    float radius = 0.1f;
};

class B2dBodyBuilder: public BodyVisitor {
public:
    explicit B2dBodyBuilder(b2WorldId world_id) {
        this->world_id = world_id;
    }

    void visitCircle(CircleBody& circle) override;
    void visitRectangle(RectangleBody& rectangle) override;
    static b2BodyId b2dCreateBody(const SimulationBodyConfig &config, b2WorldId world_id);
private:
    b2WorldId world_id{};
};

class SimulationBody {
public:
    virtual ~SimulationBody() = default;
    SimulationBody() = delete;

    SimulationBody(Vector2D initial_position, float initial_rotation): position(initial_position), rotation(initial_rotation) {}
    virtual void accept(BodyVisitor& visitor) = 0;

    Vector2D getPosition() const {
        return position;
    }

    float getRotation() const {
        return rotation;
    }

    void setPosition(const Vector2D& position) {
        if (!B2_IS_NULL(id)) {
            throw std::runtime_error("Can't set position when body is placed in simulation, use Simulation methods to change position");
        }
        this->position = position;
    }

    void setRotation(float rotation) {
        if (!B2_IS_NULL(id)) {
            throw std::runtime_error("Cant set rotation when body is placed in simulation, use Simulation methods to change rotation");
        }
        this->rotation = rotation;
    }

private:
    b2BodyId id={};
    Vector2D position;
    float rotation;

    friend class B2dSimulation;
    friend class B2dBodyBuilder;
};



class RectangleBody: public SimulationBody {
public:
    explicit RectangleBody(const RectangleBodyConfig& config=RectangleBodyConfig()): SimulationBody(config.initial_position, config.initial_rotation) {
        this->config = config;
    }

    void accept(BodyVisitor &visitor) override {
        visitor.visitRectangle(*this);
    }

    RectangleBodyConfig config;
};


class CircleBody: public SimulationBody {
public:
    explicit CircleBody(const CircleBodyConfig& config=CircleBodyConfig()): SimulationBody(config.initial_position, config.initial_rotation) {
        this->config = config;
    }

    void accept(BodyVisitor &visitor) override {
        visitor.visitCircle(*this);
    }

    CircleBodyConfig config;
};




#endif //SIMULATIONBODY_H
