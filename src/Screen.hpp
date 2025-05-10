#pragma once


#include <SFML/Graphics.hpp>

void debug_lines(sf::RenderWindow* window);


class Screen {
public:
    Screen(unsigned int width, unsigned int height);
    ~Screen();
    void createWindow();
    void destroyWindow();
    void handleWindowEvents();
    sf::Transform& getScreenMatrix();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void updateScreenMatrix();
    void setSize(unsigned int width, unsigned int height);
    [[nodiscard]] int getPixelScaleFactor() const;
    [[nodiscard]] sf::RenderWindow* getWindow() const;
    [[nodiscard]] bool isWindowOpen() const;

private:
    sf::Transform screen_matrix;
    sf::RenderWindow* window = nullptr;
    unsigned int width, height;
    std::string window_name;
    int pixel_scale_factor;
    bool needs_update;
};
