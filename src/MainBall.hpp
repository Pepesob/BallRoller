#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class MainBall {

public:
    explicit MainBall(float x, float y, float radius) {
        this->x_m = x;
        this->y_m = y;
        this->radius_m = radius;
    }

    void setXY(float x, float y) {
        this->x_m = x;
        this->y_m = y;
    }


    [[nodiscard]] float getX() const {
        return this->x_m;
    }

    [[nodiscard]] float getY() const {
        return this->y_m;
    }

    [[nodiscard]] float getRadius() const {
        return this->radius_m;
    }

private:
    float x_m = 0;
    float y_m = 0;
    float radius_m = 0.1;
};

