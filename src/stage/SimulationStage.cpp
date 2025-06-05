//
// Created by sp on 10.05.2025.
//

#include "SimulationStage.hpp"

#include "MainMenuStage.hpp"
#include "ObjectPlacementStage.hpp"

SimulationStage::SimulationStage(StateMachine &state_machine, std::unique_ptr<Level> level, Screen *screen, Camera *camera, const std::string &new_level_name): level(std::move(level)), state_machine(state_machine), new_level_name(new_level_name) {
    this->screen = screen;
    this->camera = camera;
}

void SimulationStage::onInit() {
    for (auto sprite: this->level->available_objects->placed_objects) {
        this->level->simulation->addObject(*sprite.object);
    }
    for (auto obj: this->level->level_setup->objects) {
        this->level->simulation->addObject(*obj);
    }
    this->level->simulation->onInit();
}

void SimulationStage::onUpdate() {
    this->handleEvents();
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
    else if (this->level->simulation->goalReached){
        this->state_machine.switchState(std::make_unique<MainMenuStage>(this->state_machine, this->screen, this->camera));
    }
    this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());

    this->clickTest();
    this->level->simulation->fixedStep();
    this->draw(screen, camera);
    if (this->go_back_to_placement) {
        level->simulation->destroyWorld();
        level->simulation->createWorld();
        this->state_machine.switchState(std::make_unique<ObjectPlacementStage>(this->state_machine, std::move(level), screen, camera, this->new_level_name));
    }
}

void SimulationStage::clickTest() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (this->mouse_left_pressed == true) {
            return;
        }
        sf::Vector2f sf_world_point = (this->screen->getScreenMatrix() * this->camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
        this->level->simulation->click({ sf_world_point.x, sf_world_point.y });
        this->mouse_left_pressed = true;
    }
    else {
        this->mouse_left_pressed = false;
    }
}

void SimulationStage::onNext() {
}

void SimulationStage::draw(Screen *screen, Camera *camera) {
    this->screen->draw(this->screen, this->camera);
    for (const auto drawer: this->level->level_setup->drawers) {
        drawer->draw(screen, camera);
    }
    for (auto sprite: this->level->available_objects->placed_objects) {
        sprite.drawer->draw(screen, camera);
    }
}

void SimulationStage::handleEvents() {
    while (const std::optional event = this->screen->getWindow()->pollEvent()) {
        this->screen->handleEvent(event);
        this->camera->handleEvent(event);
        // if (const auto e = event->getIf<sf::Event::KeyPressed>()) {
        //     this->onKeyPressed(*e);
        // }
        if (const auto e = event->getIf<sf::Event::KeyPressed>()) {
            if (e->code == sf::Keyboard::Key::R) {
                this->go_back_to_placement = true;
            }
            if (e->code == sf::Keyboard::Key::Escape) {
                this->state_machine.switchState(std::make_unique<MainMenuStage>(this->state_machine, this->screen, this->camera));
            }
        }
    }
}
