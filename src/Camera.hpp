//
// Created by sp on 02.04.2025.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>


class Camera {
public:
    // Currently camera window is 2m x 2m, transforms to coordinates (-1,1) x (-1,1)
    Camera(float x, float y, float zoom, float screen_ratio = 1);

    sf::Transform &getCameraMatrix();
    void setPosition(float x, float y);
    void move(float x, float y) {
        this->x += x;
        this->y += y;
    }
    void setScale(float zoom);
    void setScreenRatio(float ratio);
    void updateCameraMatrix();
    [[nodiscard]] float getZoom() const;

private:
    sf::Transform camera_matrix;

    float x;
    float y;
    float zoom;
    float screen_ratio;
    bool needs_update;
};


#endif //CAMERA_HPP
