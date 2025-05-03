//
// Created by sp on 02.05.2025.
//

#ifndef SIMULATIONBODY_H
#define SIMULATIONBODY_H

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
    float rotation = 0.f;
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

    virtual void accept(BodyVisitor& visitor) = 0;

private:
    b2BodyId id={};

    friend class B2dSimulation;
    friend class B2dBodyBuilder;
};



class RectangleBody: public SimulationBody {
public:
    explicit RectangleBody(const RectangleBodyConfig& config=RectangleBodyConfig()) {
        this->config=config;
    }

    void accept(BodyVisitor &visitor) override {
        visitor.visitRectangle(*this);
    }

    RectangleBodyConfig config;
};


class CircleBody: public SimulationBody {
public:
    explicit CircleBody(const CircleBodyConfig& config=CircleBodyConfig()) {
        this->config=config;
    }

    void accept(BodyVisitor &visitor) override {
        visitor.visitCircle(*this);
    }

    CircleBodyConfig config;
};




#endif //SIMULATIONBODY_H
