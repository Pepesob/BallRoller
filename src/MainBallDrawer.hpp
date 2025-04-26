//
// Created by sp on 06.04.2025.
//

#ifndef MAINBALLDRAWER_HPP
#define MAINBALLDRAWER_HPP

#include "Camera.hpp"
#include "ObjectDrawer.hpp"
#include "Screen.hpp"
#include "physics/MainBallPhysics.hpp"


class MainBallDrawer: public ObjectDrawer {
public:
    explicit MainBallDrawer(MainBallPhysics* main_ball);

    void draw(Screen *screen, Camera *camera) override;

private:
    MainBallPhysics *main_ball;
    sf::CircleShape shape;
};


#endif //MAINBALLDRAWER_HPP
