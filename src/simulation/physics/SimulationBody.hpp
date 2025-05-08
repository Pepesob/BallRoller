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

    virtual Vector2D getPosition() = 0;
    [[nodiscard]] virtual float getRotation() const = 0;


protected:
    b2BodyId id={};
    Vector2D position;
    float rotation;

    friend class B2dSimulation;
    friend class B2dBodyBuilder;
};


template<typename T>
class ConfigurableBody: public SimulationBody {
public:

    explicit ConfigurableBody(const T& config=T()): SimulationBody(config.initial_position, config.initial_rotation) {
        this->config = config;
    }

    Vector2D getPosition() override {
        return B2_IS_NULL(this->id) ? this->config.initial_position: this->position;
    }

    [[nodiscard]] float getRotation() const override {
        return B2_IS_NULL(this->id) ? this->config.initial_rotation: this->rotation;
    }

    T config;
};



class RectangleBody: public ConfigurableBody<RectangleBodyConfig> {
public:
    void accept(BodyVisitor &visitor) override {
        visitor.visitRectangle(*this);
    }
};


class CircleBody: public ConfigurableBody<CircleBodyConfig> {
public:
    void accept(BodyVisitor &visitor) override {
        visitor.visitCircle(*this);
    }
};




#endif //SIMULATIONBODY_H
