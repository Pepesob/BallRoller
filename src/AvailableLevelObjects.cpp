#include "AvailableLevelObjects.hpp"

#include <cassert>
#include <ranges>

#include "Drawer.hpp"
#include "simulation/objects/SimulationObjectBase.hpp"

AvailableLevelObjects::AvailableLevelObjects() {
    for (auto tag: SimulationObjectFactory::getAvailableTags()) {
        this->available_objects[tag] = INT_MAX;
    }

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
        // this->placed_objects_infos.push_back({tag, position, rotation});
        const SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(tag);
        sprite.object->config["initial_position"] = position;
        sprite.object->config["initial_rotation"] = rotation;
        sprite.object->applyConfig();
        this->placed_objects.push_back(sprite);
        available_objects[tag]--;
        return true;
    }
    return false;
}

bool AvailableLevelObjects::place(const std::string &tag, const YAML::Node& config) {
    if (available_objects.contains(tag) && available_objects[tag] > 0) {
        // this->placed_objects_infos.push_back({tag, config["initial_position"].as<Vector2D>(), config["initial_rotation"].as<float>()});
        const SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(tag);
        sprite.object->config = config;
        sprite.object->applyConfig();
        this->placed_objects.push_back(sprite);
        available_objects[tag]--;
        return true;
    }
    return false;
}

void AvailableLevelObjects::remove(int index) {
    const std::string tag = this->placed_objects[index].object->objectType;
    this->available_objects[tag]++;
    (this->placed_objects.begin() + index)->free();
    this->placed_objects.erase(this->placed_objects.begin() + index);

}

// void AvailableLevelObjects::reset() {
//     for (const auto& info: this->placed_objects_infos) {
//         const SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(info.tag);
//         sprite.object->config["initial_position"] = info.position;
//         sprite.object->config["initial_rotation"] = info.rotation;
//         sprite.object->applyConfig();
//         this->placed_objects.push_back(sprite);
//     }
// }

std::vector<std::string> & AvailableLevelObjects::getAvailableObjects() {
    return this->available_object_tags;
}
