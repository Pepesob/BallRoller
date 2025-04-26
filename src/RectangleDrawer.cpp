//
// Created by sp on 06.04.2025.
//

#include "RectangleDrawer.hpp"

RectangleDrawer::RectangleDrawer(RectanglePhysics *static_rect) {
    this->static_rect = static_rect;
    this->config = {};
    this->shape.setFillColor(sf::Color(222,184,135));
}

RectangleDrawer::RectangleDrawer(RectanglePhysicsConfig* config) {
    this->config = config;
    this->static_rect = nullptr;
}

void RectangleDrawer::draw(Screen* screen, Camera* camera) {
    if (this->static_rect == nullptr) {
        auto [x, y] = this->config->position;
        auto [w, h] = this->config->size;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-this->config->rotation));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        std::cout << v.x << ", " << v.y << std::endl;
        this->shape.setPosition(v);
        screen->getWindow()->draw(shape);
        return;
    }
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
