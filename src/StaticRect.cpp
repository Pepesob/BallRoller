//
// Created by sp on 04.04.2025.
//

#include "StaticRect.hpp"

StaticRect::StaticRect(float x, float y, float w, float h) {
    // Screen drawing init
    this->x_m = x;
    this->y_m = y;
    this->w_m = w;
    this->h_m = h;
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
