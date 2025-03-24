#include "Gameloop.hpp"

#include <SFML/Graphics.hpp>


void gameloop() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }
}