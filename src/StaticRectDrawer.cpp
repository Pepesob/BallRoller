//
// Created by sp on 06.04.2025.
//

#include "StaticRectDrawer.hpp"

#include <iostream>

#include "Box2d/box2d.h"

StaticRectDrawer::StaticRectDrawer(StaticRect *static_rect, Screen *screen, Camera *camera) {
    this->static_rect = static_rect;
    this->screen = screen;
    this->camera = camera;
    this->shape.setFillColor(sf::Color(222,184,135));
}

void StaticRectDrawer::draw() {
    float x = this->static_rect->getX();
    float y = this->static_rect->getY();
    float w = this->static_rect->getW();
    float h = this->static_rect->getH();
    float zoom = this->camera->getZoom();
    float psf = this->screen->getPixelScaleFactor();
    this->shape.setOrigin({w*psf*zoom/2, h*psf*zoom/2});
    this->shape.setSize({w*psf*zoom, h*psf*zoom});
    this->shape.setRotation(sf::radians(-this->static_rect->getRotation()));
    sf::Vector2f v = (this->screen->getScreenMatrix() * this->camera->getCameraMatrix()).transformPoint({x, y});
    this->shape.setPosition(v);
    this->screen->getWindow()->draw(shape);
}
