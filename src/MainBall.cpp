
#include "MainBall.hpp"

MainBall::MainBall(float x, float y, float radius) {
    this->x_m = x;
    this->y_m = y;
    this->radius_m = radius;
}

void MainBall::setXY(float x, float y) {
    this->x_m = x;
    this->y_m = y;
}

void MainBall::setX(float x) {
    this->x_m = x;
}

void MainBall::setY(float y) {
    this->y_m = y;
}

float MainBall::getX() const {
    return this->x_m;
}

float MainBall::getY() const {
    return this->y_m;
}

float MainBall::getRadius() const {
    return this->radius_m;
}
