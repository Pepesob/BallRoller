//
// Created by sp on 05.05.2025.
//

#ifndef YAML_CONFIGURATION_HPP
#define YAML_CONFIGURATION_HPP

#include "yaml-cpp/yaml.h"
#include "common.hpp"


namespace YAML {
    template<>
    struct convert<Vector2D> {
        static Node encode(const Vector2D& rhs) {
            Node node;
            node["x"] = rhs.x;
            node["y"] = rhs.y;
            return node;
        }

        static bool decode(const Node& node, Vector2D& rhs) {
            if(!node.IsMap()) {
                return false;
            }
            rhs.x = node["x"].as<float>();
            rhs.y = node["y"].as<float>();
            return true;
        }
    };
}


template<typename T>
void assignIfExist(const YAML::Node& node, T* ptr) {
    if (node) *ptr = node.as<T>();
}


#endif //YAML_CONFIGURATION_HPP
