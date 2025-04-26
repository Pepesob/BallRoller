//
// Created by sp on 26.04.2025.
//

#ifndef EXAMPLESETUP_HPP
#define EXAMPLESETUP_HPP
#include <vector>

#include "MainBallDrawer.hpp"
#include "ObjectDrawer.hpp"
#include "RectangleDrawer.hpp"
#include "physics/PhysicsEngine.hpp"
#include "physics/RectanglePhysics.hpp"


class ExampleSetup {
public:
    ExampleSetup(PhysicsEngine* pe) {
        // TODO - consider initialization of physics objects inside PhysicsEngine from method, not in constructor to avoid ExampleSetup need for PhysicsEngine
        MainBallPhysics* ball_physics = new MainBallPhysics(pe->getWorldId());
        MainBallDrawer* ball_drawer = new MainBallDrawer(ball_physics);

        RectanglePhysicsConfig config;
        config.size = {1, 0.1};
        config.rotation = -3.14 / 6;
        RectanglePhysics* static_rect_physics = new RectanglePhysics(pe->getWorldId(), config);
        RectangleDrawer* static_rect_drawer = new RectangleDrawer(static_rect_physics);

        RectanglePhysicsConfig config2;
        config2.position = {1.5f, -0.5f};
        config2.size = {1, 0.1};
        config2.rotation = 3.14 / 6;
        config2.restitution = 2.;
        RectanglePhysics* static_rect_physics2 = new RectanglePhysics(pe->getWorldId(), config2);
        RectangleDrawer* static_rect_drawer2 = new RectangleDrawer(static_rect_physics2);

        drawers.push_back(ball_drawer);
        drawers.push_back(static_rect_drawer);
        drawers.push_back(static_rect_drawer2);

        objects.push_back(ball_physics);
        objects.push_back(static_rect_physics);
        objects.push_back(static_rect_physics2);
    }
    std::vector<ObjectDrawer*> drawers;
    std::vector<ObjectPhysics*> objects;
};



#endif //EXAMPLESETUP_HPP
