//
// Created by sp on 06.05.2025.
//

#ifndef BODYDRAWER_HPP
#define BODYDRAWER_HPP
#include "ShapeDrawer.hpp"
#include "simulation/physics/SimulationBody.hpp"


class BodyDrawer {
public:
    virtual ~BodyDrawer() = default;

    virtual void draw(Screen* screen, Camera* camera) = 0;
};

class RectangleBodyDrawer: public BodyDrawer {
public:
    RectangleBodyDrawer(RectangleBody* body) {
        this->rectangle = body;
    }

    void draw(Screen* screen, Camera* camera) override {
        this->drawer.size = rectangle->config.size;
        drawer.position = rectangle->getPosition();
        drawer.rotation = rectangle->getRotation();
        drawer.draw(screen, camera);
    }

private:
    RectangleBody* rectangle;
    RectangleDrawer drawer;
};


class CircleBodyDrawer: public BodyDrawer {
public:
    CircleBodyDrawer(CircleBody* body) {
        this->circle = body;
    }

    void draw(Screen* screen, Camera* camera) override {
        drawer.radius = circle->config.radius;
        this->drawer.position = circle->getPosition();
        this->drawer.rotation = circle->getRotation();
        this->drawer.draw(screen, camera);
    }

private:
    CircleBody* circle;
    CircleDrawer drawer;
};








#endif //BODYDRAWER_HPP
