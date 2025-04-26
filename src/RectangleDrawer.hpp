//
// Created by sp on 06.04.2025.
//

#ifndef STATICRECTDRAWER_HPP
#define STATICRECTDRAWER_HPP

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "ObjectDrawer.hpp"
#include "Screen.hpp"
#include "physics/RectanglePhysics.hpp"

class RectangleDrawer: public ObjectDrawer {
public:
    explicit RectangleDrawer(RectanglePhysics* static_rect);

    void draw(Screen* screen, Camera* camera) override;

private:
    RectanglePhysics* static_rect;
    sf::RectangleShape shape;
};



#endif //STATICRECTDRAWER_HPP
