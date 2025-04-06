//
// Created by sp on 06.04.2025.
//

#ifndef STATICRECTDRAWER_HPP
#define STATICRECTDRAWER_HPP

#include <SFML/Graphics.hpp>

#include "StaticRect.hpp"

class StaticRectDrawer {
public:
    StaticRectDrawer(StaticRect* static_rect, float psf, float zoom=1) {
        this->static_rect = static_rect;
        this->pixel_scale_factor = psf;
        this->zoom = zoom;
        this->shape.setFillColor(sf::Color(222,184,135));
    }

    void draw(sf::RenderWindow& window, sf::Transform& transform) {
        float x = this->static_rect->getX();
        float y = this->static_rect->getY();
        float w = this->static_rect->getW();
        float h = this->static_rect->getH();
        this->shape.setSize({w*this->pixel_scale_factor*this->zoom, h*this->pixel_scale_factor*this->zoom});
        sf::Vector2f v = transform.transformPoint({x - w/2, y + h/2});
        this->shape.setPosition(v);
        window.draw(shape);
    }
private:
    sf::RectangleShape shape;
    StaticRect* static_rect;
    float pixel_scale_factor;
    float zoom;
};



#endif //STATICRECTDRAWER_HPP
