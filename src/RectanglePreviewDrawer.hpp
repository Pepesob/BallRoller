//
// Created by sp on 27.04.2025.
//

#ifndef RECTANGLEPREVIEWDRAWER_HPP
#define RECTANGLEPREVIEWDRAWER_HPP
#include "ObjectPreviewDrawer.hpp"
#include "physics/RectanglePhysics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"


class RectanglePreviewDrawer: public ObjectPreviewDrawer {
public:
    explicit RectanglePreviewDrawer(const RectanglePhysicsConfig& config) {
        this->config = config;
    }

    void draw(Screen *screen, Camera *camera) override {
        auto [x, y] = this->position;
        auto [w, h] = this->config.size;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-this->rotation));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(shape);
    }
private:
    RectanglePhysicsConfig config;
    sf::RectangleShape shape;
};



#endif //RECTANGLEPREVIEWDRAWER_HPP
