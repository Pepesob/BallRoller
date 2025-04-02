//
// Created by sp on 02.04.2025.
//

#ifndef SCREEN_HPP
#define SCREEN_HPP
#include "SFML/Graphics.hpp"


class Screen {
public:
    Screen(int width, int height) {
        this->width = width;
        this->height = height;
        this->needs_update = true;
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

    void setSize(int width, int height) {
        this->width = width;
        this->height = height;
        needs_update = true;
    }


private:
    sf::Transform screen_matrix;
    int width, height;
    bool needs_update;
};



#endif //SCREEN_HPP
