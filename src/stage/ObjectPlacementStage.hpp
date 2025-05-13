#pragma once

#include "AvailableLevelObjects.hpp"
#include "Level.hpp"
#include "SimulationStage.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "simulation/objects/AcceleratorObject.hpp"
#include "StateMachine.hpp"



class ObjectPlacementStage: public State {

public:
    ObjectPlacementStage(StateMachine& state_machine, Level& level, Screen* screen, Camera* camera): state_machine(state_machine), level(level) {
        this->screen = screen;
        this->camera = camera;
    }

    void everyFrameInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
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
    }

    void onKeyPressed(const sf::Event::KeyPressed& keyPressed) {
        switch (keyPressed.code) {
            case sf::Keyboard::Key::Num1:
            case sf::Keyboard::Key::Num2:
            case sf::Keyboard::Key::Num3:
            case sf::Keyboard::Key::Num4:
            case sf::Keyboard::Key::Num5:
            case sf::Keyboard::Key::Num6:
            case sf::Keyboard::Key::Num7:
                this->index = static_cast<int>(keyPressed.code) - static_cast<int>(sf::Keyboard::Key::Num1);
            this->changeObject(this->index);
            break;
            case sf::Keyboard::Key::P:
                this->state_machine.switchState(new SimulationStage(state_machine, level, screen, camera));
            break;
            case sf::Keyboard::Key::S:
                saveCurrentWorld(this->level.available_objects->placed_objects, "resources/Level1234.yaml");
            break;
            default:
                break;
        }
    }
    void onMousePressed(const sf::Event::MouseButtonPressed& keyPressed) {
        if (keyPressed.button == sf::Mouse::Button::Left) {
            this->placeObject();
        }
    }

    void onMouseMoved(const sf::Event::MouseMoved& mouseMoved) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sf::Vector2f dx = sf::Vector2f(this->mouse_pos - mouseMoved.position);
            camera->move(dx.x/screen->getPixelScaleFactor(), -dx.y/screen->getPixelScaleFactor());
        }
        this->mouse_pos = mouseMoved.position;
        sf::Vector2f wp = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        this->world_pos = {wp.x, wp.y};
        this->moveObject();
    }

    void moveObject() {
        const auto objs = level.available_objects->getAvailableObjects();
        if (this->index >= 0 && this->index < objs.size()) {
            // this->current_sprite.object->config["initial_position"] = this->world_pos;
            // this->current_sprite.object->config["initial_rotation"] = this->rotation_radians;
            // this->current_sprite.object->applyConfig();
            this->current_sprite.object->compound.setTransform(this->world_pos, this->rotation_radians);
        }
    }

    void placeObject() {
        const auto objs = level.available_objects->getAvailableObjects();
        if (this->index >= 0 && this->index < objs.size()) {
            this->level.available_objects->place(objs[this->index], this->world_pos, this->rotation_radians);
        }
        this->current_tag = "";
        this->index = -1;
    }

    void draw() {
        const auto objs = level.available_objects->getAvailableObjects();
        for (const auto drawer: this->level.level_setup->drawers) {
            drawer->draw(screen, camera);
        }
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

    void onInit() override {

    }

    void onUpdate() override {
        this->handleEvents();
        this->everyFrameInput();
        this->moveObject();
        this->draw();
    }

    void onNext() override {}

    void handleEvents() {
        while (const std::optional event = this->screen->getWindow()->pollEvent()) {
            this->screen->handleEvent(event);
            if (const auto e = event->getIf<sf::Event::KeyPressed>()) {
                this->onKeyPressed(*e);
            }
            else if (const auto e = event->getIf<sf::Event::MouseButtonPressed>()) {
                this->onMousePressed(*e);
            }
            else if (const auto e = event->getIf<sf::Event::MouseMoved>()) {
                this->onMouseMoved(*e);
            }
        }
    }

private:
    int index = -1;

    std::string current_tag;
    SimulationSprite current_sprite {};

    StateMachine& state_machine;
    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    Vector2D world_pos {0,0};
    float rotation_radians = 0;


    Level& level;
};

