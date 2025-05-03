//
// Created by sp on 26.04.2025.
//

#ifndef DRAWINGENGINE_HPP
#define DRAWINGENGINE_HPP

#include <vector>

#include "Camera.hpp"
#include "Drawer.hpp"
#include "Screen.hpp"

void debug_lines(sf::RenderWindow* window) {
    // Calculate 10% of window dimensions
    float cellWidth = window->getSize().x * 0.05f;
    float cellHeight = window->getSize().y * 0.05f;


    sf::Vertex line[2];
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    // Draw vertical lines
    for (float x = cellWidth; x < window->getSize().x; x += cellWidth)
    {
        line[0].position = sf::Vector2f(x, 0);
        line[1].position = sf::Vector2f(x, window->getSize().y);
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Draw horizontal lines
    for (float y = cellHeight; y < window->getSize().y; y += cellHeight)
    {
        line[0].position = sf::Vector2f(0, y);
        line[1].position = sf::Vector2f(window->getSize().x, y);
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Create a red dot at the center of the screen
    sf::CircleShape redDot(5); // Radius 10
    redDot.setFillColor(sf::Color::Cyan);

    // Position the dot at the center of the window
    redDot.setPosition({window->getSize().x / 2 - redDot.getRadius(), window->getSize().y / 2 - redDot.getRadius()});

    // Draw the red dot
    window->draw(redDot);
}

//
//
// class DrawingEngine {
// public:
//     void addDrawer(Drawer* drawer) {
//         this->drawers.push_back(drawer);
//     }
//
//     void addDrawer(SimulationObjectDrawer* drawer) {
//         this->addDrawer(new SimulationObjectDrawerWrapper(drawer));
//     }
//
//     void draw(Screen* screen, Camera* camera) const {
//
//         for (const auto o: this->drawers) {
//             o->draw(screen, camera);
//         }
//         debug_lines(screen->getWindow());
//
//     }
//
// private:
//     class SimulationObjectDrawerWrapper: public Drawer {
//     public:
//         explicit SimulationObjectDrawerWrapper(SimulationObjectDrawer* drawer) {
//             this->drawer = drawer;
//         }
//
//         void draw(Screen *screen, Camera *camera) override {
//             this->drawer->drawSimulation(screen, camera);
//         }
//     private:
//         SimulationObjectDrawer* drawer;
//     };
//     std::vector<Drawer*> drawers;
// };



#endif //DRAWINGENGINE_HPP
