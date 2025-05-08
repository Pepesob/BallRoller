//
// Created by sp on 26.04.2025.
//

#ifndef OBJECTPLACEMENTSTAGE_HPP
#define OBJECTPLACEMENTSTAGE_HPP
#include <iostream>
#include "DrawingEngine.hpp"
#include "AvailableLevelObjects.hpp"
#include "Level.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "simulation/objects/AcceleratorObject.hpp"



class ObjectPlacementStage {

public:
    ObjectPlacementStage(AvailableLevelObjects& available_objects, Screen* screen, Camera* camera): available_objects(available_objects) {
        this->screen = screen;
        this->camera = camera;
    }

    void keyboardInput(B2dSimulation& simulation) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            this->available_objects.select(0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            this->available_objects.select(1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            this->available_objects.select(2);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
            this->available_objects.select(3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
            this->available_objects.select(4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
            this->available_objects.select(5);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) {
            this->available_objects.select(6);
        }
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        //     this->camera->setDeltaZoom(0.999);
        // }
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        //     this->camera->setDeltaZoom(1.001);
        // }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            this->rotation_radians += 0.001;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            this->rotation_radians -= 0.001;
        }
        this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());
        sf::Vector2f wp = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        this->world_pos = {wp.x, wp.y};
        this->available_objects.set(this->world_pos, this->rotation_radians);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (pressed == true) {
                return;
            }
            this->placeObject();
            pressed = true;
        } else {
            pressed = false;
        }
    }

    void placeObject() {
        this->available_objects.place(this->world_pos, this->rotation_radians);
    }

private:
    bool pressed = false;

    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    Vector2D world_pos {0,0};
    float rotation_radians = 0;

    AvailableLevelObjects& available_objects;
};



#endif //OBJECTPLACEMENTSTAGE_HPP
