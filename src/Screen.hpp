#pragma once


#include <SFML/Graphics.hpp>

#include "Camera.hpp"

void debug_lines(sf::RenderWindow* window);


class Screen {
public:
    Screen(unsigned int width, unsigned int height);
    ~Screen();
    void createWindow();
    void destroyWindow();
    void handleWindowEvents();
    void handleEvent(const std::optional<sf::Event> &event);

    sf::Transform& getScreenMatrix();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void updateScreenMatrix();
    void setSize(unsigned int width, unsigned int height);
    [[nodiscard]] int getPixelScaleFactor() const;
    [[nodiscard]] sf::RenderWindow* getWindow() const;
    [[nodiscard]] bool isWindowOpen() const;
    void draw(Screen* screen, Camera* camera);

private:
    sf::Transform screen_matrix;
    sf::Texture background_texture;
    sf::Sprite background;
    sf::RenderWindow* window = nullptr;
    unsigned int width, height;
    std::string window_name;
    int pixel_scale_factor;
    bool needs_update;
};
