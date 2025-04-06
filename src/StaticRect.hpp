//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECT_HPP
#define STATICRECT_HPP
#include <iostream>

#include "SFML/Graphics.hpp"


class StaticRect {
public:
    StaticRect(float x, float y, float w, float h){
        // Screen drawing init
        this->x_m = x;
        this->y_m = y;
        this->w_m = w;
        this->h_m = h;
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

private:
    float x_m, y_m, w_m, h_m;
};



#endif //STATICRECT_HPP
