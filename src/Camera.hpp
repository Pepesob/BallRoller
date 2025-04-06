//
// Created by sp on 02.04.2025.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>


class Camera {

public:
    // Currently camera window is 2m x 2m, transforms to coordinates (-1,1) x (-1,1)
    Camera(float x, float y, float zoom);

    sf::Transform& getCameraMatrix();
    void setPosition(float x, float y);
    void setScale(float zoom);
    void updateCameraMatrix();
    [[nodiscard]] float getZoom() const;

private:
    sf::Transform camera_matrix;

    float x;
    float y;
    float zoom;
    bool needs_update = true;
};



#endif //CAMERA_HPP
