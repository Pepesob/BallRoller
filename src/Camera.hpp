#pragma once

#include <SFML/Graphics.hpp>

#include "common.hpp"


class Camera {
public:
    // Currently camera window is 2m x 2m, transforms to coordinates (-1,1) x (-1,1)
    Camera(float x, float y, float zoom, float screen_ratio = 1);

    sf::Transform &getCameraMatrix();
    void setPosition(float x, float y);
    Vector2D getPosition();
    void move(float x, float y);
    void setScreenRatio(float ratio);
    void updateCameraMatrix();
    [[nodiscard]] float getZoom() const;
    void setZoom(float zoom);
    void setDeltaZoom(float deltaZoom);

    void handleEvent(const std::optional<sf::Event> &event);

private:
    void validatePosition();
    void validateZoom();

    sf::Transform camera_matrix;

    float x;
    float y;
    float zoom;
    float screen_ratio;
    bool needs_update;

    float max_x = 2;
    float max_y = 2;

    float min_x = -2;
    float min_y = -2;

    float min_zoom = 0.1;
    float max_zoom = 2;

    sf::Vector2i prev_mouse_pos;
};



