#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class MainBall {

private:
    sf::CircleShape shape;
    float x_m = 0;
    float y_m = 1;
    float radius_m = 0.1;
    float pixel_scale_factor = 720;

    // Set shape radius in meters and then scale it by appropriate factor, this will ensure modularity and easy changable
public:
    explicit MainBall(float psf) {
        // Screen drawing init
        this->pixel_scale_factor = psf;
        this->shape.setRadius(this->radius_m);
        this->shape.setFillColor(sf::Color::Red);
        this->shape.setPosition({this->x_m, this->y_m});
        this->shape.setOrigin({this->radius_m, this->radius_m});
        this->shape.setScale({this->pixel_scale_factor, this->pixel_scale_factor});
    }

    void setXY(float x, float y) {
        this->x_m = x;
        this->y_m = y;
    }

    void setPixelScaleFactor(float s) {
        this->pixel_scale_factor = s;
    }


    float getX() {
        return this->x_m;
    }

    float getY() {
        return this->y_m;
    }

    float getRatius() {
        return this->radius_m;
    }

    void draw(sf::RenderWindow& window, sf::Transform& transform) {
        sf::Vector2f v = transform.transformPoint({this->x_m, this->y_m});
        this->shape.setPosition(v);
        window.draw(shape);
    }

};

