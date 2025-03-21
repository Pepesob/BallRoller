#pragma once

#include <SFML/Window.hpp>

class Screen {
private:
    sf::Window window = sf::Window(sf::VideoMode({800, 600}), "My window");

public:
    bool isOpen() {
        return this->window.isOpen();
    }

    void serveWindowEvents() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
};

