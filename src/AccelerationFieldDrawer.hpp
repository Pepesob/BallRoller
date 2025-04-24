//
// Created by sp on 24.04.2025.
//

#ifndef ACCELERATIONFIELDDRAWER_HPP
#define ACCELERATIONFIELDDRAWER_HPP
#include "AccelerationField.hpp"
#include "Camera.hpp"
#include "Screen.hpp"


class AccelerationFieldDrawer {
public:
    AccelerationFieldDrawer(AccelerationField* static_rect, Screen* screen, Camera* camera) {
        this->acceleration_field = static_rect;
        this->screen = screen;
        this->camera = camera;
        this->shape.setFillColor(sf::Color(255,0,128, 80));
    }


    void draw() {
        float x = this->acceleration_field->getX();
        float y = this->acceleration_field->getY();
        float w = this->acceleration_field->getWidth();
        float h = this->acceleration_field->getHeight();
        float zoom = this->camera->getZoom();
        float psf = this->screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2, h*psf*zoom/2});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-this->acceleration_field->getRotation()));
        sf::Vector2f v = (this->screen->getScreenMatrix() * this->camera->getCameraMatrix()).transformPoint({x, y});
        this->shape.setPosition(v);
        this->screen->getWindow()->draw(shape);
    }

private:
    sf::RectangleShape shape;
    AccelerationField* acceleration_field;
    Screen* screen;
    Camera* camera;
};



#endif //ACCELERATIONFIELDDRAWER_HPP
