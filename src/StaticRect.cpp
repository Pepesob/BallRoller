//
// Created by sp on 04.04.2025.
//

#include "StaticRect.hpp"

StaticRect::StaticRect(float x, float y, float w, float h, float rot) {
    // Screen drawing init
    this->x_m = x;
    this->y_m = y;
    this->w_m = w;
    this->h_m = h;
    this->rot_rad = rot;
}

float StaticRect::getX() const {
    return x_m;
}

float StaticRect::getY() const {
    return y_m;
}

float StaticRect::getW() const {
    return w_m;
}

float StaticRect::getH() const {
    return h_m;
}

float StaticRect::getRotation() const {
    return this->rot_rad;
}
