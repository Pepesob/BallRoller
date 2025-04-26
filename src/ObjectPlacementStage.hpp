//
// Created by sp on 26.04.2025.
//

#ifndef OBJECTPLACEMENTSTAGE_HPP
#define OBJECTPLACEMENTSTAGE_HPP
#include "DrawingEngine.hpp"
#include "ObjectDrawer.hpp"
#include "RectangleDrawer.hpp"
#include "physics/ObjectPhysics.hpp"
#include "physics/PhysicsEngine.hpp"
#include "physics/RectanglePhysics.hpp"
#include "SFML/Window/Keyboard.hpp"


class ObjectPlacementStage {

public:
    ObjectPlacementStage(PhysicsEngine* physics_engine, DrawingEngine* drawing_engine, Screen* screen, Camera* camera) {
        this->physics_engine = physics_engine;
        this->drawing_engine = drawing_engine;
        this->screen = screen;
        this->camera = camera;
    }

    void keyboardInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            currentObject = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            currentObject = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            currentObject = 3;
        }
        this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());
        this->world_pos = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        // std::cout << world_pos.x << " " << world_pos.y << std::endl;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            std::cout << "Button pressed" << std::endl;
            this->placeObject();
        }
        this->createCurrentObject();
    }

    void placeObject() {
        switch (currentObject) {
            case 1: {
                RectanglePhysicsConfig config;
                config.position = {world_pos.x, world_pos.y};
                config.size = {1, 0.1};
                auto obj = new RectanglePhysics(physics_engine->getWorldId(), config);
                this->physics_engine->addObjectPhysics(obj);
                this->drawing_engine->addDrawer(new RectangleDrawer(obj));
                break;
            }
            default:
                break;
        }
    }

    void createCurrentObject() {
        delete this->current_drawer;
        this->current_drawer = nullptr;
        if (this->currentObject == 1) {
            RectanglePhysicsConfig* config = new RectanglePhysicsConfig();
            config->position = {this->world_pos.x, this->world_pos.y};
            config->size = {1, 0.1};
            this->current_drawer = new RectangleDrawer(config);
        }
    }

    void draw(Screen* screen, Camera* camera) {
        if (this->current_drawer != nullptr) {
            std::cout << "Drawing" << std::endl;
            this->current_drawer->draw(screen, camera);
        }
    }

private:
    PhysicsEngine* physics_engine;
    DrawingEngine* drawing_engine;
    Screen* screen;
    Camera* camera;
    int currentObject = 0;
    sf::Vector2i mouse_pos;
    sf::Vector2f world_pos;
    ObjectDrawer* current_drawer = nullptr;
};



#endif //OBJECTPLACEMENTSTAGE_HPP
