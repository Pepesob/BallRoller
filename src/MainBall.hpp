#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class MainBall {

public:
    MainBall(float x, float y, float radius);

    void setXY(float x, float y);
    void setX(float x);
    void setY(float y);
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getRadius() const;

private:
    float x_m;
    float y_m;
    float radius_m;
};

