//
// Created by sp on 02.04.2025.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>


class Camera {

public:
    // Currently camera window is 2m x 2m, transforms to coordinates (-1,1) x (-1,1)
    Camera(float x, float y, float zoom): x(x), y(y) {
        this->x = x;
        this->y = y;
        this->zoom = zoom;
        this->needs_update = true;
    }

    sf::Transform& getCameraMatrix() {
        if (this->needs_update) {
            this->updateCameraMatrix();
        }
        return camera_matrix;
    }

    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
        this->needs_update = true;
    }

    void setScale(float zoom) {
        this->zoom = zoom;
        this->needs_update = true;
    }

    void updateCameraMatrix() {
        camera_matrix = sf::Transform::Identity;
        camera_matrix.translate({this->x, this->y});
        camera_matrix.scale({this->zoom, this->zoom});
        this->needs_update = false;
    }


private:
    sf::Transform camera_matrix;

    float x;
    float y;
    float zoom;
    bool needs_update = true;
};



#endif //CAMERA_HPP
