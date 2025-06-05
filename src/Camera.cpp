#include "Camera.hpp"

#include <iostream>

Camera::Camera(float x, float y, float zoom, float screen_ratio): x(x), y(y), zoom(zoom), screen_ratio(screen_ratio), needs_update(true) {
}

sf::Transform & Camera::getCameraMatrix() {
    if (this->needs_update) {
        this->updateCameraMatrix();
    }
    return camera_matrix;
}

void Camera::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    this->validatePosition();
    this->needs_update = true;
}

Vector2D Camera::getPosition() {
    return {this->x, this->y};
}

void Camera::move(float x, float y) {
    this->x += x;
    this->y += y;
    this->validatePosition();
    this->needs_update = true;
}

void Camera::validatePosition() {
    this->x = std::min(this->x, this->max_x);
    this->x = std::max(this->x, this->min_x);

    this->y = std::min(this->y, this->max_y);
    this->y = std::max(this->y, this->min_y);
}

void Camera::validateZoom() {
    this->zoom = std::max(this->zoom, this->min_zoom);
    this->zoom = std::min(this->zoom, this->max_zoom);
}


void Camera::setScreenRatio(float ratio) {
    this->screen_ratio = ratio;
    this->needs_update = true;
}

void Camera::updateCameraMatrix() {
    camera_matrix = sf::Transform::Identity;
    camera_matrix.translate({-this->x, -this->y});
    camera_matrix.scale({1/this->screen_ratio, 1});
    camera_matrix.scale({this->zoom, this->zoom});
    this->needs_update = false;
}

float Camera::getZoom() const {
    return zoom;
}

void Camera::setZoom(float zoom) {
    this->needs_update = true;
    this->zoom = zoom;
    this->validateZoom();
}

void Camera::setDeltaZoom(float deltaZoom) {
    this->needs_update = true;
    this->zoom *= deltaZoom;
    this->validateZoom();
}

void Camera::handleEvent(const std::optional<sf::Event> &event) {
    if (const auto e = event->getIf<sf::Event::Resized>()) {
        this->setScreenRatio(static_cast<float>(e->size.x) / static_cast<float>(e->size.y));
    }
}
