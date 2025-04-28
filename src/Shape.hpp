//
// Created by sp on 28.04.2025.
//

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <box2d/box2d.h>

#include "common.hpp"
#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Screen.hpp"

class RectangleShape;
class CircleShape;

class ShapeBuilder {
public:
    explicit ShapeBuilder(b2BodyId body_id) {
        this->body_id = body_id;
    }

    void buildRectangle(const RectangleShape& rectangle);
    void buildCircle(const CircleShape& shape);

private:
    b2BodyId body_id{};
};


class SimulationShape {
public:
    virtual ~SimulationShape() = default;

    virtual void accept(ShapeBuilder& builder) = 0;
};


struct ShapeConfig {
    float friction = 0;
    float restitution = 0.5f;
    float density = 1.f;
    bool isSensor = false;
};

class RectangleShape : public SimulationShape {
public:
    RectangleShape(Vector2D position_self, Vector2D size, const ShapeConfig& config=ShapeConfig()) {
        this->position_self = position_self;
        this->size = size;
        this->config = config;
    }

    void accept(ShapeBuilder& builder) override {
        builder.buildRectangle(*this);
    }

    Vector2D position_self={};
    Vector2D size={1,1};
    ShapeConfig config;
};

class CircleShape: public SimulationShape {
public:
    CircleShape(Vector2D position_self, float radius, const ShapeConfig& config=ShapeConfig()) {
        this->position_self = position_self;
        this->radius = radius;
        this->config = config;
    }

    void accept(ShapeBuilder& builder) override {
        builder.buildCircle(*this);
    }

    Vector2D position_self={};
    float radius;
    ShapeConfig config;
};


struct SimulationBodyConfig {
    int bodyType = b2_staticBody;
    Vector2D position = {0,0};
    float rotation = 0.f;
};

class SimulationBody {
public:
    virtual ~SimulationBody() = default;

    explicit SimulationBody(const SimulationBodyConfig& config=SimulationBodyConfig()) {
        this->config = config;
        // this->id = count++;
    }

    void addShape(SimulationShape* shape) {
        shapes.push_back(shape);
    }

    SimulationBodyConfig config;
    std::vector<SimulationShape*> shapes;

//     bool operator==(const SimulationBody &body) const {
//         return this->id == body.id;
//     }
//
//
// private:
//     friend struct std::hash<SimulationBody>;
//     static unsigned int count;
//     unsigned int id;
};

// template<>
// struct std::hash<SimulationBody> {
//     size_t operator()(const SimulationBody& body) const noexcept {
//         return hash<unsigned int>()(body.id);
//     }
// };




class B2dSimulation {

public:
    B2dSimulation(Vector2D gravity) {
        this->gravity = gravity;
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {this->gravity.x, this->gravity.y};
        this->world_id = b2CreateWorld(&worldDef);
    }

    void step() {
        b2World_Step(world_id, timeStep, subStepCount);
    }

    void addBody(SimulationBody* body) {
        b2BodyId body_id = this->b2dCreateBody(*body);
        for (auto shape: body->shapes) {
            b2dAddShapeToBody(body_id, *shape);
        }
        this->bodies[body] = body_id;
    }

    Vector2D getBodyPosition(SimulationBody* body) {
        b2BodyId body_id = this->bodies[body];
        b2Vec2 v = b2Body_GetPosition(body_id);
        return {v.x, v.y};
    }

    float getBodyRotation(SimulationBody* body) {
        b2BodyId body_id = this->bodies[body];
        b2Rot r = b2Body_GetRotation(body_id);
        return b2Rot_GetAngle(r);
    }

private:
    b2BodyId b2dCreateBody(SimulationBody& body) const {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.position = {body.config.position.x, body.config.position.y};
        bodyDef.rotation = b2MakeRot(body.config.rotation);
        bodyDef.type = static_cast<b2BodyType>(body.config.bodyType);
        return b2CreateBody(this->world_id, &bodyDef);
    }

    static void b2dAddShapeToBody(b2BodyId body_id, SimulationShape& shape) {
        ShapeBuilder builder(body_id);
        shape.accept(builder);
    }

    std::unordered_map<SimulationBody*, b2BodyId> bodies;
    b2WorldId world_id {};
    Vector2D gravity = {0,0};
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
};

class RectangleShapeRenderer {
public:
    void drawShape(RectangleShape& shape, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {
        auto [x, y] = shape.position_self;
        auto [w, h] = shape.size;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({objectPos.x, objectPos.y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(this->shape);
    }

private:
    // sf::RenderTexture renderTexture;
    sf::RectangleShape shape;
};

class CircleShapeRenderer {
public:
    void drawShape(CircleShape& shape, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {
        sf::CircleShape circle;
        float radius = shape.radius;
        auto [x, y] = objectPos;
        circle.setRadius(shape.radius * screen->getPixelScaleFactor() * camera->getZoom());
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({
            x - radius, y + radius
        });
        circle.setPosition(v);
        screen->getWindow()->draw(circle);
    }
};

#endif //SHAPE_HPP
