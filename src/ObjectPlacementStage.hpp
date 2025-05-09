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
    ObjectPlacementStage(Level& level, Screen* screen, Camera* camera): level(level) {
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
        this->changeObject(this->index);
        this->moveObject();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            this->placeObject();
            pressed = true;
        } else {
            pressed = false;
        }

        this->draw(screen, camera);
    }

    void moveObject() {
        const auto objs = level.available_objects->getAvailableObjects();
        if (this->index >= 0 && this->index < objs.size()) {
            this->current_sprite.object->config["initial_position"] = this->world_pos;
            this->current_sprite.object->config["initial_rotation"] = this->rotation_radians;
            this->current_sprite.object->applyConfig();
        }
    }

    void placeObject() {
        if (pressed == true) {
            return;
        }
        const auto objs = level.available_objects->getAvailableObjects();
        if (this->index >= 0 && this->index < objs.size()) {
            this->level.available_objects->place(objs[this->index], this->world_pos, this->rotation_radians);
        }
        this->current_tag = "";
        this->index = -1;
    }

    void draw(Screen* screen, Camera* camera) {
        const auto objs = level.available_objects->getAvailableObjects();
        for (const auto sprite: this->level.available_objects->placed_objects) {
            sprite.drawer->draw(screen, camera);
        }
        if (this->index >= 0 && this->index < objs.size()) {
            this->current_sprite.drawer->draw(screen, camera);
        }
    }

    void changeObject(int index) {
        const auto objs = this->level.available_objects->getAvailableObjects();
        if (index < 0 || index >= objs.size()) {
            return;
        }
        const std::string& tag = objs[index];
        if (tag == this->current_tag) {
            return;
        }
        this->current_tag = tag;
        delete this->current_sprite.drawer;
        delete this->current_sprite.object;
        this->current_sprite = SimulationObjectFactory::createSimulationSprite(tag);
    }

private:
    bool pressed = false;
    int index = -1;

    std::string current_tag;
    SimulationSprite current_sprite {};

    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    Vector2D world_pos {0,0};
    float rotation_radians = 0;


    Level& level;
};



#endif //OBJECTPLACEMENTSTAGE_HPP
