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
            this->index = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            this->index = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            this->index = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
            this->index = 3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
            this->index = 4;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
            this->index = 5;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) {
            this->index = 6;
        }
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        //     sf::Transform t = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse();
        //     sf::Vector2f current = t.transformPoint(sf::Vector2f(sf::Mouse::getPosition(*this->screen->getWindow())));
        //     sf::Vector2f prev = t.transformPoint(sf::Vector2f(this->mouse_pos));
        //     sf::Vector2f dx = prev - current;
        //     // this->camera->move(dx.x, dx.y);
        // }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            this->camera->setDeltaZoom(0.999);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            this->camera->setDeltaZoom(1.001);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            this->rotation_radians += 0.001;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            this->rotation_radians -= 0.001;
        }
        if (this->available_objects.isPlaced(this->index) || this->index < 0 || this->index >= this->available_objects.size()) {
            this->index = -1;
        }
        this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());
        sf::Vector2f wp = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        this->world_pos = {wp.x, wp.y};
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (pressed == true || this->index == -1) {
                return;
            }
            this->placeObject(simulation);
            std::cout << this->index << std::endl;
            pressed = true;
        } else {
            pressed = false;
        }
    }

    void placeObject(B2dSimulation& simulation) {
        this->available_objects.objects[this->index]->setInitialPosition(this->world_pos);
        this->available_objects.place(simulation, this->index);
    }

    void draw(Screen* screen, Camera* camera) {
        if (this->index != -1) {
            this->available_objects.objects[this->index]->setInitialPosition(this->world_pos);
            this->available_objects.objects[this->index]->setInitialRotation(this->rotation_radians);
            this->available_objects.objects[this->index]->drawPreview(screen, camera);
        }
    }

private:
    bool pressed = false;
    int index = -1;

    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    Vector2D world_pos {0,0};
    float rotation_radians = 0;

    AvailableLevelObjects& available_objects;
};



#endif //OBJECTPLACEMENTSTAGE_HPP
