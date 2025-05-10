#pragma once

#include <string>
#include <vector>

#include "simulation/objects/SimulationObjectFactory.hpp"


class AvailableLevelObjects {
public:
    AvailableLevelObjects();

    ~AvailableLevelObjects();

    explicit AvailableLevelObjects(const YAML::Node& node);
    bool place(const std::string& tag, Vector2D position, float rotation);
    [[nodiscard]] std::vector<std::string>& getAvailableObjects();

    std::vector<std::string> available_object_tags;
    std::map<std::string, int> available_objects;
    std::vector<SimulationSprite> placed_objects;
};
