//
// Created by sp on 26.04.2025.
//

#ifndef OBJECTPLACEMENTSTAGE_HPP
#define OBJECTPLACEMENTSTAGE_HPP
#include <iostream>
#include <unordered_map>

#include "AvailableLevelObjects.hpp"
#include "DrawingEngine.hpp"
#include <SFML/Window.hpp>
#include "SFML/Graphics/Transform.hpp"
#include "simulation/objects/AcceleratorObject.hpp"
#include "simulation/objects/MainBallObject.hpp"
#include "simulation/objects/RectangleObject.hpp"


class ObjectPlacementStage {

public:
    ObjectPlacementStage(Screen* screen, Camera* camera){
        this->screen = screen;
        this->camera = camera;

        this->main_ball_object = std::make_shared<MainBallObject>();
        this->rectangle_object = std::make_shared<RectangleObject>();
        this->accelerator_object = std::make_shared<AcceleratorObject>();

        this->available_objects[0] = this->main_ball_object;
        this->available_objects[1] = this->rectangle_object;
        this->available_objects[2] = this->accelerator_object;

        this->available_drawers[0] = new MainBallDrawer(this->main_ball_object);
        this->available_drawers[1] = new RectangleDrawer(this->rectangle_object);
    }

    void keyboardInput(B2dSimulation& simulation, DrawingEngine& drawingEngine) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            this->index = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            this->index = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            this->index = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sf::Transform t = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse();
            sf::Vector2f current = t.transformPoint(sf::Vector2f(sf::Mouse::getPosition(*this->screen->getWindow())));
            sf::Vector2f prev = t.transformPoint(sf::Vector2f(this->mouse_pos));
            sf::Vector2f dx = prev - current;
            this->camera->move(dx.x, dx.y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            this->camera->setDeltaZoom(0.001);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            this->camera->setDeltaZoom(-0.001);
        }
        this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());
        sf::Vector2f wp = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        this->world_pos = {wp.x, wp.y};
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (pressed == true || this->index == -1) {
                return;
            }
            this->placeObject(simulation, drawingEngine);
            std::cout << this->index << std::endl;
            pressed = true;
        } else {
            pressed = false;
        }
    }

    void placeObject(B2dSimulation& simulation, DrawingEngine& drawingEngine) {
        this->available_objects[this->index]->setInitialPosition(this->world_pos);
        simulation.addObject(this->available_objects[this->index]);
        drawingEngine.addDrawer(this->available_drawers[this->index]);
    }

    void draw(Screen* screen, Camera* camera) {
        if (this->index != -1) {
            this->available_objects[this->index]->setInitialPosition(this->world_pos);
            this->available_drawers[this->index]->drawPreview(screen, camera);
        }
    }

private:
    bool pressed = false;
    size_t index = -1;

    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    Vector2D world_pos {0,0};

    std::shared_ptr<MainBallObject> main_ball_object;
    std::shared_ptr<RectangleObject> rectangle_object;
    std::shared_ptr<AcceleratorObject> accelerator_object;

    std::unordered_map<std::string, float> simulationObjectConfig;
    std::shared_ptr<SimulationObjectBase> available_objects[4]{};
    SimulationObjectDrawer* available_drawers[4]{};
};



#endif //OBJECTPLACEMENTSTAGE_HPP
