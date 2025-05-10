#pragma once


#include "Level.hpp"
#include "StateMachine.hpp"
#include "Screen.hpp"
#include "Camera.hpp"


class SimulationStage: public State {
public:
    explicit SimulationStage(StateMachine& state_machine,Level& level, Screen* screen, Camera* camera): state_machine(state_machine), level(level) {
        this->screen = screen;
        this->camera = camera;
    }

    void onInit() override {
        for (auto sprite: this->level.available_objects->placed_objects) {
            this->level.simulation->addObject(*sprite.object);
        }
        for (auto obj: this->level.level_setup->objects) {
            this->level.simulation->addObject(*obj);
        }
    }


    void onUpdate() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            this->camera->setDeltaZoom(0.999);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            this->camera->setDeltaZoom(1.001);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            auto current_pos = sf::Mouse::getPosition(*this->screen->getWindow());
            sf::Vector2f dx = sf::Vector2f(this->mouse_pos - current_pos);
            camera->move(dx.x/screen->getPixelScaleFactor(), -dx.y/screen->getPixelScaleFactor());
        }
        else if (this->level.simulation->goalReached){
            this->state_machine.shutdown = true;
        }
        this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());

        this->clickTest();
        this->level.simulation->fixedStep();
        this->draw(screen, camera);
    }

    void clickTest() {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (this->mouse_left_pressed == true) {
                return;
            }
            sf::Vector2f sf_world_point = (this->screen->getScreenMatrix() * this->camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
            this->level.simulation->click({ sf_world_point.x, sf_world_point.y });
            this->mouse_left_pressed = true;
        }
        else {
            this->mouse_left_pressed = false;
        }
    }

    void onNext() override {}

    void draw(Screen* screen, Camera* camera) {
        for (const auto drawer: this->level.level_setup->drawers) {
            drawer->draw(screen, camera);
        }
        for (auto sprite: this->level.available_objects->placed_objects) {
            sprite.drawer->draw(screen, camera);
        }
    }

private:
    Level& level;
    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    StateMachine& state_machine;
    bool mouse_left_pressed = false;
};
