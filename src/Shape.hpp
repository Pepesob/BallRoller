//
// Created by sp on 28.04.2025.
//

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>
#include <box2d/box2d.h>
#include "common.hpp"
#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Screen.hpp"

class RectangleShape;
class CircleShape;
class SimulationObject;
class B2dSimulation;
class CircleBody;
class RectangleBody;
class SimulationBody;
class SimulationBodyConfig;
void collisionNotify(B2dSimulation& simulation);

// class ShapeBuilder {
// public:
//     explicit ShapeBuilder(b2BodyId body_id) {
//         this->body_id = body_id;
//     }
//
//     void buildRectangle(const RectangleShape& rectangle);
//     void buildCircle(const CircleShape& shape);
//
// private:
//     b2BodyId body_id{};
// };


class B2dBodyBuilder {
public:
    static void buildCircle(CircleBody& circle, b2WorldId world_id);
    static void buildRectangle(RectangleBody& rectangle, b2WorldId world_id);
    static b2BodyId b2dCreateBody(const SimulationBodyConfig &config, b2WorldId world_id);
};



// class SimulationShape {
// public:
//     virtual ~SimulationShape() = default;
//
//     virtual void accept(ShapeBuilder& builder) = 0;
// };

//
// struct ShapeConfig {
//     float friction = 0;
//     float restitution = 0.5f;
//     float density = 1.f;
//     bool isSensor = false;
// };
//
// class RectangleShape : public SimulationShape {
// public:
//     RectangleShape(Vector2D size, const ShapeConfig& config=ShapeConfig()) {
//         this->size = size;
//         this->config = config;
//     }
//
//     void accept(ShapeBuilder& builder) override {
//         builder.buildRectangle(*this);
//     }
//
//     Vector2D size={1,1};
//     ShapeConfig config;
// };
//
// class CircleShape: public SimulationShape {
// public:
//     CircleShape(Vector2D position_self, float radius, const ShapeConfig& config=ShapeConfig()) {
//         this->position_self = position_self;
//         this->radius = radius;
//         this->config = config;
//     }
//
//     void accept(ShapeBuilder& builder) override {
//         builder.buildCircle(*this);
//     }
//
//     Vector2D position_self={};
//     float radius;
//     ShapeConfig config;
// };
//

struct SimulationBodyConfig {
    int bodyType = b2_staticBody;
    Vector2D position = {0,0};
    float rotation = 0.f;
    float friction = 0.5f;
    float restitution = 0.5f;
    float density = 1.f;
    bool isSensor = false;
};

class SimulationBody {
public:
    virtual ~SimulationBody() = default;

private:
    virtual void build(b2WorldId world_id) = 0;
    b2BodyId id={};

    friend class B2dSimulation;
    friend class B2dBodyBuilder;
};

struct CircleBodyConfig: SimulationBodyConfig {
    float radius = 0.1f;
};

class CircleBody: public SimulationBody {
public:
    explicit CircleBody(const CircleBodyConfig& config=CircleBodyConfig()) {
        this->config=config;
    }

    CircleBodyConfig config;
private:
    void build(b2WorldId world_id) override {
        B2dBodyBuilder::buildCircle(*this, world_id);
    }
};

struct RectangleBodyConfig: SimulationBodyConfig {
    Vector2D size = {1.f,0.1f};
};

class RectangleBody: public SimulationBody {
public:
    explicit RectangleBody(const RectangleBodyConfig& config=RectangleBodyConfig()) {
        this->config=config;
    }

    RectangleBodyConfig config;

private:
    void build(b2WorldId world_id) override {
        B2dBodyBuilder::buildRectangle(*this, world_id);
    }
};

class B2dSimulation {
public:
    explicit B2dSimulation(Vector2D gravity) {
        this->gravity = gravity;
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {this->gravity.x, this->gravity.y};
        this->world_id = b2CreateWorld(&worldDef);
    }

    void step();

    void fixedStep() {
        if (this->prev_time == std::chrono::steady_clock::time_point::min()) {
            this->prev_time = std::chrono::steady_clock::now();
        }
        std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
        std::chrono::duration<float> timeStepChrono{this->timeStep};
        auto diff = current - this->prev_time;
        int possible_step_count = diff / timeStepChrono;


        int actual_step_count = std::ceil(std::sqrt(possible_step_count)); // > 0 ? 1 : 0;

        std::cout<<actual_step_count<<std::endl;

        for (int i = 0; i < actual_step_count; i++) {
            this->step();
        }

        this->prev_time += std::chrono::duration_cast<std::chrono::nanoseconds>(timeStepChrono * actual_step_count);
    }

