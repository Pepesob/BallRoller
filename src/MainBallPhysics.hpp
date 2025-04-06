//
// Created by sp on 02.04.2025.
//

#ifndef MAINBALLPHYSICS_HPP
#define MAINBALLPHYSICS_HPP

#include "MainBall.hpp"
#include "box2d/box2d.h"



class MainBallPhysics {

public:
    MainBallPhysics(MainBall* main_ball, b2WorldId world_id);

    void update() const;

private:
    MainBall* main_ball;
    b2BodyId body_id;
    b2ShapeId shape_id;
};



#endif //MAINBALLPHYSICS_HPP
