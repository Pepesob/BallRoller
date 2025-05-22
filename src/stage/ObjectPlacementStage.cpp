//
// Created by sp on 26.04.2025.
//

#include "ObjectPlacementStage.hpp"

#include <fstream>

#include "SFML/Graphics/Transform.hpp"
#include "AvailableLevelObjects.hpp"

void saveCurrentWorld(const std::vector<SimulationSprite> &objects, const std::string &filename) {
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "setupObjects" << YAML::BeginSeq;
    for (const auto& obj : objects) {
        out << obj.object->config;
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::BeginMap;

    // availableObjects
    out << YAML::Key << "availableObjects" << YAML::Value << YAML::BeginSeq;

    out << YAML::BeginMap;
    out << YAML::Key << "objectType" << YAML::Value << "Accelerator";
    out << YAML::Key << "quantity" << YAML::Value << 6;
    out << YAML::EndMap;

    out << YAML::BeginMap;
    out << YAML::Key << "objectType" << YAML::Value << "Teleporter";
    out << YAML::Key << "quantity" << YAML::Value << 1;
    out << YAML::EndMap;

    out << YAML::BeginMap;
    out << YAML::Key << "objectType" << YAML::Value << "Rectangle";
    out << YAML::Key << "quantity" << YAML::Value << 1;
    out << YAML::EndMap;

    out << YAML::EndSeq;

    // simulation
    out << YAML::Key << "simulation" << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "gravity" << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << 0;
    out << YAML::Key << "y" << YAML::Value << -6.0;
    out << YAML::EndMap; // gravity
    out << YAML::EndMap; // simulation

    out << YAML::EndMap;

    std::ofstream fout(filename);
    fout << out.c_str();
}


ObjectPlacementStage::ObjectPlacementStage(StateMachine &state_machine, Level *level, Screen *screen, Camera *camera): state_machine(state_machine), level(level) {
    this->screen = screen;
    this->camera = camera;
    this->highlighter.setRadius(5);
    this->highlighter.setOrigin({5,5});
    this->highlighter.setFillColor(sf::Color::Blue);
}

void ObjectPlacementStage::everyFrameInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->camera->setDeltaZoom(0.999);
        this->calculateMouseWorldPos();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->camera->setDeltaZoom(1.001);
        this->calculateMouseWorldPos();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->rotation_radians += 0.001;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->rotation_radians -= 0.001;
    }
}

void ObjectPlacementStage::onKeyPressed(const sf::Event::KeyPressed &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Key::Num1:
        case sf::Keyboard::Key::Num2:
        case sf::Keyboard::Key::Num3:
        case sf::Keyboard::Key::Num4:
        case sf::Keyboard::Key::Num5:
        case sf::Keyboard::Key::Num6:
        case sf::Keyboard::Key::Num7:
            this->selected_object = -1;
            this->index = static_cast<int>(keyPressed.code) - static_cast<int>(sf::Keyboard::Key::Num1);
            this->changeObject(this->index);
            break;
        case sf::Keyboard::Key::P:
            this->state_machine.switchState(new SimulationStage(state_machine, level, screen, camera));
            break;
        case sf::Keyboard::Key::S:
            saveCurrentWorld(this->level->available_objects->placed_objects, "resources/levels/Level12345.yaml");
            break;
        case sf::Keyboard::Key::Period:
            this->index = -1;
            this->selected_object = (this->selected_object + 1) % this->level->available_objects->placed_objects.size();
            break;
        case sf::Keyboard::Key::Comma:
            this->index = -1;
            this->selected_object = (this->selected_object == -1 ? this->selected_object : this->selected_object - 1) % this->level->available_objects->placed_objects.size();
            break;
        case sf::Keyboard::Key::Backspace:
            if (this->selected_object >= 0 && this->selected_object < this->level->available_objects->placed_objects.size()) {
                this->level->available_objects->remove(this->selected_object);
                this->selected_object = -1;
            }
            break;
        default:
            break;
    }
}

void ObjectPlacementStage::onMousePressed(const sf::Event::MouseButtonPressed &keyPressed) {
    if (keyPressed.button == sf::Mouse::Button::Left) {
        this->placeObject();
    }
}

void ObjectPlacementStage::onMouseMoved(const sf::Event::MouseMoved &mouseMoved) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        sf::Vector2f dx = sf::Vector2f(this->mouse_pos - mouseMoved.position);
        camera->move(dx.x/screen->getPixelScaleFactor(), -dx.y/screen->getPixelScaleFactor());
    }
    this->mouse_pos = mouseMoved.position;
    this->calculateMouseWorldPos();
    this->moveObject();
}

void ObjectPlacementStage::calculateMouseWorldPos() {
    sf::Vector2f wp = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
    this->world_pos = {wp.x, wp.y};
}

void ObjectPlacementStage::moveObject() const {
    const auto objs = level->available_objects->getAvailableObjects();
    if (this->index >= 0 && this->index < objs.size()) {
        // this->current_sprite.object->config["initial_position"] = this->world_pos;
        // this->current_sprite.object->config["initial_rotation"] = this->rotation_radians;
        // this->current_sprite.object->applyConfig();
        this->current_sprite.object->compound.setTransform(this->world_pos, this->rotation_radians);
    }
}

void ObjectPlacementStage::placeObject() {
    const auto objs = level->available_objects->getAvailableObjects();
    if (this->index >= 0 && this->index < objs.size()) {
        this->level->available_objects->place(objs[this->index], this->world_pos, this->rotation_radians);
    }
    this->current_tag = "";
    this->index = -1;
}

void ObjectPlacementStage::draw() {
    const auto objs = level->available_objects->getAvailableObjects();
    for (const auto drawer: this->level->level_setup->drawers) {
        drawer->draw(screen, camera);
    }
    for (const auto sprite: this->level->available_objects->placed_objects) {
        sprite.drawer->draw(screen, camera);
    }
    if (this->index >= 0 && this->index < objs.size()) {
        this->current_sprite.drawer->draw(screen, camera);
    }
    if (this->selected_object >= 0 && this->selected_object < this->level->available_objects->placed_objects.size()) {
        Vector2D v = this->level->available_objects->placed_objects[this->selected_object].object->compound.getPosition();
        sf::Vector2f v_sf = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint(sf::Vector2f({v.x, v.y}));
        this->highlighter.setPosition(v_sf);
        this->screen->getWindow()->draw(this->highlighter);
    }
}

void ObjectPlacementStage::changeObject(int index) {
    const auto objs = this->level->available_objects->getAvailableObjects();
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

void ObjectPlacementStage::onInit() {

}

void ObjectPlacementStage::onUpdate() {
    this->handleEvents();
    this->everyFrameInput();
    this->moveObject();
    this->draw();
}

void ObjectPlacementStage::onNext() {}

void ObjectPlacementStage::handleEvents() {
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
