//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECT_HPP
#define STATICRECT_HPP
#include <iostream>

#include "SFML/Graphics.hpp"


class StaticRect {
public:
    StaticRect(float x, float y, float w, float h, float psf){
        // Screen drawing init
        this->x_m = x;
        this->y_m = y;
        this->w_m = w;
        this->h_m = h;
        this->pixel_scale_factor = psf;
        this->shape.setSize({this->w_m*psf, this->h_m*psf});
        // this->shape.setOrigin({this->w_m / 2, this->h_m / 2});
        this->shape.setPosition({this->x_m, this->y_m});

        this->shape.setFillColor(sf::Color(222,184,135));
        // this->shape.setScale({this->pixel_scale_factor, this->pixel_scale_factor});
    }

    void updateShape() {
        this->shape.setSize({this->w_m*this->pixel_scale_factor*this->zoom, this->h_m*this->pixel_scale_factor*this->zoom});
    }

    void draw(sf::RenderWindow& window, sf::Transform& transform) {
        sf::Vector2f v = transform.transformPoint({this->x_m - this->w_m/2, this->y_m + this->h_m/2});
        this->shape.setPosition(v);
        // // std::cout << v.x << " " << v.y << std::endl;
        // std::cout << "Static rect points" << std::endl;
        // for (int i=0; i<4; i++) {
        //     std::cout << this->shape.getPoint(i).x << " " << this->shape.getPoint(i).y << std::endl;
        // }
        window.draw(shape);
    }

    float getX() const {
        return x_m;
    }

    float getY() const {
        return y_m;
    }

    float getW() const {
        return w_m;
    }

    float getH() const {
        return h_m;
    }

    void setZoom(float zoom) {
        this->zoom = zoom;
        this->updateShape();
    }

private:
    float x_m, y_m, w_m, h_m;
    float zoom = 1;
    float pixel_scale_factor = 720;
    sf::RectangleShape shape;
};



#endif //STATICRECT_HPP
