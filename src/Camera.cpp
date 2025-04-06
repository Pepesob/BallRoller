//
// Created by sp on 02.04.2025.
//

#include "Camera.hpp"

Camera::Camera(float x, float y, float zoom): x(x), y(y) {
    this->x = x;
    this->y = y;
    this->zoom = zoom;
    this->needs_update = true;
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
    this->needs_update = true;
}

void Camera::setScale(float zoom) {
    this->zoom = zoom;
    this->needs_update = true;
}

void Camera::updateCameraMatrix() {
    camera_matrix = sf::Transform::Identity;
    camera_matrix.translate({-this->x, -this->y});
    camera_matrix.scale({this->zoom, this->zoom});
    this->needs_update = false;
}

float Camera::getZoom() const {
    return zoom;
}
