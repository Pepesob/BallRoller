//
// Created by sp on 25.04.2025.
//

#ifndef COMMON_HPP
#define COMMON_HPP

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
#endif //COMMON_HPP
