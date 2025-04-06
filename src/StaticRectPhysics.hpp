//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECTPHYSICS_HPP
#define STATICRECTPHYSICS_HPP

#include "StaticRect.hpp"
#include "box2d/box2d.h"


class StaticRectPhysics {

public:
    StaticRectPhysics(StaticRect* static_rect, b2WorldId world_id);

    void update();

private:
    StaticRect* static_rect;
    b2WorldId world_id;
    b2BodyId body_id;
    b2ShapeId shape_id;
};



#endif //STATICRECTPHYSICS_HPP