    void resetTimer() {
        this->prev_time = std::chrono::steady_clock::time_point::min();
    }

    void addObject(const std::shared_ptr<SimulationObject> &obj);

    void addBody(SimulationBody& body) {
        body.build(this->world_id);
        this->bodies.push_back(&body);
    }

    [[nodiscard]] SimulationBody& b2dGetAssociatedBody(b2BodyId body_id) const {
        for (auto it: this->bodies) {
            if (B2_ID_EQUALS(it->id, body_id)) {
                return *it;
            }
        }
        throw std::runtime_error("Unknown body with given body_id");
    }

    std::shared_ptr<SimulationObject> getAssociatedObject(const SimulationBody& body) const;

    Vector2D getBodyPosition(SimulationBody& body) {
        b2BodyId body_id = body.id;
        b2Vec2 v = b2Body_GetPosition(body_id);
        return {v.x, v.y};
    }

    float getBodyRotation(SimulationBody& body) {
        b2BodyId body_id = body.id;
        b2Rot r = b2Body_GetRotation(body_id);
        return b2Rot_GetAngle(r);
    }

    void applyForce(SimulationBody& body, Vector2D force) {
        b2BodyId body_id = body.id;
        b2Body_ApplyForce(body_id, {force.x, force.y}, {0,0}, false);
    }

    // void addBody(SimulationBody& body) {
    //     b2BodyId body_id = this->b2dCreateBody(body);
    //     body.id = body_id;
    //     this->bodiesSet.insert(body_id);
    // }

    // static void b2dAddShapeToBody(b2BodyId body_id, SimulationShape& shape) {
    //     ShapeBuilder builder(body_id);
    //     shape.accept(builder);
    // }

    std::vector<SimulationBody*> bodies;
    std::vector<std::shared_ptr<SimulationObject>> objects;
    b2WorldId world_id {};
    Vector2D gravity = {0,0};
    float timeStep = 1.f/60.f;
    int subStepCount = 4;
private:
    std::chrono::steady_clock::time_point prev_time = std::chrono::steady_clock::time_point::min();
};



class SimulationObject {
public:
    virtual ~SimulationObject() = default;
    virtual void onCollisionBegin(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void onCollisionEnd(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void step() {}
    virtual std::vector<SimulationBody*> getBodies() {return {};}
};

class AcceleratorObject : public SimulationObject {
public:
    void onCollisionBegin(B2dSimulation &simulation, SimulationBody& this_body, SimulationBody& other_body) override {
        simulation.applyForce(other_body, {10,0});
    }

    // void onCollisionEnd(B2dSimulation &simulation, SimulationBody &this_body, SimulationBody &other_body) override;
};



class RectangleShapeRenderer {
public:
    void drawShape(RectangleBody& shape, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {
        auto [w, h] = shape.config.size;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({objectPos.x, objectPos.y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(this->shape);
    }

private:
    sf::RectangleShape shape;
};

class CircleShapeRenderer {
public:
    CircleShapeRenderer() {
        const unsigned int texSize = 256;
        sf::Image image;
        image.resize({texSize, texSize},sf::Color::Transparent);

        // Fill image with two colors
        for (unsigned int y = 0; y < texSize; ++y)
        {
            for (unsigned int x = 0; x < texSize; ++x)
            {
                float factor = static_cast<float>(y) / texSize; // Vertical gradient
                unsigned int r = ((1.0f - factor) * 255 + factor * 0);   // From Red to Blue
                unsigned int g = ((1.0f - factor) * 0   + factor * 0);
                unsigned int b = ((1.0f - factor) * 0   + factor * 255);
                image.setPixel({x, y}, sf::Color(r, g, b));
            }
        }

        // Load texture from image
        bool res = this->texture.loadFromImage(image);
        if (!res) {
            throw std::runtime_error("Failed to load texture from image");
        }
    }

    void drawShape(CircleBody& shape, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {
        sf::CircleShape circle;
        float radius = shape.config.radius;
        auto [x, y] = objectPos;
        float psf = screen->getPixelScaleFactor();
        circle.setOrigin({radius*psf*camera->getZoom(), radius*psf*camera->getZoom()});
        circle.setRadius(shape.config.radius * psf * camera->getZoom());
        circle.setRotation(sf::radians(-objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        circle.setPosition(v);
        circle.setTexture(&this->texture);
        screen->getWindow()->draw(circle);
    }

private:
    sf::Texture texture;
};

#endif //SHAPE_HPP
