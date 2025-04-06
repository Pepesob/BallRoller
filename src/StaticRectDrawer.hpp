//
// Created by sp on 06.04.2025.
//

#ifndef STATICRECTDRAWER_HPP
#define STATICRECTDRAWER_HPP

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Screen.hpp"
#include "StaticRect.hpp"

class StaticRectDrawer {
public:
    StaticRectDrawer(StaticRect* static_rect, Screen* screen, Camera* camera) {
        this->static_rect = static_rect;
        this->screen = screen;
        this->camera = camera;
        this->shape.setFillColor(sf::Color(222,184,135));
    }

    void draw() {
        float x = this->static_rect->getX();
        float y = this->static_rect->getY();
        float w = this->static_rect->getW();
        float h = this->static_rect->getH();
        float zoom = this->camera->getZoom();
        float psf = this->screen->getPixelScaleFactor();
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        sf::Vector2f v = (this->screen->getScreenMatrix() * this->camera->getCameraMatrix()).transformPoint({x - w/2, y + h/2});
        this->shape.setPosition(v);
        this->screen->getWindow()->draw(shape);
    }
private:
    sf::RectangleShape shape;
    StaticRect* static_rect;
    Screen* screen;
    Camera* camera;
};



#endif //STATICRECTDRAWER_HPP
