//
// Created by sp on 02.04.2025.
//

#include "Screen.hpp"

Screen::Screen(unsigned int width, unsigned int height, int psf) {
    this->width = width;
    this->height = height;
    this->window = nullptr;
    this->pixel_scale_factor = psf;
    this->needs_update = true;
    this->window_name = "BallRoller";
}

Screen::~Screen() {
    delete this->window;
}

void Screen::createWindow() {
    if (this->window == nullptr) {
        this->window = new sf::RenderWindow();
        this->window->create(sf::VideoMode({this->width, this->height}), this->window_name);
    }
    else {
        throw std::runtime_error("Window already exists");
    }
}

void Screen::destroyWindow() {
    if (this->window != nullptr) {
        this->window->close();
        delete this->window;
        this->window = nullptr;
    }
    else {
        throw std::runtime_error("Window does not exist");
    }
}

void Screen::handleWindowEvents() {
    if (this->window == nullptr) {
        throw std::runtime_error("Window does not exist");
    }
    while (const std::optional event = this->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->destroyWindow();
        }
    }
}

sf::Transform & Screen::getScreenMatrix() {
    if (this->needs_update) {
        this->updateScreenMatrix();
    }
    return this->screen_matrix;
}

void Screen::updateScreenMatrix() {
    float w = this->width;
    float h = this->height;
    this->screen_matrix = sf::Transform(
        w / 2.f, 0, w/ 2.f,
        0, -h / 2.f, h / 2.f,
        0, 0, 1
    );
    needs_update = false;
}

void Screen::setSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    if (this->window != nullptr) {
        this->window->setSize({this->width, this->height});
    }
    needs_update = true;
}

int Screen::getPixelScaleFactor() const {
    return this->pixel_scale_factor;
}

sf::RenderWindow * Screen::getWindow() const {
    return this->window;
}

bool Screen::isWindowOpen() const {
    return this->window != nullptr;
}
