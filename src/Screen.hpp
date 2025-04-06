//
// Created by sp on 02.04.2025.
//

#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics/RenderWindow.hpp>


class Screen {
public:
    Screen(unsigned int width, unsigned int height, int psf);

    ~Screen();

    void createWindow();
    void destroyWindow();
    void handleWindowEvents();
    sf::Transform& getScreenMatrix();
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



#endif //SCREEN_HPP
