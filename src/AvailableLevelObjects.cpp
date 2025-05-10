#include "AvailableLevelObjects.hpp"

#include <cassert>
#include <ranges>

#include "Drawer.hpp"
#include "simulation/objects/SimulationObjectBase.hpp"

AvailableLevelObjects::AvailableLevelObjects() {
    this->available_objects["Rectangle"] = 3;
    this->available_objects["Accelerator"] = 3;

    auto ks = std::views::keys(this->available_objects);
    this->available_object_tags = {ks.begin(), ks.end()};
}

AvailableLevelObjects::~AvailableLevelObjects() {
    for (auto sprite: this->placed_objects) {
        delete sprite.drawer;
        delete sprite.object;
    }
}

AvailableLevelObjects::AvailableLevelObjects(const YAML::Node &node) {
    try {
        assert(node.IsSequence());
        for (const YAML::Node& obj_config: node) {
            const auto& tag = obj_config["objectType"].as<std::string>();
            int quantity = obj_config["quantity"].as<int>();
            this->available_objects[tag] = quantity;
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error while loading available level objects");
    }

    auto ks = std::views::keys(this->available_objects);
    this->available_object_tags = {ks.begin(), ks.end()};
}

bool AvailableLevelObjects::place(const std::string &tag, Vector2D position, float rotation) {
    if (available_objects.contains(tag) && available_objects[tag] > 0) {
        const SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(tag);
        sprite.object->config["initial_position"] = position;
        sprite.object->config["rotation"] = rotation;
        sprite.object->applyConfig();
        this->placed_objects.push_back(sprite);
        available_objects[tag]--;
        return true;
    }
    return false;
}

std::vector<std::string> & AvailableLevelObjects::getAvailableObjects() {
    return this->available_object_tags;
}
