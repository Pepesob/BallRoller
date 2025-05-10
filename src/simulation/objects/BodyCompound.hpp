

#pragma once
#include "common.hpp"
#include "simulation/physics/SimulationBody.hpp"


class BodyCompound {
public:
    BodyCompound() = default;

    void addBody(SimulationBody& body, Vector2D local_position, float self_rotation) {
        this->placed_bodies.push_back({body, local_position, self_rotation});
    }

    void setPosition(const Vector2D world_position) {
        for (auto&[body, local_position, self_rotation]: this->placed_bodies) {
            InitialPositionSetterVisitor visitor;
            visitor.position = world_position + local_position;
            visitor.rotation = self_rotation;
            body.accept(visitor);
        }
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
        SimulationBody& body;
        Vector2D local_position;
        float self_rotation;
    };

    Vector2D world_position = {};
    float self_rotation = 0;
    std::vector<PlacedBody> placed_bodies = {};
};


