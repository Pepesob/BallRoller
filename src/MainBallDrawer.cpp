//
// Created by sp on 06.04.2025.
//

#include "MainBallDrawer.hpp"

MainBallDrawer::MainBallDrawer(MainBall *main_ball, Screen *screen, Camera *camera) {
    this->main_ball = main_ball;
    this->screen = screen;
    this->camera = camera;

    this->shape.setFillColor(sf::Color::Red);
    this->shape.setRadius(
        this->main_ball->getRadius() * this->screen->getPixelScaleFactor() * this->camera->getZoom());
}

void MainBallDrawer::draw() {
    float radius = this->main_ball->getRadius();
    float x = this->main_ball->getX();
    float y = this->main_ball->getY();
    this->shape.setRadius(
        this->main_ball->getRadius() * this->screen->getPixelScaleFactor() * this->camera->getZoom());
    sf::Vector2f v = (this->screen->getScreenMatrix() * this->camera->getCameraMatrix()).transformPoint({
        x - radius, y + radius
    });
    this->shape.setPosition(v);
    this->screen->getWindow()->draw(this->shape);
}
