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
            if(!(node.IsMap() && node["x"] && node["y"])) {
                return false;
            }
            rhs.x = node["x"].as<float>();
            rhs.y = node["y"].as<float>();
            return true;
        }
    };

    template<>
    struct convert<SimulationBodyConfig> {
        static Node encode(const SimulationBodyConfig& rhs) {
            Node node;
            node["bodyType"] = rhs.bodyType;
            node["initial_position"] = rhs.initial_position;
            node["initial_rotation"] = rhs.initial_rotation;
            node["friction"] = rhs.friction;
            node["restitution"] = rhs.restitution;
            node["density"] = rhs.density;
            node["isSensor"] = rhs.isSensor;
            return node;
        }

        static bool decode(const Node& node, SimulationBodyConfig& rhs) {
            if(!node.IsMap()) {
                return false;
            }
            rhs.bodyType = node["bodyType"].as<int>();
            rhs.initial_position = node["initial_position"].as<Vector2D>();
            rhs.initial_rotation = node["initial_rotation"].as<float>();
            rhs.friction = node["friction"].as<float>();
            rhs.restitution = node["restitution"].as<float>();
            rhs.density = node["density"].as<float>();
            rhs.isSensor = node["isSensor"].as<bool>();
            return true;
        }
    };

    template<>
    struct convert<RectangleBodyConfig> {
        static Node encode(const RectangleBodyConfig& rhs) {
            Node node;
            node = static_cast<const SimulationBodyConfig&>(rhs);
            node["size"] = rhs.size;
            return node;
        }

        static bool decode(const Node& node, RectangleBodyConfig& rhs) {
            if(!node.IsMap()) {
                return false;
            }
            static_cast<SimulationBodyConfig&>(rhs) = node.as<SimulationBodyConfig>();
            rhs.size = node["size"].as<Vector2D>();
            return true;
        }
    };

    template<>
    struct convert<CircleBodyConfig> {
        static Node encode(const CircleBodyConfig& rhs) {
            Node node;
            node = static_cast<const SimulationBodyConfig&>(rhs);
            node["radius"] = rhs.radius;
            return node;
        }

        static bool decode(const Node& node, CircleBodyConfig& rhs) {
            if(!node.IsMap()) {
                return false;
            }
            static_cast<SimulationBodyConfig&>(rhs) = node.as<SimulationBodyConfig>();
            rhs.radius = node["radius"].as<float>();
            return true;
        }
    };
}


template<typename T>
void assignIfExist(const YAML::Node& node, T* ptr) {
    if (node) *ptr = node.as<T>();
}

class YamlConfigLoaderVisitor: public BodyVisitor {
public:
    explicit YamlConfigLoaderVisitor(const YAML::Node& node): node(node) {
        this->index = 0;
    }

    void visitCircle(CircleBody &circle) override {
        circle.config = node[this->index++].as<CircleBodyConfig>();
        circle.setPosition(circle.config.initial_position);
        circle.setRotation(circle.config.initial_rotation);
    }

    void visitRectangle(RectangleBody &rectangle) override {
        rectangle.config = node[this->index++].as<RectangleBodyConfig>();
        rectangle.setPosition(rectangle.config.initial_position);
        rectangle.setRotation(rectangle.config.initial_rotation);
    }

    const YAML::Node node;
    int index;
};

class YamlConfigSaverVisitor: public BodyVisitor {
public:
    explicit YamlConfigSaverVisitor() {
        this->index = 0;
    }

    void visitCircle(CircleBody &circle) override {
        node.push_back(circle.config);
        this->index++;
    }

    void visitRectangle(RectangleBody &rectangle) override {
        node.push_back(rectangle.config);
        this->index++;
    }

    YAML::Node node;
    int index;
};


#endif //YAML_CONFIGURATION_HPP
