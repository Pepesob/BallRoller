//
// Created by sp on 27.04.2025.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "common.hpp"
#include "Drawer.hpp"
#include <SFML/Graphics.hpp>


class Rectangle: public Shape {
public:
    [[nodiscard]] virtual Vector2D getSize() const = 0;
};

class RectanglePrototype : public Rectangle, public ShapePrototype {
public:
    [[nodiscard]] Vector2D getPosition() const override {
        return this->position;
    }

    [[nodiscard]] float getRotation() const override {
        return this->rotation;
    }

    [[nodiscard]] Vector2D getSize() const override {
        return this->size;
    }

    void setPosition(const Vector2D &position) override {
        this->position = position;
    }

    void setSize(const Vector2D &size) {
        this->size = size;
    }

    void setRotation(float rotation) override {
        this->rotation = rotation;
    }

private:
    Vector2D position{};
    Vector2D size{};
    float rotation=0;
};

struct RectanglePhysicsConfig: ObjectPhysicsConfig {
    Vector2D size = {1,1};
    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 1.f;
    b2BodyType bodyType = b2_staticBody;
    bool isSensor = false;
    bool enableSensorEvents = false;
};


class RectanglePhysics: public ObjectPhysics, public Rectangle {
public:
    explicit RectanglePhysics(b2WorldId world_id, const RectanglePhysicsConfig& config=RectanglePhysicsConfig()) {
        this->world_id = world_id;

        this->size = config.size;

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = config.bodyType;
        bodyDef.position = {config.position.x, config.position.y};
        bodyDef.rotation = b2MakeRot(config.rotation);
        this->body_id = b2CreateBody(world_id, &bodyDef);

        b2Polygon dynamicBox = b2MakeBox(config.size.x/2, config.size.y/2);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.friction = config.friction;
        shapeDef.restitution = config.restitution;
        shapeDef.density = config.density;
        shapeDef.isSensor = config.isSensor;
        shapeDef.enableSensorEvents = config.enableSensorEvents;
        this->shape_id = b2CreatePolygonShape(this->body_id, &shapeDef, &dynamicBox);
    }

    [[nodiscard]] Vector2D getPosition() const override {
        auto [x, y] = b2Body_GetPosition(this->body_id);
        return {x, y};
    }

    [[nodiscard]] Vector2D getSize() const override {
        return this->size;
    }

    [[nodiscard]] float getRotation() const override {
        return b2Rot_GetAngle(b2Body_GetRotation(this->body_id));
    }

    [[nodiscard]] b2ShapeId getShapeId() const {
        return this->shape_id;
    }
    b2BodyId getBodyId() override {
        return this->body_id;
    }

    void onContact(ObjectPhysics *object) override {
        // if (auto* ball = object->getObjectAsType<MainBallPhysics*>()) {
        //     std::cout << "Collision with ball" << std::endl;
        // }
    }

    void step() override {

    }

protected:
    b2WorldId world_id = {};
    b2BodyId body_id = {};
    b2ShapeId shape_id = {};
    Vector2D size = {};
};

class RectangleDrawer: public Drawer {
public:

    explicit RectangleDrawer(Rectangle* static_rect) {
        this->static_rect = static_rect;
        this->shape.setFillColor(sf::Color(222,184,135));
    }

    explicit RectangleDrawer(Rectangle* static_rect, sf::Color color) {
        this->static_rect = static_rect;
        this->shape.setFillColor(color);
    }


    void draw(Screen* screen, Camera* camera) override {
        auto [x, y] = this->static_rect->getPosition();
        auto [w, h] = this->static_rect->getSize();
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-this->static_rect->getRotation()));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(shape);
    }

private:
    Rectangle* static_rect;
    sf::RectangleShape shape;
};






#endif //RECTANGLE_HPP
