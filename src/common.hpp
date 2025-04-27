//
// Created by sp on 25.04.2025.
//

#ifndef COMMON_HPP
#define COMMON_HPP
#include "physics/ObjectPhysics.hpp"

struct Vector2D {
    float x;
    float y;
};

struct ObjectPhysicsConfig {
    virtual ~ObjectPhysicsConfig() = default;
    Vector2D position = {0,0};
    float rotation = 0;
};

enum PhysicsObjectType {
    None,
    Rectangle,
};
#endif //COMMON_HPP
