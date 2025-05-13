#pragma once

#include <SFML/Graphics.hpp>


class Camera {
public:
    // Currently camera window is 2m x 2m, transforms to coordinates (-1,1) x (-1,1)
    Camera(float x, float y, float zoom, float screen_ratio = 1);

    sf::Transform &getCameraMatrix();
    void setPosition(float x, float y);
    void move(float x, float y);
    void setScreenRatio(float ratio);
    void updateCameraMatrix();
    [[nodiscard]] float getZoom() const;
    void setZoom(float zoom);
    void setDeltaZoom(float deltaZoom);

    void handleEvent(const std::optional<sf::Event> &event);

private:
    sf::Transform camera_matrix;

    float x;
    float y;
    float zoom;
    float screen_ratio;
    bool needs_update;

    sf::Vector2i prev_mouse_pos;
};

