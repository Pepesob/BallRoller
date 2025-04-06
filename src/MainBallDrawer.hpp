//
// Created by sp on 06.04.2025.
//

#ifndef MAINBALLDRAWER_HPP
#define MAINBALLDRAWER_HPP

#include "Camera.hpp"
#include "MainBall.hpp"
#include "Screen.hpp"


class MainBallDrawer {
public:
    MainBallDrawer(MainBall *main_ball, Screen *screen, Camera *camera);
    void draw();

private:
    MainBall *main_ball;
    Screen *screen;
    Camera *camera;
    sf::CircleShape shape;
};


#endif //MAINBALLDRAWER_HPP
