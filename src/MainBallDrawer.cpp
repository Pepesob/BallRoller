//
// Created by sp on 06.04.2025.
//

#include "MainBallDrawer.hpp"

MainBallDrawer::MainBallDrawer(MainBallPhysics *main_ball) {
    this->main_ball = main_ball;

    this->shape.setFillColor(sf::Color::Red);
}

void MainBallDrawer::draw(Screen* screen, Camera* camera) {
    float radius = this->main_ball->getRadius();
    auto [x, y] = this->main_ball->getPosition();
    this->shape.setRadius(
        this->main_ball->getRadius() * screen->getPixelScaleFactor() * camera->getZoom());
    sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({
        x - radius, y + radius
    });
    this->shape.setPosition(v);
    screen->getWindow()->draw(this->shape);
}
