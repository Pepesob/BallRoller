//
// Created by sp on 02.04.2025.
//

#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include <stdexcept>
#include <stdlib.h>


class Screen {
public:
    Screen(unsigned int width, unsigned int height, int psf) {
        this->width = width;
        this->height = height;
        this->window = nullptr;
        this->pixel_scale_factor = psf;
        this->needs_update = true;
        this->window_name = "BallRoller";
    }

    ~Screen() {
        delete this->window;
    }

    void createWindow() {
        if (this->window == nullptr) {
            this->window = new sf::RenderWindow();
            this->window->create(sf::VideoMode({this->width, this->height}), this->window_name);
        }
        else {
            throw std::runtime_error("Window already exists");
        }
    }

    void destroyWindow() {
        if (this->window != nullptr) {
            this->window->close();
            delete this->window;
            this->window = nullptr;
        }
        else {
            throw std::runtime_error("Window does not exist");
        }
    }

    void handleWindowEvents() {
        if (this->window == nullptr) {
            throw std::runtime_error("Window does not exist");
        }
        while (const std::optional event = this->window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                this->destroyWindow();
            }
        }
    }

    sf::Transform& getScreenMatrix() {
        if (this->needs_update) {
            this->updateScreenMatrix();
        }
        return this->screen_matrix;
    }

    void updateScreenMatrix() {
        float w = this->width;
        float h = this->height;
        this->screen_matrix = sf::Transform(
            w / 2.f, 0, w/ 2.f,
            0, -h / 2.f, h / 2.f,
            0, 0, 1
            );
        needs_update = false;
    }

    void setSize(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
        if (this->window != nullptr) {
            this->window->setSize({this->width, this->height});
        }
        needs_update = true;
    }

    [[nodiscard]] int getPixelScaleFactor() const {
        return this->pixel_scale_factor;
    }

    [[nodiscard]] sf::RenderWindow* getWindow() const {
        return this->window;
    }

    bool isWindowOpen() const {
        return this->window != nullptr;
    }


private:
    sf::Transform screen_matrix;
    sf::RenderWindow* window = nullptr;
    unsigned int width, height;
    std::string window_name;
    int pixel_scale_factor;
    bool needs_update;
};



#endif //SCREEN_HPP
