//
// Created by sp on 06.04.2025.
//

#ifndef STATICRECTDRAWER_HPP
#define STATICRECTDRAWER_HPP

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Drawer.hpp"
#include "Screen.hpp"
#include "physics/RectanglePhysics.hpp"

class RectangleDrawer: public Drawer {
public:
    explicit RectangleDrawer(RectanglePhysics* static_rect);


    void draw(Screen* screen, Camera* camera) override;

private:
    RectanglePhysics* static_rect;
    sf::RectangleShape shape;
};



#endif //STATICRECTDRAWER_HPP
