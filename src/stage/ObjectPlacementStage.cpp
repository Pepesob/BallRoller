//
// Created by sp on 26.04.2025.
//

#include "ObjectPlacementStage.hpp"

#include <fstream>

#include "SFML/Graphics/Transform.hpp"
#include "AvailableLevelObjects.hpp"
#include "MainMenuStage.hpp"

void saveCurrentWorld(const std::vector<SimulationSprite> &objects, const std::unordered_map<std::string, int>& tagCounts, const std::string &filename) {
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "setupObjects" << YAML::BeginSeq;
    for (const auto& obj : objects) {
        out << YAML::BeginMap;
        out << YAML::Key << "objectType" << YAML::Value << obj.object->objectType;
        out << YAML::Key << "initial_position" << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << obj.object->compound.getPosition().x;
        out << YAML::Key << "y" << YAML::Value << obj.object->compound.getPosition().y << YAML::EndMap;
        out << YAML::Key << "initial_rotation" << YAML::Value << obj.object->compound.getRotation();
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    // availableObjects
    // Save available objects from tagCounts
    out << YAML::Key << "availableObjects" << YAML::BeginSeq;
    for (const auto& [objectType, quantity] : tagCounts) {
        if (quantity == 0) {
            continue;
        }
        out << YAML::BeginMap;
        out << YAML::Key << "objectType" << YAML::Value << objectType;
        out << YAML::Key << "quantity" << YAML::Value << quantity;
        out << YAML::EndMap;
    }
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


ObjectPlacementStage::ObjectPlacementStage(StateMachine &state_machine, std::unique_ptr<Level> level, Screen *screen, Camera *camera, const std::string& customLevelName): state_machine(state_machine), level(std::move(level)) {
    this->screen = screen;
    this->camera = camera;
    this->highlighter.setRadius(5);
    this->highlighter.setOrigin({5,5});
    this->highlighter.setFillColor(sf::Color::Blue);
    this->custom_level_name = customLevelName;

    for (const auto& tag : SimulationObjectFactory::getAvailableTags()) {
        tagCounts[tag] = 0;  // default to 0
    }
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
            this->switch_to_simulation = true;
            break;
        case sf::Keyboard::Key::S:
            if (!this->custom_level_name.empty()) {
                saveCurrentWorld(this->level->available_objects->placed_objects, this->tagCounts,"resources/levels/" + this->custom_level_name);
                this->state_machine.switchState(std::make_unique<MainMenuStage>(this->state_machine, this->screen, this->camera));
            }
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
        case sf::Keyboard::Key::Escape:
            this->state_machine.switchState(std::make_unique<MainMenuStage>(this->state_machine, this->screen, this->camera));
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
    this->screen->draw(this->screen, this->camera);
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
    this->current_sprite.free();
    this->current_sprite = SimulationObjectFactory::createSimulationSprite(tag);
}

void ObjectPlacementStage::onInit() {
    ImGui::SFML::Init(*this->screen->getWindow());
}

void ObjectPlacementStage::onUpdate() {
    if (!this->custom_level_name.empty()) {
        ImGui::SFML::Update(*this->screen->getWindow(), deltaClock.restart());
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
        ImGui::Begin("Tag Configuration");

        ImGui::Text("Set number of available elements:");
        ImGui::Separator();

        for (auto& [tag, count] : tagCounts) {
            ImGui::PushID(tag.c_str()); // Prevent ID conflicts
            ImGui::InputInt(tag.c_str(), &count);
            ImGui::PopID();
        }

        ImGui::End();
        ImGui::SFML::Render(*this->screen->getWindow());
    }
    this->handleEvents();
    this->everyFrameInput();
    this->moveObject();
    this->draw();
    if (this->switch_to_simulation) {
        this->state_machine.switchState(std::make_unique<SimulationStage>(state_machine, std::move(level), screen, camera));
    }
}

void ObjectPlacementStage::onNext() {
    this->current_sprite.free();
    ImGui::SFML::Shutdown();
}

void ObjectPlacementStage::handleEvents() {
    while (const std::optional event = this->screen->getWindow()->pollEvent()) {
        this->screen->handleEvent(event);
        this->camera->handleEvent(event);
        ImGui::SFML::ProcessEvent(*this->screen->getWindow(), event.value());
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
