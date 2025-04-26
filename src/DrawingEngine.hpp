//
// Created by sp on 26.04.2025.
//

#ifndef DRAWINGENGINE_HPP
#define DRAWINGENGINE_HPP

#include <vector>

#include "Camera.hpp"
#include "ObjectDrawer.hpp"
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



class DrawingEngine {
public:

    DrawingEngine() {
        this->camera = new Camera{-0, 0, 0.5f};
        this->screen = new Screen{720, 720};
    }

    void addDrawer(ObjectDrawer* drawer) {
        this->drawers.push_back(drawer);
    }

    void start() {
        if (this->started) {
            throw std::runtime_error("DrawingEngine already started");
        }
        this->screen->createWindow();
        this->started = true;
    }

    void stop() {
        if (!this->started) {
            throw std::runtime_error("DrawingEngine is not started");
        }
        this->screen->destroyWindow();
        this->started = false;
    }

    void draw() const {
        // TODO - window events should not be handled here, find a way to change that
        screen->handleWindowEvents();
        camera->setScreenRatio(static_cast<float>(screen->getWidth()) / static_cast<float>(screen->getHeight()));
        screen->getWindow()->clear();
        for (const auto o: this->drawers) {
            o->draw(this->screen, this->camera);
        }
        debug_lines(this->screen->getWindow());
        screen->getWindow()->display();
    }

    Camera* getCamera() {
        return camera;
    }

    Screen* getScreen() {
        return screen;
    }

private:
    std::vector<ObjectDrawer*> drawers;
    Camera* camera;
    Screen* screen;
    bool started = false;
};



#endif //DRAWINGENGINE_HPP
