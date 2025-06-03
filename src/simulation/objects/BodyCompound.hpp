

#pragma once

#include "common.hpp"
#include "simulation/physics/SimulationBody.hpp"


class RevoluteJoint {
public:
    RevoluteJoint() {
        this->joint_def = b2DefaultRevoluteJointDef();
        this->joint_def.lowerAngle = 0.0f;
        this->joint_def.upperAngle = 2.0f * 3.14159265358979323846;
    }

    SimulationBody* body1{};
    SimulationBody* body2{};
    Vector2D local_pos1{};
    Vector2D local_pos2{};
    b2RevoluteJointDef joint_def{};
    b2JointId joint_id{};
};


class BodyCompound {
public:
    BodyCompound() = default;

    void addBody(SimulationBody* body, Vector2D local_position={0,0}, float self_rotation=0) {
        this->placed_bodies.push_back({body, local_position, self_rotation});
    }

    void setPosition(const Vector2D world_position) {
        this->world_position = world_position;
        for (auto&[body, local_position, self_rotation]: this->placed_bodies) {
            InitialPositionSetterVisitor visitor;
            visitor.position = world_position + local_position;
            body->accept(visitor);
        }
    }

    void setRotation(float radians) {
        this->compound_rotation = radians;
        for (auto&[body, local_position, self_rotation]: this->placed_bodies) {
            InitialPositionSetterVisitor visitor;
            visitor.rotation = self_rotation + radians;
            body->accept(visitor);
        }
    }

    void setTransform(const Vector2D world_position, float radians) {
        this->world_position = world_position;
        this->compound_rotation = radians;
        for (auto&[body, local_position, self_rotation]: this->placed_bodies) {
            InitialPositionSetterVisitor visitor;
            float sint = std::sin(compound_rotation);
            float cost = std::cos(compound_rotation);
            visitor.position = Vector2D{local_position.x * cost - local_position.y * sint, local_position.x * sint + local_position.y * cost} + world_position;
            visitor.rotation = self_rotation + radians;
            body->accept(visitor);
        }
    }

    Vector2D getPosition() const {
        return this->world_position;
    }

    float getRotation() const {
        return this->compound_rotation;
    }

private:
    class InitialPositionSetterVisitor: public BodyVisitor {
    public:
        void visitCircle(CircleBody &circle) override {
            circle.config.initial_position = this->position;
            circle.config.initial_rotation = this->rotation;
        }

        void visitRectangle(RectangleBody &rectangle) override {
            rectangle.config.initial_position = this->position;
            rectangle.config.initial_rotation = this->rotation;
        }

        Vector2D position = {};
        float rotation = 0;
    };

    struct PlacedBody {
        SimulationBody* body;
        Vector2D local_position;
        float self_rotation;
    };

    Vector2D world_position = {};
    float compound_rotation = 0;
    std::vector<PlacedBody> placed_bodies = {};
};


