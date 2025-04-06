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
    StaticRectDrawer(StaticRect* static_rect, Screen* screen, Camera* camera);

    void draw();

private:
    sf::RectangleShape shape;
    StaticRect* static_rect;
    Screen* screen;
    Camera* camera;
};



#endif //STATICRECTDRAWER_HPP
