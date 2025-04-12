//
// Created by sp on 02.04.2025.
//

#ifndef MAINBALLPHYSICS_HPP
#define MAINBALLPHYSICS_HPP

#include "MainBall.hpp"
#include "ObjectPhysics.hpp"
#include "box2d/box2d.h"



class MainBallPhysics: public ObjectPhysics {

public:
    MainBallPhysics(MainBall* main_ball, b2WorldId world_id);

    [[nodiscard]] b2BodyId getBodyId() const;
    [[nodiscard]] b2ShapeId getShapeId() const;

    b2BodyId getBodyId() override;

    void step() override;

    // void update() const;

private:
    MainBall* main_ball;
    b2BodyId body_id;
    b2ShapeId shape_id;
};



#endif //MAINBALLPHYSICS_HPP
