//
// Created by sp on 25.04.2025.
//

#ifndef COMMON_HPP
#define COMMON_HPP

#include <yaml-cpp/yaml.h>

struct Vector2D {
    float x;
    float y;
};

struct ObjectPhysicsConfig {
    virtual ~ObjectPhysicsConfig() = default;
    Vector2D position = {0,0};
    float rotation = 0;
};

class Shape {
public:
    virtual ~Shape() = default;
    [[nodiscard]] virtual Vector2D getPosition() const = 0;
    [[nodiscard]] virtual float getRotation() const = 0;
};

class ShapePrototype : public Shape {

public:
    virtual void setPosition(const Vector2D &position) = 0;
    virtual void setRotation(float rotation) = 0;
};

enum PhysicsObjectType {
    TypeNone,
    TypeRectangle,
    TypeAccelerationField,
};

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
}
#endif //COMMON_HPP
