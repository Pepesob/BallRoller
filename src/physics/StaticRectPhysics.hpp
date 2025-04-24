//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECTPHYSICS_HPP
#define STATICRECTPHYSICS_HPP

#include "ObjectPhysics.hpp"
#include "StaticRect.hpp"
#include "box2d/box2d.h"


class StaticRectPhysics: public ObjectPhysics {

public:
    StaticRectPhysics(StaticRect* static_rect, b2WorldId world_id, float friction=0.f, float restitution=1.f);

    [[nodiscard]] b2ShapeId getShapeId() const {
        return this->shape_id;
    }
    b2BodyId getBodyId() override {
        return this->body_id;
    }

    void step() override;

    // void update();

protected:
    StaticRect* static_rect = nullptr;
    b2WorldId world_id = {};
    b2BodyId body_id = {};
    b2ShapeId shape_id = {};
};



#endif //STATICRECTPHYSICS_HPP
