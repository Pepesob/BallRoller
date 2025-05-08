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
    ObjectPlacementStage(AvailableLevelObjects& available_objects, Screen* screen, Camera* camera) {
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
        this->moveObject();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            this->placeObject();
        } else {
            pressed = false;
        }

        this->draw(screen, camera);
    }

    void moveObject() {
        if (this->index >= 0 && this->index < av.available_object_tags.size()) {
            av.move(this->index, this->world_pos, this->rotation_radians);
        }
    }

    void placeObject() {
        if (pressed == true) {
            return;
        }
        if (this->index >= 0 && this->index < av.available_object_tags.size()) {
            this->av.move(this->index, this->world_pos, this->rotation_radians);
            this->av.place(this->index);
            pressed = true;
        }
        this->index = -1;
    }

    void draw(Screen* screen, Camera* camera) {
        for (const auto sprite: this->av.placed_sprites) {
            sprite->drawer->draw(screen, camera);
        }
        if (this->index >= 0 && this->index < av.available_object_tags.size()) {
            this->av.available_sprites[this->index].drawer->draw(screen, camera);
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

    AvLvlObj av;
    // AvailableLevelObjects& available_objects;
};



#endif //OBJECTPLACEMENTSTAGE_HPP
