#include "BodyDrawer.hpp"

#include "Screen.hpp"
#include "Camera.hpp"

void RectangleDrawer::draw(Screen *screen, Camera *camera) {
    auto [w, h] = this->size;
    auto [x,y] = this->position;
    float zoom = camera->getZoom();
    int psf = screen->getPixelScaleFactor();
    this->shape.setTexture(&texture);
    this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
    this->shape.setSize({w*psf*zoom, h*psf*zoom});
    this->shape.setRotation(sf::radians(-this->rotation));
    sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
    this->shape.setPosition(v);
    screen->getWindow()->draw(this->shape);
}

void CircleDrawer::draw(Screen *screen, Camera *camera) {
    auto [x, y] = this->position;
    float psf = screen->getPixelScaleFactor();
    circle.setOrigin({radius*psf*camera->getZoom(), radius*psf*camera->getZoom()});
    circle.setRadius(radius * psf * camera->getZoom());
    circle.setRotation(sf::radians(-this->rotation));
    sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
    circle.setPosition(v);
    circle.setTexture(&this->texture);
    screen->getWindow()->draw(circle);
}

RectangleBodyDrawer::RectangleBodyDrawer(RectangleBody *body) {
    this->rectangle = body;
}

void RectangleBodyDrawer::draw(Screen *screen, Camera *camera) {
    this->drawer.size = rectangle->config.size;
    drawer.position = rectangle->getPosition();
    drawer.rotation = rectangle->getRotation();
    drawer.draw(screen, camera);
}

CircleBodyDrawer::CircleBodyDrawer(CircleBody *body) {
    this->circle = body;
}

void CircleBodyDrawer::draw(Screen *screen, Camera *camera) {
    drawer.radius = circle->config.radius;
    this->drawer.position = circle->getPosition();
    this->drawer.rotation = circle->getRotation();
    this->drawer.draw(screen, camera);
}

