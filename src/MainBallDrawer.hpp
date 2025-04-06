//
// Created by sp on 06.04.2025.
//

#ifndef MAINBALLDRAWER_HPP
#define MAINBALLDRAWER_HPP
#include "MainBall.hpp"


class MainBallDrawer {
public:
    MainBallDrawer(MainBall* main_ball, float psf, float zoom=1) {
        this->main_ball = main_ball;
        this->zoom = zoom;
        this->pixel_scale_factor = psf;
        this->shape.setFillColor(sf::Color::Red);
        this->shape.setRadius(this->main_ball->getRadius() * this->pixel_scale_factor * this->zoom);
    }


    void draw(sf::RenderWindow& window, sf::Transform& transform) {
        float radius = this->main_ball->getRadius();
        float x = this->main_ball->getX();
        float y = this->main_ball->getY();
        this->shape.setRadius(this->main_ball->getRadius() * this->pixel_scale_factor * this->zoom);
        sf::Vector2f v = transform.transformPoint({x-radius, y+radius});
        this->shape.setPosition(v);
        window.draw(shape);
    }


private:
    MainBall* main_ball;
    sf::CircleShape shape;
    float pixel_scale_factor = 720;
    float zoom = 1;
};



#endif //MAINBALLDRAWER_HPP
