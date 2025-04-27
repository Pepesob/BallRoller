//
// Created by sp on 26.04.2025.
//

#ifndef OBJECTPLACEMENTSTAGE_HPP
#define OBJECTPLACEMENTSTAGE_HPP
#include "DrawingEngine.hpp"
#include "Drawer.hpp"
#include "RectangleDrawer.hpp"
#include "SimulationObjectFactory.hpp"
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
            this->current_object_type = PhysicsObjectType::Rectangle;
            auto* config = new RectanglePhysicsConfig();
            config->size = {1, 0.1};
            this->current_config = config;
            this->current_drawer = SimulationObjectFactory::createObjectPreviewDrawer(this->current_object_type, *config);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            this->current_object_type = PhysicsObjectType::None;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            this->current_object_type = PhysicsObjectType::None;
        }
        this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());
        this->world_pos = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            this->placeObject();
        }
    }

    void placeObject() {
        b2WorldId world_id = this->physics_engine->getWorldId();
        this->current_config->position = {this->world_pos.x, this->world_pos.y};
        ObjectPhysics* obj = SimulationObjectFactory::createObjectPhysics(this->current_object_type, this->current_config, world_id);
        Drawer* obj_drawer = SimulationObjectFactory::createObjectDrawer(this->current_object_type, obj);
        this->physics_engine->addObjectPhysics(obj);
        this->drawing_engine->addDrawer(obj_drawer);
    }

    void draw(Screen* screen, Camera* camera) {
        if (this->current_drawer != nullptr) {
            this->current_drawer->setPosition({this->world_pos.x, this->world_pos.y});
            this->current_drawer->draw(screen, camera);
        }
    }

private:
    PhysicsEngine* physics_engine;
    DrawingEngine* drawing_engine;
    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    sf::Vector2f world_pos;
    ObjectPreviewDrawer* current_drawer = nullptr;
    ObjectPhysicsConfig* current_config = nullptr;
    PhysicsObjectType current_object_type = PhysicsObjectType::None;
};



#endif //OBJECTPLACEMENTSTAGE_HPP
