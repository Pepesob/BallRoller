//
// Created by sp on 28.04.2025.
//

#ifndef SHAPE_HPP
#define SHAPE_HPP


#include "common.hpp"
#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Screen.hpp"
#include "simulation/physics/SimulationBody.hpp"


class WorldShapeDrawer {
public:
    virtual ~WorldShapeDrawer() = default;

    virtual void draw(Screen* screen, Camera* camera)=0;

    Vector2D position{};
    float rotation=0;
};

class RectangleDrawer: public WorldShapeDrawer {
public:
    void draw(Screen* screen, Camera* camera) override {
        auto [w, h] = this->size;
        auto [x,y] = this->position;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setTexture(&texture);
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-this->rotation));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(this->shape);
    }

    Vector2D size{};
    sf::Texture texture;
    sf::RectangleShape shape;
};


class CircleDrawer: public WorldShapeDrawer {
public:
    void draw(Screen* screen, Camera* camera) override {
        auto [x, y] = this->position;
        float psf = screen->getPixelScaleFactor();
        circle.setOrigin({radius*psf*camera->getZoom(), radius*psf*camera->getZoom()});
        circle.setRadius(radius * psf * camera->getZoom());
        circle.setRotation(sf::radians(-this->rotation));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        circle.setPosition(v);
        circle.setTexture(&this->texture);
        screen->getWindow()->draw(circle);
    }

    float radius = 0;
    sf::CircleShape circle;
    sf::Texture texture;
};


class RectangleShapeDrawer {
public:
    void drawShape(RectangleBodyConfig config, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {
        auto [w, h] = config.size;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({objectPos.x, objectPos.y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(this->shape);
    }

    sf::RectangleShape shape;
};



class CircleShapeDrawer {
public:
    CircleShapeDrawer() {
        this->texture = sf::Texture("resources/pokeball_texture.png");
        this->circle.setTexture(&this->texture);
    }

    void drawShape(CircleBodyConfig config, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {

        float radius = config.radius;
        auto [x, y] = objectPos;
        float psf = screen->getPixelScaleFactor();
        circle.setOrigin({radius*psf*camera->getZoom(), radius*psf*camera->getZoom()});
        circle.setRadius(config.radius * psf * camera->getZoom());
        circle.setRotation(sf::radians(-objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        circle.setPosition(v);
        circle.setTexture(&this->texture);
        screen->getWindow()->draw(circle);
    }

    sf::CircleShape circle;
    sf::Texture texture;
};




#endif //SHAPE_HPP
